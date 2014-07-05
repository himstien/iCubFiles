#include <cstdlib>
#include <iostream>
#include <time.h>

#include "neuronsLIF.h"
#include "receptiveField.h"

using namespace std;

int main(int argc, char *argv[])
{
    neuronLIF neuron1;
    neuron1.setNeuronId("neuron1");
    bool spiked;
    neuron1.setDebug(false);
    neuron1.save2File(true);

    receptiveField rf1;
    rf1.setWeights;
        
    for (int i=0; i < 10000000; i++)
    {        
        spiked = neuron1.updateNeuron(100, (unsigned int)time(0));
        cout << spiked << " @ " << neuron1.getTimeStamp() << " " << neuron1.getPotential() << endl;
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}

