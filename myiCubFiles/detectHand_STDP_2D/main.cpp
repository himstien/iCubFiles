/////////// Project: detect hand with STDP 2D
// STDP 2D DVS and HAND

// *** include standard header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include <signal.h>

// *** include yarp headers
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>

//#include "IzhikevicNeuron.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;

Vector vecImageWeights;

void handleSignals(int sig)
{
	cout << "Signal " << sig << " caught " << endl;

	ofstream file_weights;
	file_weights.open("deleteThisFile.dat");
	cout << "Writing to file with size of vector: "<< vecImageWeights.size() << endl;
	for (int i=0; i < 320; i++)
	{
//cout << i << endl;
		for(int j=0; j<240; j++)
		{
			for(int k=0; k<60 ; k++)
			{
				for(int l=0; l<60 ; l++)
				{
					if(vecImageWeights((j*320+i)+(l*60+k)*60*60) > 0.0001)
					{

char *buffer = new char[6];
*buffer++=i;
*buffer++=j;
*buffer++=k;
*buffer++=l;
//cout << i << " " << j << " " << k << " " << l << endl;
*buffer++=vecImageWeights((j*320+i)+(l*60+k)*60*60);
*buffer++ = ('\n');

file_weights.write(buffer, 6);

//delete buffer;

//cout << vecImageWeights((j*320+i)+(l*60+k)*60*60)<< endl;
//file_weights.write() << i << " " << j << " " << k << " " << l << " " << vecImageWeights((j*320+i)+(l*60+k)*60*60) << endl;
}
				}
			}
//		file_weights << endl;
		}
	}
file_weights.close();	
cout << "Exiting " << endl;
::exit(int(1));

}



double updateWeights(int time1, int time2)
{
    //double delTime = abs(delT);
    double sigma = 1000.0;
    double delT = abs((double)time1 - (double)time2);

	    
	double A = 1; //(1/(sigma*sqrt(2*3.14152)));

    double inFunc = (delT*delT)/2*(sigma*sigma);

    double G = A*exp(-inFunc);

    //cout << G-20 << endl;

    return (G);

};


int main(int argc, char** argv)
{
//	signal(yarp::os::YARP_SIGABRT, &handleSignals);
	signal(YARP_SIGTERM, &handleSignals);
	signal(YARP_SIGINT, &handleSignals);
	unsigned long int initTimeSTDP = Time::now();
    bool verbose = false;

    ofstream file_outFile, file_writeData;
    Network yarp;
	
	int xMin, yMin, zMin, xMax, yMax, zMax;
	xMin=-45; xMax=10; yMin=-8; yMax=40; zMin=-33; zMax=-7;
	int numSizeSensorX = 60; //xMax-xMin+10;
	int numSizeSensorY = 60; //yMax-yMin+10;
	cout << "numX Y: " << numSizeSensorX << " " << numSizeSensorY << endl;

//	ImageOf<PixelInt> imageWeights;
//	imageWeights.resize(320*240, numSizeSensorX*numSizeSensorY);
	
	vecImageWeights.resize(320*240*numSizeSensorX*numSizeSensorY);

// **** Pre-known port names... TODO: Change code to get port names automatically ****
    string portname_dvsSim = "/dvsSIM/eventBottle:o";
    string portname_readDVSSim = "/dvsSimRead:i";

    string portname_handNeuron = "/leftHandPoseNeurons";
    string portname_readHandNeuron = "/dvsHandNeuronRead:i";

    //string portname_localyarpview = "/viewer/temp:i";
    string portname_localyarpImage = "/viewer/imageHandDetect:o";
	string portname_imageWeightsOut = "/viewer/imageHandWeights:o";	

	ImageOf<PixelInt> imageHandLayer;
	ImageOf<PixelInt> imageToSend;
//	imageHandLayer.resize(256, 256);
	imageToSend.resize(numSizeSensorX, numSizeSensorY);
	Port imageHandPort;
	Port imageWeightsPort;
	imageHandPort.open(portname_localyarpImage.c_str());
	imageWeightsPort.open(portname_imageWeightsOut.c_str());

	Network::connect(portname_localyarpImage.c_str(), "/imageHandLayer");
	Network::connect(portname_imageWeightsOut.c_str(), "/imageHandWeights");

    int sizeData;

// Declare image to connect with yarpviewer

// Declare bottles and eventBottles
    //Bottle *bottle_inputDVSData = new Bottle; //, *dvsRead;


// Declare and open buffered ports for receiving Tactile and DVS events
    BufferedPort<Bottle> bufport_dvsIn;
    bool dvsPortOk = bufport_dvsIn.open(portname_readDVSSim.c_str());

    BufferedPort<Bottle> bufport_handSignalIn;
    //Bottle *bottle_handPoseData;// = new Bottle;
    bool portOpenOk = bufport_handSignalIn.open(portname_readHandNeuron.c_str());

   // yarpview bufport_imageView;
   // bool portImageOk = bufport_imageView.open(portname_localyarpview);

    if (!dvsPortOk || !portOpenOk){ cout << "Error opening port! Check yarp network status!!!" << endl; return(1);}
	cout << "DVS port open? " << dvsPortOk << endl;

    if(!yarp.exists(portname_dvsSim.c_str()))
    {
        cout << "Port " << portname_dvsSim.c_str() << " not open! " << endl;
        return(1);
    }

    if( !yarp.exists(portname_handNeuron.c_str()) )
    {
        cout << "Port " << portname_handNeuron.c_str() << " not open! " << endl;
        return(1);
    }

        cout << "Trying to connect ports..." << endl;
        bool  connectSuccess = true;
        connectSuccess = Network::connect(portname_handNeuron.c_str(), portname_readHandNeuron.c_str());
        connectSuccess = connectSuccess & Network::connect(portname_dvsSim.c_str(), portname_readDVSSim.c_str());
        if (!connectSuccess) { cout << "Could not connect ports! Something went wrong! Check if YARP and iCub_SIM are running." << endl; return(1);}


// declare variables for main loop
    unsigned int totalEvents = 0; // count for number of events received from aexGrabber
    bool AE_first = false; // To make sure that the events in the file are written in the format: [X Y time]
    double encoderPos = 0; // Get position of eye horizontal motion

 //   poscntrl_head->positionMove(4, -5.0); // Move eye in horizontal direction to value -5

// main loop for reading events from aexGrabber and save into pixel vectors
    long int lastTimeStamp = 0;
    long int firstTimeStamp = 0;
    long int frameTimeStamp = 0;
    long int latestTimeStamp = 0;
    long int motorSpikeTime = 0;
    int currentTime = 0;


    bool firstEvent=false;

    unsigned int TIMEINLOOP = 0;

    //verbose=true;
   
	for (int i=0; i < numSizeSensorX; i++)
	{
		for (int j=0; j < numSizeSensorY; j++)
		{
//			imageHandLayer.pixel(i,j) = 0;
			imageToSend.pixel(i,j) = 127;
	
		}
	}

	long int tHand;	int polarity; int y; int x;
	long int tHandPrev; long int time; long int initTime;

	int indexDVS, indexHand;


    while(true){	
    if(connectSuccess && yarp.exists(portname_handNeuron.c_str()) && yarp.exists(portname_dvsSim.c_str()))
    {
//		for (int i=0; i < 256; i++)
//		{
//		for (int j=0; j < numSizeSensorY; j++)
//			{
//				imageToSend.pixel(i,j) = 0;
//			}
//		}
	

        Bottle *inputDVSEvent = bufport_dvsIn.read();

        Bottle *inputHandSignal = bufport_handSignalIn.read();

//cout << "HandSignal: " << (*inputHandSignal).isNull() << " DVS: " << (*inputDVSEvent).isNull() << endl;
	

 //       if ( !(*inputDVSEvent).isNull() )
	{

	int currentTime = Time::now();	
	time = ((*inputDVSEvent).pop()).asInt();
	initTime = ((*inputDVSEvent).pop()).asInt();
	polarity = ((*inputDVSEvent).pop()).asInt();
	y = ((*inputDVSEvent).pop()).asInt();
	x = ((*inputDVSEvent).pop()).asInt();

	//	if(  !(*inputHandSignal).isNull() )
	//	{
			tHand = ((*inputHandSignal).pop()).asInt();
			//if(tHand > 0){
				int xHand = ((*inputHandSignal).pop()).asInt();
				int yHand = ((*inputHandSignal).pop()).asInt();
		indexDVS = y*320 + x;
		indexHand = yHand*60 + xHand;

		imageToSend.pixel(xHand, yHand) = 127+127*exp(-abs(time-tHand));
		
		if ( abs(time-tHand) > 5 )
		{
		vecImageWeights(indexDVS+60*60*indexHand) = vecImageWeights(indexDVS+60*60*indexHand) + exp(-abs(time-tHand));
		}
		else
		{
		vecImageWeights(indexDVS+60*60*indexHand) = -5; //vecImageWeights(indexDVS+60*60*indexHand) + exp(-abs(time-tHand));
		}
		
cout << time << " " << tHand << " " << currentTime << " " << vecImageWeights(indexDVS+60*60*indexHand) << " " << exp(-abs(time-tHand)/2) << endl;

		
//		imageWeights.pixel(indexDVS, indexHand) = vecImageWeights(indexDVS*60*60+indexHand);
	
//cout << imageWeights.pixel(indexDVS, indexHand) << endl;
			//}
			//else {
			//	int xHand = ((*inputHandSignal).pop()).asInt();
			//	int yHand = ((*inputHandSignal).pop()).asInt();
			//	imageToSend.pixel(xHand, yHand) = exp(-abs(Time::now()-tHand)/100);
			//	}

			//long int initHand = ((*inputHandSignal).pop()).asInt();	
	//		tHandPrev = tHand;
	//	}

	}
	}
	else
	{
	    connectSuccess = Network::connect(portname_handNeuron.c_str(), portname_readHandNeuron.c_str());
	    connectSuccess = connectSuccess & Network::connect(portname_dvsSim.c_str(), portname_readDVSSim.c_str());
	}
	//cout << "Sending images" << endl;
	imageHandPort.write(imageToSend);
//	imageWeightsPort.write(imageWeights);	
	//cout << "Sending images done" << endl;
    } // end of while

}	








/*
    for (int frames = 0; frames < EVENTBOTTLESTOREAD; frames++)
    {
        totalEvents = 0;
        currentTime = 0;
        firstEvent = false;

  //  moveEyes = (bool) round(frames%2);
        if(verbose) cout << "Move command " << moveEyes << endl;

//int window = 8;
        bool notmoving=NULL;

        while(yarp.exists(portname_aexGrabber.c_str()) && totalEvents <= TIMEINLOOP)
        { // Do if aexGrabber port exists and a given number of totalEvents

                                                                              // are not read yet
     //   if(currentTime > TIMEINLOOP/2) {moveEyes = false; } // Move eye for first half of events......



            if(verbose) cout << " Reading from eventBottle" << endl;
            eventbottle_dvsRead = bufport_dvsIn.read();         // read data from DVS (aexGrabber/eventBottle)
        //inputData = inPort.read(false);                   // read from left hand tactile sensor
            if(verbose) cout << (*eventbottle_dvsRead).get_sizeOfBottle() << endl;

            notmoving = true;
            bool updateWeightsFlag = false;

            if ( (*eventbottle_dvsRead).get_sizeOfBottle() > 0)
            {

                storeDVSX.resize((*eventbottle_dvsRead).get_sizeOfBottle());
                storeDVSY.resize((*eventbottle_dvsRead).get_sizeOfBottle());
                storeDVST.resize((*eventbottle_dvsRead).get_sizeOfBottle());
            /*        Bottle *bottle_handPoseData = bufport_leftArmNeuron.read(false);
                    while (bottle_handPoseData==NULL){
                        bottle_handPoseData = bufport_leftArmNeuron.read(false);
                    }
                    cout << (*bottle_handPoseData).toString().c_str() << endl;

                    if((*bottle_handPoseData).get(0) == 20 && (*bottle_handPoseData).get(1) == 29)
                        updateWeightsFlag = true;


                    delete bottle_handPoseData;
            /
//if(verbose) cout << "Entering the loop for updating pixel probs" << endl;
                bottle_inputDVSData = (*eventbottle_dvsRead).get_packet();
         //   cout << "Testing function: inputData : " << (*inputDVSData).size() << endl;
              //  eEventQueue q; // = new eEventQueue;
              //  (*unmask_events).unmaskData(bottle_inputDVSData, &q); // Use the already built unmask class to unmask the bottle into aer struct q

                int thisLoopTimeStart=0;
                int thisLoopTime = 0;

                int X=0,Y=0;
                int clustX=0, clustY=0;
                int *clust;
                int counterXY = 0;
                int counterT = 0;
                for (int i = size_of_data; i >= 0; i--)
                {

		 	X = bottle_inputDVSData.data[0];
			Y = bottle_inputDVSData.data[1];
			P = bottle_inputDVSData.data[2];
			T = bottle_inputDVSData.data[3];

              //  cout << i << endl;
                   }
                for (int n=0; n < 1; n++) //storeDVSX.size()
                {
                    int dvsPixeln = storeDVSX.at(n)*128+storeDVSY.at(n);
                    for (int m=1; m < storeDVSX.size(); m++)
                    {
                        int dvsPixelm = storeDVSX.at(m)*128+storeDVSY.at(m);
                        int toUpdate = dvsPixeln*numRowsSensor*numRowsSensor + dvsPixelm;
                        if (vector_Weights.at(toUpdate) < 1 & vector_Weights.at(toUpdate) > -1)
                        {
                            vector_Weights.at(toUpdate) = vector_Weights.at(toUpdate) + updateWeights(storeDVST.at(n), storeDVST.at(m));
                        }
                    }
                }
                storeDVSX.clear(); storeDVSY.clear(); storeDVST.clear();
        } /* End of processing with data  //cout << "end of event bottle data reading" << endl;
    } /* End of number of frames /
    file_outFile.close();
    bufport_dvsIn.close();

    driver_leftArmCntrl.close();

    delete bottle_inputDVSData; //, *dvsRead;
    delete eventbottle_dvsRead;
    //delete bottle_handPoseData;

    return 0;
}



*/
