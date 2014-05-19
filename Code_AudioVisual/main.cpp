#include <iostream>
#include <fstream>

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/AudioGrabberInterfaces.h>

#include <yarp/os/Property.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <yarp/os/Time.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/NetInt16.h>

#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>
#include <yarp/sig/SoundFile.h>

//#include "unmask.h"
#include "eventCodec.h"
#include "eventBottle.h"


using namespace std;
using namespace yarp::sig;
using namespace yarp::os;
using namespace yarp::dev;
using namespace emorph::ecodec;

const int numClusters=5;
Vector numEventsPerCluster;
Vector clustersX;
Vector clustersY;
Vector distClusters;

void updateClusterValues(int x, int y, int channel, int polarity);


int main(int numArgs, char** args)
{


Network yarp;

//Initialize DVS ports and connections
string dvsPort = "/aexGrabber/eventBottle:o";
BufferedPort<eventBottle> readDVS;
(readDVS).open("/dvsReadLocal:i");
bool connSuccess = yarp.connect(dvsPort.c_str(), "/dvsReadLocal:i");

if (!connSuccess)
{
	printf("Connection to DVS port failed. Check that aexGrabber is running!!!\n\n");	
	return 1;
}
	
//Initialize Microphone ports and connections
Port soundOut;
soundOut.open("/soundMic");

Property conf;
conf.put("device","portaudio");
conf.put("read", "");
conf.put("samples", 48000);
conf.put("iD", "0");
conf.put("rate", 48000);
conf.put("channels", 1);

PolyDriver poly(conf);
IAudioGrabberSound *sndGrabber;

poly.view(sndGrabber);
if (sndGrabber==NULL) 
    {
        printf("cannot open interface\n");
        return 1;
    }


// Initialize feature based image outputs to be sent to yarpview
ImageOf<PixelRgb> imageOut;
string portname_imageOutPort = "/imageOut";
Port port_imageOut; 
port_imageOut.open(portname_imageOutPort.c_str());

// Initialize variables for collecting DVS events and Microphone sound

eventBottle *evBottle;
Sound snd;

int sndDataSize;
unsigned char *sndData;
int sndChannels, sndSamples;

// Create files to write data from DVS and Mic
ofstream sndFile, dvsFile;

cout << "Num input arguments : " << numArgs << endl;
if (numArgs == 2)
{
    cout << "Writing sound to : " << args[1] << endl;
    sndFile.open(args[1]);
    dvsFile.open("dvsData.dat");
}
else if (numArgs == 3)
{
    cout << "Writing sound to : " << args[1] << " and events to : " << args[2] << endl;
    sndFile.open(args[1]);
    dvsFile.open(args[2]);
}
else
{
    sndFile.open("micData.dat");
    dvsFile.open("dvsData.dat");
}
//### Psuedo code

// Do every T amount of time

	// For each eye
	
		// Define cluster init position.
			// Num clusters	= 5 (const init);

//numClusters = 5;
			// Cluster events = 0 (variable init);

numEventsPerCluster.resize(5);
clustersX.resize(5);
clustersY.resize(5);
distClusters.resize(5);


clustersX[0] = 64; clustersY[0] = 64;
clustersX[1] = 10; clustersY[1] = 10;
clustersX[2] = 10; clustersY[2] = 100;
clustersX[3] = 100; clustersY[3] = 10;
clustersX[4] = 100; clustersY[4] = 100;

int totalTime = 0;
int initTime = Time::now();

int dataCollectionTime = 60;

    while(true && totalTime < dataCollectionTime)
    {

        if(sndGrabber->getSound(snd))
        {
            sndDataSize = snd.getRawDataSize();    
            sndData = snd.getRawData();
            sndChannels = snd.getChannels();
            sndSamples = snd.getSamples();
            
		// With each event shift cluster position to new value.
            evBottle = readDVS.read();


            cout << "Size of DVS packets: " << (*evBottle).get_sizeOfPacket() << endl;
            cout << "Size of Sound packets: " << sndDataSize << endl;            
            cout << "Size of Bytes Samples: " << snd.getBytesPerSample() << endl;            
            Bottle *bottle = (*evBottle).get_packet();

//unmask U;
//U.unmaskData(bottle);

            eEventQueue q;

            eEvent::decode(*bottle, q);

            int sizeOfQ = q.size();

            int X, Y, Pol, channel;

            for (int i=0; i < sizeOfQ; i++)
            {
	            if (q[i]->getType() == "AE")
	            {
	        	    AddressEvent* ptr=dynamic_cast<AddressEvent*>(q[i]);
                    X = ptr->getX();
                    Y = ptr->getY();
                    channel = ptr->getChannel();       
                    Pol = ptr->getPolarity();
                    
                    dvsFile << X << " " << Y << " " << channel << " " << Pol << " ";                      
                    updateClusterValues(X, Y, channel, Pol);      
        	    }
            
                else if (q[i]->getType() == "TS")
    	        {
    	    	    TimeStamp* ptr=dynamic_cast<TimeStamp*>(q[i]);
                    unsigned int timeS = ptr->getStamp();
                    
                    dvsFile <<  timeS << endl;                    
//                updateClusterValues(X, Y, channel, Pol);      
        	    }
//            for (int numC=0; numC < numClusters; numC++)
//            {
//                cout << "[" << clustersX[numC] << ":" << clustersY[numC] << ":" << numEventsPerCluster[numC] << "]";
//            }
//            cout << endl;
            } 
            
            yarp::sig::file::write(snd, "check.wav");
            
                      
            for (int iSnd=0; iSnd < sndSamples; iSnd++)
                {
                     for (int jSnd=0; jSnd < sndChannels; jSnd++)
                     {
//                cout << (float)sndData[iSnd] << endl;
                       sndFile << (snd.get(iSnd,jSnd)) << " ";
                     }
               //      sndFile << endl;
                 }
		sndFile << endl;
            }
		
            totalTime = Time::now() - initTime; 
            cout << totalTime << endl;
            soundOut.write(snd);
}



//
//eventPacket.();
			// Add event to this cluster
			// Main cluster = max event clusters

	
	// Get [x,y] for each eye

	// Do gaze control using these values.

// Reset all clusters
sndFile.close();
dvsFile.close();

}


void updateClusterValues(int x, int  y, int  channel, int polarity)
{

    if (channel == 0)
                {
                    for (int numC = 0; numC < numClusters; numC++)
                    {
                    
                        distClusters[numC] = (clustersX[numC]-x)*(clustersX[numC]-x) + (clustersY[numC]-y)*(clustersY[numC]-y);
#ifdef verbose
                        cout << ptr->getX()<< " " << ptr->getY() << " " << ptr->getChannel() << " " <<  ptr->getPolarity() << endl;
#endif
                    }
                    int minCluster = 0; int minClusterVal=100;
                    for (int numC = 0; numC < numClusters; numC++)
                    {
                        if(distClusters[numC] < minClusterVal)
                        {
                            minCluster = numC;
                            minClusterVal = distClusters[numC];
                        }
                    }
                    
                    numEventsPerCluster[minCluster] = numEventsPerCluster[minCluster]+1;
                    clustersX[minCluster] = clustersX[minCluster] - (clustersX[minCluster]-x)/2;
                    clustersY[minCluster] = clustersY[minCluster] - (clustersY[minCluster]-y)/2;
                }


}