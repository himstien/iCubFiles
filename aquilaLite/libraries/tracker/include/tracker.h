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

#ifndef AQUILA_LITE_IMAGE_LIB_H
#define AQUILA_LITE_IMAGE_LIB_H

#include <string>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

using namespace yarp::os;
using namespace yarp::sig;

namespace aquilatracker
{
class Tracker : public yarp::os::Thread
{

public:
    Tracker();
    Tracker(int thresh, float sat, bool satmask, bool simmode, bool strictObj, bool calib, bool rightcam, bool leftcam);
    ~Tracker();

private:
    BufferedPort<Bottle> outputPort;

    int threshold;
    float saturation;
    bool simulationMode;
    bool running;
    bool saturationMask;
    bool strictObjectDetection;
    bool camCalib;
    bool rightCamOn;
    bool leftCamOn;

    //images
    ImageOf<PixelRgb> *leftImage;
    ImageOf<PixelRgb> *rightImage;
    ImageOf<PixelRgb> oldLeftImage;
    ImageOf<PixelRgb> oldRightImage;
    ImageOf<PixelRgb> leftMotionImage;
    ImageOf<PixelRgb> rightMotionImage;

    struct Image
    {
        BufferedPort<ImageOf<PixelRgb> > inputPort;
        BufferedPort<ImageOf<PixelRgb> > outputPort;
        std::string inputPortName;
        std::string outputPortName;
    };

    Image leftCam;
    Image rightCam;
    Image leftMotion;
    Image rightMotion;

    std::string trackerOutputPortName;

    //intensity based object pointers
    int *grouping;
    int *min_x;
    int *min_y;
    int *max_x;
    int *max_y;
    int oldMinX[100][5];
    int oldMinY[100][5];
    int oldMaxX[100][5];
    int oldMaxY[100][5];
    int *ignore;
    int oldObjectNo[5];
    int objectPosition;
    int target[2][10];
    int currentTarget;

    void run();
    void sendMotionData(int x, int y);
    void sendObjectData(int n);
    void findMotion(ImageOf<PixelRgb> *image, ImageOf<PixelRgb> *oldImage, ImageOf<PixelRgb> *motionImage);
    void myCopyImage(ImageOf<PixelRgb> *source, ImageOf<PixelRgb> *destination);
    void myCopyImageToVector(ImageOf<PixelRgb> *source, int *destination, bool direction);
    void changePixel(ImageOf<PixelRgb> *image, int x, int y, int r, int g, int b);
    void drawBox(ImageOf<PixelRgb> *image, int Xmin, int Xmax, int Ymin, int Ymax, int r, int g, int b);
    void connectedScan(int n, int x, int y, int imageWidth, int imageHeight, int loops, int maxSize);
    int  findUnsaturatedObjects(ImageOf<PixelRgb> *image);
    int  connectedSearch(ImageOf<PixelRgb> *image, int imageWidth, int imageHeight);
    int  myMax(int a, int b, int c, int d, int e);
    int  myMin(int a, int b, int c, int d, int e);

public:

    void clean();
    void connectPorts();
    void disconnectPorts();
    bool openPorts(std::string portPrefix);

    void stop();

    void setThreshold(int thresholdValue);
    void setSaturation(int saturationValue);
    void setSimulationMode(bool active);
    void setSaturationMask(bool active);
    void setStrictObjectDetection(bool active);
    void setCamCalib(bool active);
    void setRightCam(bool active);
    void setLeftCam(bool active);


    int  getThreshold();
    int  getSaturation();
    bool getSimulationMode();
    bool getSaturationMask();
    bool getStrictObjectDetection();
    bool getCamCalib();
    bool getRightCam();
    bool getLeftCam();

};
}
#endif//AQUILA_LITE_IMAGE_LIB_H
