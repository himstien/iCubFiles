#include <cstdlib>
#include <iostream>
#include <time.h>

#include "neuronsLIF.h"
#include "receptiveField.h"

using namespace std;

int main(int argc, char *argv[])
{
    bool run = true;

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

    if(rf1.isValid())
    {
        //cout << rf1.getWeightAt(10, 10) << endl;    
        
    
        while(run)
        {        
            

        }
        system("PAUSE");
    }
    return EXIT_SUCCESS;
}

