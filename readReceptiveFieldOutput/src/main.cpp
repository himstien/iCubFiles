#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <math.h>
#include <vector>

#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>

using namespace std;
using namespace yarp::os;


int main(int argc, char *argv[])
{
    Network yarpy;

    bool run = true;

    BufferedPort<Bottle> inputBottle1;
    inputBottle1.open("/localNeuronPotentialReader1:i");    

    BufferedPort<Bottle> inputBottle2;
    inputBottle2.open("/localNeuronPotentialReader2:i");    

    BufferedPort<Bottle> inputBottle3;
    inputBottle3.open("/localNeuronPotentialReader3:i");    

    BufferedPort<Bottle> inputBottle4;
    inputBottle4.open("/localNeuronPotentialReader4:i");    

    BufferedPort<Bottle> inputBottle5;
    inputBottle5.open("/localNeuronPotentialReader5:i");    


    yarpy.connect( "/outputRF1", "/localNeuronPotentialReader1:i");
    yarpy.connect( "/outputRF2", "/localNeuronPotentialReader2:i");
    yarpy.connect( "/outputRF3", "/localNeuronPotentialReader3:i");
    yarpy.connect( "/outputRF4", "/localNeuronPotentialReader4:i");
    yarpy.connect( "/outputRF5", "/localNeuronPotentialReader5:i");

    vector<double> potential;

    while(run)
    {
        Bottle *tempData1; Bottle *tempData2; Bottle *tempData3; Bottle *tempData4; Bottle *tempData5;
        
        tempData1 = inputBottle1.read(); tempData2 = inputBottle2.read(); tempData3 = inputBottle3.read(); tempData4 = inputBottle4.read(); 
        tempData5 = inputBottle5.read();

        for (int i=0; i<tempData2->size(); i++)
        {
            cout << tempData2->get(i).asDouble() << " ";
        }
        cout << endl;

    }
       

}


