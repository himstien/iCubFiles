#include <iostream>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <vector>

//#include <boost/tuple/tuple.hpp>
#include "IzhikevicNeuron.h"
//#include "gnuplot-iostream.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::dev;

void connectToHand();

int main()
{

unsigned long int initTime = Time::now();
Network yarp;

//Gnuplot gp;


FILE *testFile;

yarp::dev::IPositionControl *leftArmControl;
//IEncoders *encoders_arm;

Property property_arm;

BufferedPort<Bottle> handNeurons;
handNeurons.open("/local/handNeurons");

property_arm.put("robot", "icubSim");   property_arm.put("device", "remote_controlboard");
property_arm.put("local", "/icubSim/left_arm/local"); property_arm.put("remote", "/icubSim/left_arm");

PolyDriver driver_arm(property_arm);

driver_arm.view(leftArmControl);
testFile = fopen("testFile.txt", "w");

bool notmoving = true;

IzhikevicNeuron Neuron1;

        double potential = 0;
        long int spikeTime = 0;

double inputCurrent;


double t;
double noise;
double counter = 0;
vector<double> plotData; 

while(true){

    Bottle& toWrite = handNeurons.prepare();
    toWrite.clear();

    leftArmControl->checkMotionDone(&notmoving);
    noise = rand()%10;
    inputCurrent = ( (double) (!notmoving)) * 500 + noise;

    t = Time::now(); //abs(Time::now()-initTime);
    Neuron1.updatePotential(inputCurrent, t);
    potential = Neuron1.getPotential();
    spikeTime = Neuron1.getLastSpikeTime();
//    cout << !notmoving << " " << inputCurrent << " " << potential << " " << spikeTime << endl;
//    fprintf(testFile, "%d %d %lf %ld \n", t, inputCurrent, potential, spikeTime);
    toWrite.addInt(initTime);
    toWrite.addInt(spikeTime);
//	gp << "plot '-' with vectors title 'potential'\n";
//	gp.send1d(potential);

//    out1.push_back(spikeTime);
    handNeurons.write();
   // plotData.push_back(initTime);
   // plotData.push_back(potential);


   // counter++;
//	if (counter > 100)
//	{	counter = 0;
//		for (unsigned int i=0; i < plotData.size(); i++)
//		{	cout << plotData[i] << ' ';
//		}
//	cout << endl;
//	} 
    Time::delay(0.001);
    //t = t+1;
    }
}
