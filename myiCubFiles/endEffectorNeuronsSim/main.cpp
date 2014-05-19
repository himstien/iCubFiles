/////////////// Project name: end Effector Neuron Sim

#include <iostream>
#include <fstream>
#include <vector>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>

#include "IzhikevicNeuron.h"

using namespace std;

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;


int main()
{

Network yarp;

bool verbose=false;

string portname_leftHandNeurons = "/local/leftArmPoseNeuron";
Port leftHandNeuronsPort;
leftHandNeuronsPort.open(portname_leftHandNeurons.c_str());

string portname_testHandNeurons = "/leftHandPoseNeurons";
BufferedPort<Bottle> testHandNeuronsPort;
testHandNeuronsPort.open(portname_testHandNeurons.c_str());

string portname_leftHandVelocity = "/leftHandVelocity";
BufferedPort<Bottle> leftHandVelocityPort;
leftHandVelocityPort.open(portname_leftHandVelocity.c_str());
//neuronData.resize(3*sizeof(int));

//neuronData.resize(3);


string portname_icubLeftArmLocal = "/icubSim/world";
cout << verbose << endl;
cout << Network::connect(portname_leftHandNeurons.c_str(), portname_icubLeftArmLocal.c_str()) << endl;

yarp::sig::Vector vec_effEndTra;
yarp::sig::Vector vec_effEndRot;
vec_effEndTra.resize(3*sizeof(double));

int xMin, yMin, zMin, xMax, yMax, zMax;
xMin=-45; xMax=10; yMin=-8; yMax=40; zMin=-33; zMax=-7;
int numX = xMax-xMin+2;
int numY = yMax-yMin+2;
cout << "numX Y: " << numX << " " << numY << endl;
IzhikevicNeuron Neurons[numX][numY];

//double potential = 0;
long int spikeTime = 0;

double inputCurrent;

double initTime = Time::now();
//file_init_time << initTime << endl;

double t;
double noise;
double X = 0; 
double Y = 0;
double Z = 0;

double Xp, Yp, Zp, Xhat, Yhat, Zhat;
Xp=0; Yp=0; Zp=0;


Bottle writeToPort("world get lhand");
Bottle replyFromWorld;
while(true){
	
	leftHandNeuronsPort.write(writeToPort, replyFromWorld);
   // neuronData.clear();
	vec_effEndTra[2] = -(replyFromWorld.pop()).asDouble()-0.04;
	vec_effEndTra[1] = (replyFromWorld.pop()).asDouble()-0.5484;
	vec_effEndTra[0] = -(replyFromWorld.pop()).asDouble();

    if(verbose) cout << "position of end effector: " << vec_effEndTra.toString().c_str() << endl;

    
	X = (vec_effEndTra[0]*100);
	Y = (vec_effEndTra[1]*100);
	Z = (vec_effEndTra[2]*100);

	Xhat = X-Xp;
	Yhat = Y-Yp;
	Zhat = Z-Zp;
	

	for (int i = xMin; i < xMax; i=i+5){
		for (int j = yMin; j < yMax; j=j+5){
	
    			noise = rand()%10;
    			inputCurrent = 1000*(sqrt((Xhat*Xhat+Yhat*Yhat+Zhat*Zhat)))*exp(-sqrt((i-X)*(i-X)+(j-Y)*(j-Y))/2) + noise;

			t = abs(Time::now());

//cout << i-xMin << " " << j-yMin << " " << spikeTime << endl;

			Neurons[i-xMin][j-yMin].updatePotential(inputCurrent, t);
 //   double potential = Neurons[21][21].getPotential();
//cout << potential << endl;
			
    			spikeTime = Neurons[i-xMin][j-yMin].getLastSpikeTime();
			
    			
 //   file_endeffector << X << " " << Y << " " << spikeTime << endl;
cout << X << " " << Y << " " << Z << endl;

 //   dataToWrite = neuronData.data();
  //  cout << neuronData.size() << endl;
  //  cout << neuronData.size() << endl;
    			Bottle &neuronData = testHandNeuronsPort.prepare();
			neuronData.clear();
    //neuronData = leftHandNeuronsPort.prepare();
    			neuronData.addInt(i-xMin);
    			neuronData.addInt(j-yMin);
    			neuronData.addInt(spikeTime);

			Bottle &velocityData = leftHandVelocityPort.prepare();
			velocityData.addDouble(Xhat);
			velocityData.addDouble(Yhat);
			velocityData.addDouble(Zhat);
			leftHandVelocityPort.write();

//    cout << neuronData.toString().c_str() << endl;
			if( spikeTime >0)// && (t-spikeTime)<10)
			{ 
				testHandNeuronsPort.write();
			}
    			Time::delay(0.001);
    //cout << leftHandNeuronsPort.getPendingReads() << endl;
    			neuronData.clear();
			velocityData.clear();	
		}
	}


    //Bottle *testData = testHandNeuronsPort.read();
    //cout << (*testData).size() << endl;

    //t = t+1;
	Xp = X; Yp=Y;Zp=Z;
    }
}
