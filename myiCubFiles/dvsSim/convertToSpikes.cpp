#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string>
//#include <random>
  /* Get all OS and signal processing YARP classes */
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

using namespace yarp::os;
using namespace yarp::sig;


int main(int nargin, char** argv) {

//	std::default_random_engine generator;
//	std::normal_distribution<double> distribution(0.0, 10);
	unsigned long int initTime = Time::now();
	std::string handPort_Value;
	std::string handCam;
	std::string dvsImagePort;
	std::string grayImagePort;

//	std::string handPort_Value;
	std::string localHandCam;
	std::string localDVSImagePort;
	std::string localGrayImagePort;

	std::string temp;

	

    if (nargin > 1){
	temp = argv[1];
//	handPort_Value = "/icubSim/cam/" + temp;
//	handCam = "/" + temp + "Cam";
//	dvsImagePort = "/" + temp + "DVSImage";
//	grayImagePort = "/" + temp + "GrayImage";
//
//	localHandCam = "/local" + temp + "Cam";
//	localDVSImagePort = "/local" + temp + "DVSImage";
//	localGrayImagePort = "/local" + temp + "GrayImage";
	
	}
    else{
	temp = "left";
//	handPort_Value = "/icubSim/cam/" + temp;
//	handCam = "/" + temp + "Cam";
//	dvsImagePort = "/" + temp + "DVSImage";
//	grayImagePort = "/" + temp + "GrayImage";
//
//	localHandCam = "/local" + temp + "Cam";
//	localDVSImagePort = "/local" + temp + "DVSImage";
//	localGrayImagePort = "/local" + temp + "GrayImage";

	}
	handPort_Value = "/icubSim/cam/" + temp;// + "/fovea";
	handCam = "/" + temp + "Cam";
	dvsImagePort = "/" + temp + "DVSImage";
	grayImagePort = "/" + temp + "GrayImage";

	localHandCam = "/local" + temp + "Cam";
	localDVSImagePort = "/local" + temp + "DVSImage";
	localGrayImagePort = "/local" + temp + "GrayImage";

    Network yarp; // set up yarp


    BufferedPort<ImageOf<PixelRgb> > imagePort;  // make a port for reading images
    BufferedPort<ImageOf<PixelMono> > imageOutGray;
    BufferedPort<Bottle> simDVSEvents;
    Port imageOutPort;
    Port imageOutDVSPort;

// 	yarpview ("/leftCam");

    imagePort.open(localHandCam.c_str());  // give the port a name
    imageOutGray.open("/tutorial/image/gray:o");  // give the port a name
    imageOutPort.open(localGrayImagePort.c_str());
    imageOutDVSPort.open(localDVSImagePort.c_str());
    simDVSEvents.open("/dvsSIM/eventBottle:o");

    printf("%s, %s \n", handPort_Value.c_str(), handCam.c_str());
    Network::connect(handPort_Value.c_str(), localHandCam.c_str());
    Network::connect(localGrayImagePort.c_str(), grayImagePort.c_str());
    Network::connect(localDVSImagePort.c_str(), dvsImagePort.c_str());
    Network::connect(handPort_Value.c_str(), handCam.c_str());

    ImageOf<PixelMono>  prevImage;
    ImageOf<PixelMono>  dvsImage;
    ImageOf<PixelMono>  grayLogImage;
    // prevImage = imageOutGray.prepare();
	
    unsigned int sizeOfImageX = 320;
    unsigned int sizeOfImageY = 240;	
    dvsImage.resize(sizeOfImageX,sizeOfImageY);
    prevImage.resize(sizeOfImageX,sizeOfImageY);
	grayLogImage.resize(sizeOfImageX,sizeOfImageY);
    	bool first = true;
	unsigned long int timeStart = Time::now();

    while (true) {
	
      ImageOf<PixelRgb> *image = imagePort.read();  // read an image
      srand(time(0));
      if (image!=NULL) { // check we actually got something
	prevImage = imageOutGray.prepare();
	prevImage.resize(image->width(), image->height());
	dvsImage.resize(image->width(), image->height());
	grayLogImage.resize(image->width(), image->height());
	unsigned long int t = Time::now() - timeStart;
	//	printf("Linked image variable to port\n");
	if(first){
	  printf("input image size: %d x %d\n", image->width(), image->height());
	  // int ptr = 0;
	  for(int x=0; x < image->width(); x++){
	    for(int y=0; y < image->height(); y++){
		    PixelRgb& pixel = image->pixel(x,y);
		    double grayVal = pixel.r*0.2126 + pixel.g*0.7152 + pixel.b*0.0722;
		    //printf("%d %d \n", x, y);
		    prevImage.pixel(x,y) = (int)log(grayVal);
		    grayLogImage.pixel(x,y) = 100*(int)log(grayVal);
		    //  v[ptr++] = grayVal;
		  }
		}
	  first = false;
	}
	else{
	  for(int x=0; x < image->width(); x++){
	    for(int y=0; y < image->height(); y++){
	    PixelRgb& pixel = image->pixel(x,y);

	    double grayVal = (pixel.r*0.2126 + pixel.g*0.7152 + pixel.b*0.0722);// + (rand()%2-1);
	    int present = (int)log(grayVal);
//			grayVal = temp;
//			printf("%lf %lf\n",(rand()%10), grayVal);

	    int difference = 100*((double)prevImage.pixel(x,y)-present); //+(rand()%1-0.5);

	    //printf("%lf %d %d\n", (double)prevImage.pixel(x,y), present, difference);
		    //   /*
	    if(difference > 5){
	      dvsImage.pixel(x,y) = 255;
		Bottle& eventsDVS = simDVSEvents.prepare();
		eventsDVS.clear();
	   //   eventsDVS.addString("event");
	      eventsDVS.addInt(x);
              eventsDVS.addInt(y);
              eventsDVS.addInt(1);
		eventsDVS.addDouble(initTime);
	      eventsDVS.addDouble(t);
		
		simDVSEvents.write();
	    }
	    else if(difference < -50){
	//		printf("%d ", difference);
	      dvsImage.pixel(x,y) = 0;
		Bottle& eventsDVS = simDVSEvents.prepare();
		eventsDVS.clear();
		eventsDVS.addInt(x);
              eventsDVS.addInt(y);
              eventsDVS.addInt(0);
		eventsDVS.addDouble(initTime);
	      eventsDVS.addDouble(t);
		
		simDVSEvents.write();
	    }
	    else{
		dvsImage.pixel(x,y) = 127;
	//      eventsDVS.addString("event");
	//      eventsDVS.addInt(x);
        //      eventsDVS.addInt(y);
        //      eventsDVS.addInt(1);
	//      eventsDVS.addInt(t);
			}
		    //  */
		    	//	    dvsImage.pixel(x,y) = 127+difference;

	    prevImage.pixel(x,y) = (int)log(grayVal);
	    grayLogImage.pixel(x,y) = 100*(int)log(grayVal);
	  }
	}
	}

	//	printf("Writing to port\n");
//	if(imageOutGray.getOutputCount())
//	imageOutGray.write(true);
	
	printf("Size of image written: %d \n", grayLogImage.getPixelSize());
	imageOutPort.write(grayLogImage);
	imageOutDVSPort.write(dvsImage);
	printf("Written to port\n");


	//	printf("We got an image of size %dx%d\n", image->width(), image->height());
      }
    }
    return 0;
}
