//##############################################################################################################################################################################################################//
//Aquila - An Open-Source GPU-Accelerated Toolkit for Cognitive and Neuro-Robotics Research																														//
//																																																				//
//Copyright (c) <2012>, Anthony Morse																																											//
//All rights reserved.																																															//
//																																																				//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:																//
//																																																				//
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.																				//
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.	//
//																																																				//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	//
//A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT	//
//LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR	//
//TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.																//
//                                                                                                                                                                                                              //
//The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted                                                                                  //
//as representing official policies,either expressed or implied, of the FreeBSD Project.                                                                                                                        //
//##############################################################################################################################################################################################################//


#include "tracker.h"
#include <string>
#include <stdlib.h>


namespace aquilatracker
{
/*!
 * \brief Default constructor. Sets the defaults that would have been
    in standard Aquila config.ini for tracker
 */
Tracker::Tracker()
{
   threshold = 50;
   saturation = 30.0;
   simulationMode = true;
   saturationMask = false;
   strictObjectDetection = true;
   camCalib = true;
   leftCamOn = true;
   rightCamOn = false;
}

/*!
 * \brief Alternative constructor to set parameters on creation
 */
Tracker::Tracker(int thresh, float sat, bool simmode, bool satmask, bool strictObj, bool calib, bool rightcam, bool leftcam)
{
   threshold = thresh;
   saturation = sat;
   simulationMode = simmode;
   saturationMask = satmask;
   strictObjectDetection = strictObj;
   camCalib = calib;
   leftCamOn = leftcam;
   rightCamOn = rightcam;
}

/*!
 * \brief Destructor.
 */
Tracker::~Tracker()
{
    clean();
}

/*!
 * \brief Opens image ports.
 */
bool Tracker::openPorts(std::string portPrefix)
{
    //assign port names
    leftCam.inputPortName = portPrefix + "/cam/left:i";
    leftCam.outputPortName = portPrefix + "/cam/left:o";
    rightCam.inputPortName = portPrefix + "/cam/right:i";
    rightCam.outputPortName = portPrefix + "/cam/right:o";
    leftMotion.inputPortName = portPrefix + "/motion/left:i";
    leftMotion.outputPortName = portPrefix + "/motion/left:o";
    rightMotion.inputPortName = portPrefix + "/motion/right:i";
    rightMotion.outputPortName = portPrefix + "/motion/right:o";
    trackerOutputPortName = portPrefix + "/data:o";

    //open ports
    bool success = (leftCam.outputPort.open(leftCam.outputPortName.c_str()) &&
                    rightCam.outputPort.open(rightCam.outputPortName.c_str()) &&
                    leftCam.inputPort.open(leftCam.inputPortName.c_str()) &&
                    rightCam.inputPort.open(rightCam.inputPortName.c_str()) &&
                    leftMotion.inputPort.open(leftMotion.inputPortName.c_str()) &&
                    rightMotion.inputPort.open(rightMotion.inputPortName.c_str()) &&
                    leftMotion.outputPort.open(leftMotion.outputPortName.c_str()) &&
                    rightMotion.outputPort.open(rightMotion.outputPortName.c_str()) &&
                    outputPort.open(trackerOutputPortName.c_str()));

    return success;
}

/*!
 * \brief Connects ports.
 */
void Tracker::connectPorts()
{
    if(simulationMode)
    {
        if(leftCamOn)
        {
           Network::connect("/icubSim/cam/left", leftCam.inputPortName.c_str());
        }

        if(rightCamOn)
        {
           Network::connect("/icubSim/cam/right", rightCam.inputPortName.c_str());
        }
    }
    else
    {
        if(camCalib)
        {
            if(leftCamOn)
            {
                Network::connect("/icub/camcalib/left/out", leftCam.inputPortName.c_str());
            }

            if(rightCamOn)
            {
                Network::connect("/icub/camcalib/right/out", rightCam.inputPortName.c_str());
            }
        }
        else
        {
            if(leftCamOn)
            {
                Network::connect("/icub/cam/left", leftCam.inputPortName.c_str());
            }

            if(rightCamOn)
            {
                Network::connect("/icub/cam/right", rightCam.inputPortName.c_str());
            }
        }
    }
}

/*!
 * \brief Disconnects ports.
 */
void Tracker::disconnectPorts()
{
    if(simulationMode)
    {
        if(leftCamOn)
        {
           Network::disconnect("/icubSim/cam/left", leftCam.inputPortName.c_str());
        }

        if(rightCamOn)
        {
           Network::disconnect("/icubSim/cam/right", rightCam.inputPortName.c_str());
        }
    }
    else
    {
        if(camCalib)
        {
            if(leftCamOn)
            {
                Network::disconnect("/icub/camcalib/left/out", leftCam.inputPortName.c_str());
            }

            if(rightCamOn)
            {
                Network::disconnect("/icub/camcalib/right/out", rightCam.inputPortName.c_str());
            }
        }
        else
        {
            if(leftCamOn)
            {
                Network::disconnect("/icub/cam/left", leftCam.inputPortName.c_str());
            }

            if(rightCamOn)
            {
                Network::disconnect("/icub/cam/right", rightCam.inputPortName.c_str());
            }
        }
    }
}

/*!
 * \brief Thread loop.
 */
void Tracker::run()
{
    //char message[100];

    //showSaturationMask = true;
    currentTarget = 0;
    objectPosition = 0;
    for(int i=0; i<5; i++) oldObjectNo[i] = 0;

    //initlise images
    leftImage = NULL;
    rightImage = NULL;
    oldLeftImage.resize(320,240);
    oldRightImage.resize(320,240);
    leftMotionImage.resize(320,240);
    rightMotionImage.resize(320,240);

 

    //grab memory for salience object detection
    grouping = (int *) malloc((320*240) * sizeof(int));

    for(int i=0; i<320*240; i++)
    {
        grouping[i] = 0;
    }

    //grab memory for salience object bounding boxes
    min_x = (int *) malloc(100 * sizeof(int));
    min_y = (int *) malloc(100 * sizeof(int));
    max_x = (int *) malloc(100 * sizeof(int));
    max_y = (int *) malloc(100 * sizeof(int));
    ignore = (int *) malloc(100 * sizeof(int));
    for(int i=0; i<100; i++)
    {
        min_x[i] = 1000;
        min_y[i] = 1000;
        max_x[i] = -1;
        max_y[i] = -1;
        for(int j=0; j<5; j++)
        {
            oldMinX[i][j] = 0;
            oldMinY[i][j] = 0;
            oldMaxX[i][j] = 0;
            oldMaxY[i][j] = 0;
        }
    }

    running = true;

    while(running)
    {

        if(leftCamOn)
        {
           //read the left and right images from the cam ports
           leftImage = leftCam.inputPort.read(false);

           //send left image to port
           if(leftImage!=NULL)
           {
               findMotion(leftImage, &oldLeftImage, &leftMotionImage);

               //search for unsaturated objects
               findUnsaturatedObjects(leftImage);

               leftCam.outputPort.prepare().copy(*leftImage);
               leftCam.outputPort.write();
               leftMotion.outputPort.prepare().copy(leftMotionImage);
               leftMotion.outputPort.write();
           }
         } // left cam processing

        if(rightCamOn)
        {
           rightImage = rightCam.inputPort.read(false);
           //send right image to port
           if(rightImage!=NULL)
           {
               findMotion(rightImage, &oldRightImage, &rightMotionImage);

               //search for unsaturated objects
               findUnsaturatedObjects(rightImage);

               rightCam.outputPort.prepare().copy(*rightImage);
               rightCam.outputPort.write();
               rightMotion.outputPort.prepare().copy(rightMotionImage);
               rightMotion.outputPort.write();
           }
        } // right cam processing
    }
}

/*!
 * \brief Stops the thread.
 */
void Tracker::stop()
{
    running  = false;
}

/*!
 * \brief Clean up.
 */
void Tracker::clean()
{
    leftCam.inputPort.interrupt();
    leftCam.outputPort.interrupt();
    rightCam.inputPort.interrupt();
    rightCam.outputPort.interrupt();
    leftMotion.inputPort.interrupt();
    leftMotion.outputPort.interrupt();
    rightMotion.inputPort.interrupt();
    rightMotion.outputPort.interrupt();
    outputPort.interrupt();

    disconnectPorts();

    leftCam.inputPort.close();
    leftCam.outputPort.close();
    rightCam.inputPort.close();
    rightCam.outputPort.close();
    leftMotion.inputPort.close();
    leftMotion.outputPort.close();
    rightMotion.inputPort.close();
    rightMotion.outputPort.close();
    outputPort.close();
}

/*!
 * \brief Basic motion finding algorithm which does not take into account the motion of the robot.
 * \note Consecutive images are subtracted and thresholded to create a black and white image showing which areas in an image have changed significantly.
 * \param[in] - image
 * \param[in] - oldImage
 * \param[in] - motionImage
 * \param[out] - motionResult
 */
void Tracker::findMotion(ImageOf<PixelRgb> *image, ImageOf<PixelRgb> *oldImage, ImageOf<PixelRgb> *motionImage)
{
    int x,y;
    int variability = 50;
    int r,b;
    //char message[100];

        for(x=0; x<image->width(); x++)
        {
            for(y=0; y<image->height(); y++)
            {
                if(image->isPixel(x,y) && oldImage->isPixel(x,y) && motionImage->isPixel(x,y))
                {
                    PixelRgb& pixel = image->pixel(x,y);
                    PixelRgb& oldPixel = oldImage->pixel(x,y);
                    PixelRgb& motionPixel = motionImage->pixel(x,y);

                    //compare each pixel between the new and old image, and threshold the absolute difference to generate an motion image
                    if(pixel.r - oldPixel.r > threshold || pixel.r - oldPixel.r < -threshold ||
                       pixel.g - oldPixel.g > threshold || pixel.g - oldPixel.g < -threshold ||
                       pixel.b - oldPixel.b > threshold || pixel.b - oldPixel.b < -threshold)
                    {
                        motionPixel.r = 255;
                        motionPixel.g = 255;
                        motionPixel.b = 255;
                    }
                    else
                    {
                        motionPixel.r = 0;
                        motionPixel.g = 0;
                        motionPixel.b = 0;
                    } // inner if
                } // outer if
            } // y loop
        } // x loop
        myCopyImage(image, oldImage);
}

void Tracker::sendMotionData(int x, int y)
{
    yarp::os::Bottle &b = outputPort.prepare();
    b.clear();
    b.addString("move");
    b.addString("head");
    b.addInt(x);
    b.addInt(y);
    outputPort.write();
}

int Tracker::myMax(int a, int b, int c, int d, int e)
{
    return std::max(std::max(std::max(std::max(a, b), c), d), e);
}

int Tracker::myMin(int a, int b, int c, int d, int e)
{
    return std::min(std::min(std::min(std::min(a, b), c), d), e);
}

/*!
 * \brief Copies one yarp image to another.
 * \param[in] source
 * \param[out] destination
 */
void Tracker::myCopyImage(ImageOf<PixelRgb> *source, ImageOf<PixelRgb> *destination)
{
    int x,y;
    for(x=0; x<source->width(); x++)
    {
        for(y=0; y<source->height(); y++)
        {
            if(source->isPixel(x,y) && destination->isPixel(x,y))
            {
                PixelRgb& sourcePixel = source->pixel(x,y);
                PixelRgb& destinationPixel = destination->pixel(x,y);
                destinationPixel.r = sourcePixel.r;
                destinationPixel.g = sourcePixel.g;
                destinationPixel.b = sourcePixel.b;
            }
        }
    }
}

/*!
 * \brief Copies a yarp image to a vector, or a vector to a yarp image.
 * \param[in] yarpImage
 * \param[in] direction
 * \param[out] vectorImage
 */
void Tracker::myCopyImageToVector(ImageOf<PixelRgb> *yarpImage, int *vectorImage, bool direction)
{
    int x,y;
    if(yarpImage!=NULL)
    {
        for(x=0; x<yarpImage->width(); x++)
        {
            for(y=0; y<yarpImage->height(); y++)
            {
                if(yarpImage->isPixel(x,y))
                {
                    PixelRgb& yarpImagePixel = yarpImage->pixel(x,y);
                    if(direction == false)
                    {
                        vectorImage[x + (y*yarpImage->width()) + (0 * (yarpImage->width() * yarpImage->height()))] = yarpImagePixel.r;
                        vectorImage[x + (y*yarpImage->width()) + (1 * (yarpImage->width() * yarpImage->height()))] = yarpImagePixel.g;
                        vectorImage[x + (y*yarpImage->width()) + (2 * (yarpImage->width() * yarpImage->height()))] = yarpImagePixel.b;
                    }
                    else
                    {
                        yarpImagePixel.r = vectorImage[x + (y*yarpImage->width()) + (0 * (yarpImage->width() * yarpImage->height()))];
                        yarpImagePixel.g = vectorImage[x + (y*yarpImage->width()) + (1 * (yarpImage->width() * yarpImage->height()))];
                        yarpImagePixel.b = vectorImage[x + (y*yarpImage->width()) + (2 * (yarpImage->width() * yarpImage->height()))];
                    }
                }
            }
        }
    }
}

/**
*@brief     This function first converts the whole image from RGB to HSV colour and then finds connected regions of pixels with high saturation (i.e. ignores white tables and more) each region is then seen as an object with a bounding box, the HSV colour profile of each bounding box is then set in 36 bins and normalized
*@param[out] n - the number of objects found
*/
int Tracker::findUnsaturatedObjects(ImageOf<PixelRgb> *image)
{
    float washout_threshold = saturation;
    float RGBmin, RGBmax, delta;
    float s = 0;

    for(int i=0; i<100; i++) {    //min_x & _y and max_x & _y provide the bounding box around areas of non-washed-out visual items (assumes the table is washed out e.g. white)
        min_x[i] = 1000;    //set to a very large value
        min_y[i] = 1000;
        max_x[i] = -1;      //set to a very small value
        max_y[i] = -1;
    }

    //filter out unsaturated colours to make an intensity matrix
    for(int x = 0; x < image->width(); x++) {
        for(int y = 0; y < image->height(); y++) {
            if(image->isPixel(x,y))
            {
                PixelRgb& pixel = image->pixel(x,y);
                //find the saturation value of each pixel
                RGBmin = std::min( (float)pixel.r/255, std::min( (float)pixel.g/255, (float)pixel.b/255 ));
                RGBmax = std::max( (float)pixel.r/255, std::max( (float)pixel.g/255, (float)pixel.b/255 ));
                delta = RGBmax - RGBmin;
                if( RGBmax != 0 )   s = delta / RGBmax;		// s
                else                s = 0;

                if(s > washout_threshold) {
                    grouping[x + (y*image->width())] = int(s*255);
                }
                else {
                    grouping[x + (y*image->width())] = 0;
                    if(saturationMask)
                    {
                        pixel.r = 0;
                        pixel.g = 0;
                        pixel.b = 0;
                    }
                }
            }
        }
    }

    //now search for connected pixels of > 0 intensity... This sets the bounding boxes and number of objects found
    return connectedSearch(image, image->width(), image->height());
}

/**
*@brief     finds connected pixels in an intensity map
*@param[out] n - the number of objects found
*/
int Tracker::connectedSearch(ImageOf<PixelRgb> *image, int imageWidth, int imageHeight)
{
    int x,y,n;
    int minSize = 10;
    int maxSize = 200;
    int variability = 5;
    int numIgnored = 0;
    char message[10000];
    n = 0;

    for(int i=0; i<100; i++)
    {
        ignore[i] = 0;
    }

    //search for areas of connected pixels within the size constraints
    for(x=0; x<imageWidth; x++)
    {
        for(y=0; y<imageHeight; y++)
        {
            if(grouping[x + (y*imageWidth)] > 0)
            {
                //is there an object out there?
                connectedScan(n, x, y, imageWidth, imageHeight, 0, maxSize);
                //connected scan has now found the full region of saturated pixels connected to this pixel so now we check how big it is
                if((max_x[n] - min_x[n]) > minSize && (max_x[n] - min_x[n]) < maxSize && (max_y[n] - min_y[n]) > minSize && (max_y[n] - min_y[n]) < maxSize && n<(100-1))
                {                    
                    //and is it stable?? - check to see if this object matches any of the objects from the previous trials...
                    int stable = 0;

                    sprintf(message,"Object %d is %d %d - %d %d", n, max_x[n], max_y[n], min_x[n], min_y[n]);

                    for(int t=0; t<5; t++)
                    {

                        //sprintf(message, "%s\ntime %d", message, t);

                        for(int oldObject=0; oldObject<oldObjectNo[t]; oldObject++)
                        {
                            //sprintf(message, "%s\n   compared to %d at %d %d - %d %d", message, oldObject, oldMaxX[oldObject][t], oldMaxY[oldObject][t], oldMinX[oldObject][t], oldMinY[oldObject][t]);

                            if( (oldMaxX[oldObject][t] > max_x[n] - variability) && (oldMaxX[oldObject][t] < max_x[n] + variability) &&
                                (oldMaxY[oldObject][t] > max_y[n] - variability) && (oldMaxY[oldObject][t] < max_y[n] + variability) &&
                                (oldMinX[oldObject][t] > min_x[n] - variability) && (oldMinX[oldObject][t] < min_x[n] + variability) &&
                                (oldMinY[oldObject][t] > min_y[n] - variability) && (oldMinY[oldObject][t] < min_y[n] + variability) )
                            {
                                stable ++;
                                //sprintf(message, "%s MATCH", message);
                            }
                        }
                    }

                    //sprintf(message,"Object %d is %d %d - %d %d ObjPos %d stability = %d", n, max_x[n], max_y[n], min_x[n], min_y[n], objectPosition, stable);

                    if(stable < 4 && strictObjectDetection) //note there are 5 time positions, but one of these may be partially overwritten with objects just found
                    {
                        ignore[n] = 1;
                        numIgnored ++;
                    }
                    else
                    {
                        drawBox(image, min_x[n], max_x[n], min_y[n], max_y[n], 255, 0, 0);
                    }

                    //copy new to old
                    oldMaxX[n][objectPosition] = max_x[n];
                    oldMaxY[n][objectPosition] = max_y[n];
                    oldMinX[n][objectPosition] = min_x[n];
                    oldMinY[n][objectPosition] = min_y[n];
                    //increment n
                    n ++;
                }
                else {
                    //the found object was either too small or too big so wipe it and carry on looking
                    min_x[n] = 1000;
                    min_y[n] = 1000;
                    max_x[n] = -1;
                    max_y[n] = -1;
                }
            }
        }
    }

    //keep a record of how many objects there are...
    oldObjectNo[objectPosition] = n;

    //increment the object position for previous objects
    objectPosition ++;
    if(objectPosition > 4) objectPosition = 0;

    //send object data
    if(n - numIgnored > 0) sendObjectData(n);

    return n - numIgnored;
}

void Tracker::sendObjectData(int n)
{
    yarp::os::Bottle &output = outputPort.prepare();
    output.clear();
    output.addString("object");
    for(int i=0; i<n; i++)
    {
        if(!ignore[i]) {
            output.addInt(min_x[i]);
            output.addInt(min_y[i]);
            output.addInt(max_x[i]);
            output.addInt(max_y[i]);
        }
    }
    outputPort.write();
}

/**
*@brief     finds connected pixels in the intensity map (recursive)
*@param[in] n - the number of the current connected area
*@param[in] pixel_x - pixel pos
*@param[in] pixel_y - pixel pos
*/
void Tracker::connectedScan(int n, int x, int y, int imageWidth, int imageHeight, int loops, int maxSize)
{
    int scan_size = 5;

    int lmin_x = x; // - scan_size;
    if(lmin_x < 1) lmin_x = 1;

    int lmax_x = x + scan_size;
    if(lmax_x > imageWidth-1) lmax_x = imageWidth-1;

    int lmin_y = y - scan_size;
    if(lmin_y < 1) lmin_y = 1;

    int lmax_y = y + scan_size;
    if(lmax_y > imageHeight-1) lmax_y = imageHeight-1;

    //remove current pixel
    grouping[x + (y*imageWidth)] = 0;

    //work out the boundaries of the object
    if(x < min_x[n]) min_x[n] = x;
    if(y < min_y[n]) min_y[n] = y;
    if(x > max_x[n]) max_x[n] = x;
    if(y > max_y[n]) max_y[n] = y;

    //this outer loop is for MAC OSX due to the stack size for recursion, remove it for linux use for better results
//    if((max_x[n] - min_x[n]) < maxSize+1 && (max_y[n] - min_y[n]) < maxSize+1) {
        for(int scan_x = lmin_x; scan_x < lmax_x; scan_x++)
        {
            for(int scan_y = lmin_y; scan_y < lmax_y; scan_y++)
            {
                if(grouping[scan_x + (scan_y*imageWidth)] > 0)
                {
                    //printf("%d,%d\n",scan_x, scan_y);
                    if(loops < 100000) connectedScan(n, scan_x, scan_y, imageWidth, imageHeight, loops++, maxSize);
                }
            }
        }
//    }
}

void Tracker::changePixel(ImageOf<PixelRgb> *image, int x, int y, int r, int g, int b)
{
    if(image->isPixel(x,y))
    {
        PixelRgb& pixel = image->pixel(x,y);
        pixel.r = r;
        pixel.g = g;
        pixel.b = b;
    }
}

/*!
 * \brief Draw a cross on an image at target location and of colour.
 */
void Tracker::drawBox(ImageOf<PixelRgb> *image, int Xmin, int Xmax, int Ymin, int Ymax, int r, int g, int b)
{
    if(Xmin < 0) Xmin = 0;
    if(Ymin < 0) Ymin = 0;
    if(Xmax > 319) Xmax = 319;
    if(Ymax > 239) Ymax = 239;
    //draw horizontal lines
    for(int x=Xmin; x<Xmax; x++)
    {
        changePixel(image, x, Ymin, r, g, b);
        changePixel(image, x, Ymax, r, g, b);
    }
    //draw vertical lines
    for(int y=Ymin+1; y<Ymax-1; y++)
    {
        changePixel(image, Xmin, y, r, g, b);
        changePixel(image, Xmax, y, r, g, b);
    }
}

/*!
 * \brief Sets sensitivity treshold.
 * \param[in] thresholdValue
 */
void Tracker::setThreshold(int thresholdValue)
{
    threshold = thresholdValue;
}

/*!
 * \brief Sets saturation treshold.
 * \param[in] saturationValue
 */
void Tracker::setSaturation(int saturationValue)
{
    char message[100];
    saturation = (float)saturationValue/100;
    sprintf(message, "saturation changed to %f", saturation);
}

/*!
 * \brief Sets saturation mask to visible or not.
 * \param[in] state
 */
void Tracker::setSaturationMask(bool active)
{
    saturationMask = active;
}

/*!
 * \brief Sets strict object detection.
 * \param[in] state
 */
void Tracker::setStrictObjectDetection(bool active)
{
    strictObjectDetection = active;
}

/*!
 * \brief Sets Calibrated Cameras or uncalibrated cameras.
 * \param[in] state
 */
void Tracker::setCamCalib(bool active)
{
    camCalib = active;
}

/*!
 * \brief Switches the right camera on or off.
 * \param[in] state
 */
void Tracker::setRightCam(bool active)
{
    rightCamOn = active;
}

/*!
 * \brief Switches the left camera on or off.
 * \param[in] state
 */
void Tracker::setLeftCam(bool active)
{
    leftCamOn = active;
}

/*!
 * \brief Sets simulation mode.
 * \param[in] simulationMode
 */
void Tracker::setSimulationMode(bool active)
{
    simulationMode = active;
}

/*!
 * \brief Gets sensitivity threshold.
 */
int Tracker::getThreshold()
{
    return threshold;
}

/*!
 * \brief Gets saturation threshold.
 */
int Tracker::getSaturation()
{
    return int(saturation*100);
}

/*!
 * \brief Gets simulation mode.
 */
bool Tracker::getSimulationMode()
{
    return simulationMode;
}

/*!
 * \brief gets saturation mask to visible or not.
 */
bool Tracker::getSaturationMask()
{
    return saturationMask;
}

/*!
 * \brief gets strict object detection.
 */
bool Tracker::getStrictObjectDetection()
{
    return strictObjectDetection;
}

/*!
 * \brief gets camCalib.
 */
bool Tracker::getCamCalib()
{
    return camCalib;
}

/*!
 * \brief gets rightCamOn.
 */
bool Tracker::getRightCam()
{
    return rightCamOn;
}

/*!

 * \brief gets leftCamOn.
 */
bool Tracker::getLeftCam()
{
    return leftCamOn;
}

}
