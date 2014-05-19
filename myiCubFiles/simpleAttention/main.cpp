#include <iostream>
#include <fstream>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>

//#include "unmask.h"
#include "eventCodec.h"
#include "eventBottle.h"


using namespace std;
using namespace yarp::sig;
using namespace yarp::os;
using namespace yarp::dev;
using namespace emorph::ecodec;

double maxOfVector(Vector, int, int);

int main(int numArgs, char** args)
{

Network yarp;
string dvsPort = "/aexGrabber/eventBottle:o";

ImageOf<PixelInt> clusterImage;
clusterImage.resize(128,128);

BufferedPort<eventBottle> readDVS;
(readDVS).open("/dvsReadLocal:i");
printf("Created port /dvsReadLocal:i to get data from DVS!!\n\n");


Port confidenceOut;
confidenceOut.open("/eventBased/confidence");

bool connectionOk = yarp.connect(dvsPort.c_str(), "/dvsReadLocal:i");

if (!connectionOk)
{
	printf("Waiting for aexGrabber port to go alive!!!\n\n");
	connectionOk = yarp.connect(dvsPort.c_str(), "/dvsReadLocal:i");
}

eventBottle *evBottle;

//### Psuedo code

// Do every T amount of time

	// For each eye
	
		// Define cluster init position.
			// Num clusters	= 5 (const init);
const int numClusters = 5;
			// Cluster events = 0 (variable init);
Vector numEventsPerCluster;
numEventsPerCluster.resize(5);

Vector currentEventNumbers, previousEventNumbers;
currentEventNumbers.resize(128*128); currentEventNumbers.zero();
previousEventNumbers.resize(128*128); previousEventNumbers.zero();

Vector confidence; confidence.resize(128*128); confidence.zero();


double timeToProcess = 0;
double previousTime = 0;
		// With each event shift cluster position to new value.
bool run = true;

while (run )
{
	evBottle = readDVS.read();

//	cout << (*evBottle).get_sizeOfPacket() << endl;

	Bottle *bottle = (*evBottle).get_packet();

//unmask U;
//U.unmaskData(bottle);
	emorph::ecodec::eEventQueue q;


	emorph::ecodec::eEvent::decode(*bottle, q);

	int sizeOfQ = q.size();
//	cout << "Size of queue = " << sizeOfQ << endl;

	int X, Y, Pol;

	
		
	for (int i=0; i < sizeOfQ; i++)
	{
		if (q[i]->getType() == "AE")
		{
//			printf("Found Address event\n\n");

			AddressEvent* addr = static_cast<AddressEvent*>(q[i]);
			if( addr -> isValid())
			{
				X = addr->getX();
				Y = addr->getY();
				Pol = addr->getPolarity();
			}	
//			cout << X << " " << Y << " " << Pol << endl;
	
			{
				currentEventNumbers(X*128+Y) = currentEventNumbers(X*128+Y) + 1;
			}

			timeToProcess = (double)Time::now() - previousTime;	
			timeToProcess = timeToProcess*10;
			
	
		}
		for (int i=0; i < 128; i++)
		{
			for (int j=0; j < 128; j++)
			{
					clusterImage(i,j) = 0;
			}
		}		
	
	
	
		if (timeToProcess > 10)
		{
			for (int i=0; i < 128; i++)
			{
				for (int j=0; j < 128; j++)
				{
					if( currentEventNumbers(i*128+j)!=0 || previousEventNumbers(i*128+j)!=0 )
					{
						confidence(i*128+j) = currentEventNumbers(i*128+j)/(previousEventNumbers(i*128+j)+currentEventNumbers(i*128+j));
						clusterImage(i,j) = 127 + confidence(i*128+j)*127;
					}
					previousEventNumbers(i*128+j) = currentEventNumbers(i*128+j);
				}
			}		
			cout << maxOfVector(confidence, 128, 128) << endl;
			
			previousTime = Time::now();
			confidenceOut.write(clusterImage);
			currentEventNumbers.zero();
			confidence.zero();

		}
	}
	
} // end of while


//
//eventPacket.();
			// Add event to this cluster
			// Main cluster = max event clusters

	
	// Get [x,y] for each eye

	// Do gaze control using these values.

// Reset all clusters
 

} // end of main

double maxOfVector (Vector vec, int sizeX, int sizeY)
{
	double maxValue = 0;
	for (int i=0; i < sizeX; i++)
	{
		for (int j=0; j < sizeY; j++)
		{
			if (vec(i*sizeX + j) > maxValue)
			{
				maxValue = vec(i*sizeX + sizeY);
			}
		}
	}
	return maxValue;
}
