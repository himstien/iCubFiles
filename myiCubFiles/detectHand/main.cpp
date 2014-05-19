
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

// *** include project header files
//#include "eventRead.h"
#include "unmask.h"
//#include "eventBuffer.h"
//#include "eventBottle.h"
//#include "eventBottleHandler.h"
//#include "eventUnmask.h"
//#include "eventCodec.h"
//#include "eventConversion.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;
//using namespace emorph::ebuffer;
//using namespace emorph::ecodec;

yarp::sig::Vector getEndEffectorPosition();
double updateWeights(int, int);

int main(int argc, char** argv)
{
    bool verbose = false;

    ofstream file_outFile, file_writeData;
    Network yarp;

  
    int numRowsSensor = 128;

    vector<double> vector_Weights(numRowsSensor*numRowsSensor*numRowsSensor*numRowsSensor,0); // To store weights between DVS pixels

// **** Pre-known port names... TODO: Change code to get port names automatically ****
    string portname_aexGrabber = "/dvsSim/eventBottle:o";
    string portname_readDVSPort = "/dvsTempRead:i";

    string portname_handPositionNeuron = "/local/leftArmPoseNeuron";
    string portname_localHandPoseRead = "/dvsHandPoseReader:i";

    string portname_icubLeftArm = "/icubSim/left_arm";
    string portname_icubLeftArmLocal = "/icubSim/leftarm/dvsReader";

    //string portname_localyarpview = "/viewer/temp:i";
    string portname_localyarpImage = "/viewer/imageOut:o";

    int size_of_data;

// Declare and initialize variables for control of eyes
// /*
    yarp::dev::IPositionControl *poscntrl_leftArm;
    yarp::dev::IEncoders *encoders_leftArm;

    Property property_arm;

    property_arm.put("robot","icub");  property_arm.put("device","remote_controlboard");
    property_arm.put("local",portname_icubLeftArmLocal.c_str()); property_arm.put("remote",portname_icubLeftArm.c_str());

    if(verbose) cout << "creating driver and ports for arm "<< endl;
    yarp::dev::PolyDriver driver_leftArmCntrl(property_arm);

// /*
    if(!driver_leftArmCntrl.isValid())
    {
        printf("Device leftArmCntrl not available.  Here are the known devices:\n");
        printf("%s", yarp::dev::Drivers::factory().toString().c_str());
        Network::fini();
        return 1;
    }

    //driver_rightArmCntrl.view(cartcntrl_rightArm);
    driver_leftArmCntrl.view(poscntrl_leftArm);
    driver_leftArmCntrl.view(encoders_leftArm);

// */

    int numJntsHand = -1;
    encoders_leftArm->getAxes(&numJntsHand);
    vector<double> vector_Joints(numJntsHand, 0);

    bool moveEyes = true;

// */

// Declare image to connect with yarpviewer

// Declare bottles and eventBottles
    Bottle *bottle_inputDVSData = new Bottle; //, *dvsRead;
    

// Declare and open buffered ports for receiving Tactile and DVS events
    BufferedPort<Bottle> bufport_dvsIn;
    bool dvsPortOk = bufport_dvsIn.open(portname_readDVSPort.c_str());

    BufferedPort<Bottle> bufport_leftArmNeuron;
    //Bottle *bottle_handPoseData;// = new Bottle;
    bool portOpenOk = bufport_leftArmNeuron.open(portname_localHandPoseRead.c_str());

   // yarpview bufport_imageView;
   // bool portImageOk = bufport_imageView.open(portname_localyarpview);

    if (!dvsPortOk || !portOpenOk){ cout << "Error opening port! Check yarp network status!!!" << endl; return(1);}

    if(!yarp.exists(portname_aexGrabber.c_str()))
    {
        cout << "Port " << portname_aexGrabber.c_str() << " not open! " << yarp.exists(portname_aexGrabber.c_str()) << endl;
        return(0);
    }

    if( !yarp.exists(portname_handPositionNeuron.c_str()) )
    {
        cout << "Port " << portname_handPositionNeuron.c_str() << " not open! " << yarp.exists(portname_handPositionNeuron.c_str()) << endl;
        return(0);
    }

    else
    {
        cout << "Trying to connect ports..." << endl;
        bool  connectSuccess = true;
        connectSuccess = Network::connect(portname_handPositionNeuron.c_str(), portname_localHandPoseRead.c_str());
        connectSuccess = connectSuccess & Network::connect(portname_aexGrabber.c_str(), portname_readDVSPort.c_str());
        if (!connectSuccess) { cout << "Could not connect ports! Something went wrong!" << endl; return(1);}
    }


    cout << "Number of inputs given: " << argc << endl;

    if (argc < 2)
    {
        file_outFile.open("weights.dat");
        file_writeData.open("DVS_Hand_data.dat");
    }
    else
    {
        file_outFile.open(argv[1]);
        file_writeData.open("DVS_Hand_data.dat");
    }

    cout << "Writing to file \b weights.txt" << endl;

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

    cout << "Creating cluster centers " << endl;
    int window = 1;
    int initClustersX[128*128];
    int initClustersY[128*128];
    int numClusters = 0;

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

            poscntrl_leftArm->checkMotionDone(&notmoving);

            vector<double> storeDVSX; vector<double> storeDVSY; vector<double> storeDVST;

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
            */
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
    } /* End of number of frames */
    file_outFile.close();
    bufport_dvsIn.close();

    driver_leftArmCntrl.close();

    delete bottle_inputDVSData; //, *dvsRead;
    delete eventbottle_dvsRead;
    //delete bottle_handPoseData;

    return 0;
}



double updateWeights(int time1, int time2)
{
    //double delTime = abs(delT);
    double sigma = 10.0;
    double delT = abs((double)time1 - (double)time2);
    double A = (1/(sigma*sqrt(2*3.14152)));

    double inFunc = (delT*delT)/2*(sigma*sigma);

    double G = A*exp(-inFunc);

    //cout << G-20 << endl;

    return (G);

}
