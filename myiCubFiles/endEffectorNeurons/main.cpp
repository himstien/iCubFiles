
#include <iostream>
#include <fstream>
#include <vector>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
YARP_DECLARE_DEVICES(icubmod)

#include "IzhikevicNeuron.h"

using namespace std;

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;


int main()
{

Network yarp;
YARP_REGISTER_DEVICES(icubmod)

ofstream file_endeffector("endEffectorDataNeurons.dat");
ofstream file_init_time("initTime.dat");
bool verbose=false;

string portname_leftHandNeurons = "/local/leftArmPoseNeuron";
BufferedPort<Bottle> leftHandNeuronsPort;
leftHandNeuronsPort.open(portname_leftHandNeurons.c_str());

string portname_testHandNeurons = "/test/leftArmPoseNeuron";
BufferedPort<Bottle> testHandNeuronsPort;
testHandNeuronsPort.open(portname_testHandNeurons.c_str());

cout << Network::connect(portname_leftHandNeurons.c_str(), portname_testHandNeurons.c_str()) << endl;
//neuronData.resize(3*sizeof(int));

//neuronData.resize(3);


string portname_icubLeftArm = "/icubSim/cartesianController/left_arm";
string portname_icubLeftArmLocal = "/icubSim/leftarm/local";
cout << verbose << endl;
ICartesianControl *cartcntrl_leftArm;

yarp::sig::Vector vec_effEndTra;
yarp::sig::Vector vec_effEndRot;

Property property_arm;

property_arm.put("robot","icubSim");  property_arm.put("device","cartesiancontrollerclient");
property_arm.put("remote",portname_icubLeftArm.c_str()); property_arm.put("local",portname_icubLeftArmLocal.c_str());

    if(verbose) cout << "creating driver and ports for arm "<< endl;
    PolyDriver driver_leftArmCntrl(property_arm);

    if(!driver_leftArmCntrl.isValid()){
        printf("Device leftArmCntrl not available.  Here are the known devices:\n");
        printf("%s", Drivers::factory().toString().c_str());
        Network::fini();
        return 1;
    }
    driver_leftArmCntrl.view(cartcntrl_leftArm);



IzhikevicNeuron Neurons[256][256];

//double potential = 0;
long int spikeTime = 0;

double inputCurrent;

double initTime = Time::now();
file_init_time << initTime << endl;

double t;
double noise;

while(true){

   // neuronData.clear();

    cartcntrl_leftArm->getPose(vec_effEndTra, vec_effEndRot);
   // file_endeffector << vec_effEndRot.toString().c_str() << " " << vec_effEndRot.toString().c_str() << endl;
    if(verbose) cout << "position of end effector: " << vec_effEndTra.toString().c_str() << " " << vec_effEndTra.toString().c_str() << endl;

   // int X = round(vec_effEndTra[0]*100)+50;
    int Y = round(vec_effEndTra[1]*100)+50;
    int X = round(vec_effEndTra[0]*100)+50;

    noise = rand()%10;
    inputCurrent = 1000 + noise;

    t = abs(Time::now()-initTime);
    Neurons[X][Y].updatePotential(inputCurrent, t);
//    potential = Neurons[X][Y].getPotential();
    spikeTime = Neurons[X][Y].getLastSpikeTime();
    //cout << X << " " << Y << " " << spikeTime << endl;
 //   file_endeffector << X << " " << Y << " " << spikeTime << endl;


 //   dataToWrite = neuronData.data();
  //  cout << neuronData.size() << endl;
  //  cout << neuronData.size() << endl;
    Bottle &neuronData = leftHandNeuronsPort.prepare();
    //neuronData = leftHandNeuronsPort.prepare();
    (neuronData).addInt(X);
    neuronData.addInt(Y);
    neuronData.addInt(spikeTime);
//    cout << neuronData.toString().c_str() << endl;

    leftHandNeuronsPort.writeStrict();
    Time::delay(0.001);
    //cout << leftHandNeuronsPort.getPendingReads() << endl;
    neuronData.clear();



    //Bottle *testData = testHandNeuronsPort.read();
    //cout << (*testData).size() << endl;

    //t = t+1;
    }
}