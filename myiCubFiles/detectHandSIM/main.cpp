
//////// Project name: detectHandSim
// *** include standard header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

// *** include yarp headers
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>


using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;



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
	unsigned long int initTimeSTDP = Time::now();
    bool verbose = false;

    ofstream file_outFile, file_writeData;
    Network yarp;


    int numSizeSensorX = 320;
    int numSizeSensorY = 240;

// **** Pre-known port names... TODO: Change code to get port names automatically ****
    string portname_dvsSim = "/dvsSIM/eventBottle:o";
    string portname_readDVSSim = "/dvsSimRead1:i";

    string portname_handNeuron = "/local/handNeurons";
    string portname_readHandNeuron = "/dvsHandNeuronRead1:i";

    //string portname_localyarpview = "/viewer/temp:i";
    string portname_localyarpImage = "/viewer/imageHandDetect1:o";

	string portname_HandVelocity = "/local/handVelocity:i";
	string portname_readHandVelocity = "/leftHandVelocity";



	Vector handPixels;

	ImageOf<PixelInt> imageHandDetect;
	ImageOf<PixelMono> imageToSend;
	imageHandDetect.resize(numSizeSensorX, numSizeSensorY);
	imageToSend.resize(numSizeSensorX, numSizeSensorY);
	Port imageHandPort;
	imageHandPort.open(portname_localyarpImage.c_str());
	Network::connect(portname_localyarpImage.c_str(), "/imageHandLocation");
    int sizeData;

// Declare image to connect with yarpviewer

// Declare bottles and eventBottles
    //Bottle *bottle_inputDVSData = new Bottle; //, *dvsRead;


// Declare and open buffered ports for receiving Tactile and DVS events
    BufferedPort<Bottle> bufport_dvsIn;
    bool dvsPortOk = bufport_dvsIn.open(portname_readDVSSim.c_str());

    BufferedPort<Bottle> bufport_handVelocityIn;
    dvsPortOk = bufport_handVelocityIn.open(portname_readHandVelocity.c_str());

    BufferedPort<Bottle> bufport_handSignalIn;
    //Bottle *bottle_handPoseData;// = new Bottle;
    bool portOpenOk = bufport_handSignalIn.open(portname_readHandNeuron.c_str());

   // yarpview bufport_imageView;
   // bool portImageOk = bufport_imageView.open(portname_localyarpview);

    if (!dvsPortOk || !portOpenOk){ cout << "Error opening port! Check yarp network status!!!" << endl; return(1);}

    if(!yarp.exists(portname_dvsSim.c_str()))
    {
        cout << "Port " << portname_dvsSim.c_str() << " not open! " << endl;
        return(1);
    }


    if(!yarp.exists(portname_HandVelocity.c_str()))
    {
        cout << "Port " << portname_HandVelocity.c_str() << " not open! " << endl;
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
        connectSuccess = connectSuccess & Network::connect(portname_HandVelocity.c_str(), portname_readHandVelocity.c_str());

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
    int EVENTBOTTLESTOREAD = 1000;

	for (int i=0; i < numSizeSensorX; i++)
	{
		for (int j=0; j < numSizeSensorY; j++)
		{
			imageHandDetect.pixel(i,j) = 0;
		}
	}

	long int tHand;	int polarity; int y; int x;
	long int tHandPrev; long int time; long int initTime;

    while(true)
    {

        Bottle *inputDVSEvent = bufport_dvsIn.read();

        Bottle *inputHandSignal = bufport_handSignalIn.read();

	Bottle *inputHandVelocity = bufport_handVelocityIn.read();	

 //       if ( !(*inputDVSEvent).isNull() )
	{
		
	time = ((*inputDVSEvent).pop()).asInt();
	initTime = ((*inputDVSEvent).pop()).asInt();
	polarity = ((*inputDVSEvent).pop()).asInt();
	y = ((*inputDVSEvent).pop()).asInt();
	x = ((*inputDVSEvent).pop()).asInt();
	//	if(  !(*inputHandSignal).isNull() )
	//	{
			tHand = ((*inputHandSignal).pop()).asInt();	
			long int initHand = ((*inputHandSignal).pop()).asInt();	
	//		tHandPrev = tHand;
	//	}

  //      cout << "x: " << x << " y: " << y << " p: " << polarity << " t: " << time << " tHand: " << tHand << endl;
	
//	double	probability;
	if (abs(time-tHand) < 2)
		{

		imageHandDetect.pixel(x, y) = imageHandDetect.pixel(x, y) + (20*exp( -abs(time-tHand)/100)) ;
		if(imageHandDetect.pixel(x,y) > 80)
			{imageToSend.pixel(x,y)=250;}
		else
			{imageToSend.pixel(x,y)=0;}
//		cout << "Image hand detect: " << (unsigned int) (imageHandDetect.pixel(x,y)) << endl;	
	 //updateWeights(time, tHand);	
		}
	else
		{
		imageHandDetect.pixel(x, y) = imageHandDetect.pixel(x, y)-527; 
		imageToSend.pixel(x,y)=0;	
	//*exp( -(time-tHandPrev)/ 1000) ; 
//		cout << "Image hand not detect: " <<  (imageHandDetect.pixel(x,y)) << endl;	
		}
//	tHandPrev = tHand;				

	
	}

	
	imageHandPort.write(imageToSend);
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
        } /* End of processing with data */ //cout << "end of event bottle data reading" << endl;
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
