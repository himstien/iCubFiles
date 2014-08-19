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
    if(rf1.isValid())
    {
        cout << "Created a valid receptive field" << endl;
    }

        
    rf1.setWeightsFile("../testGaborFilter.txt");
    rf1.setWeights();

    cout << rf1.getWeightAt(10, 10) << endl;    
        
    
    for (int i = 0; i < 100; i++)
        {        
        for (int j=0; j < 1000000; j++)
            {        
                spiked = neuron1.updateNeuron(10*(i-1), (unsigned int)time(0));
     //   cout << spiked << " @ " << neuron1.getTimeStamp() << " " << neuron1.getPotential() << endl;
            }
        }
    system("PAUSE");
    return EXIT_SUCCESS;
}

