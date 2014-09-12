#include <cstdlib>
#include <iostream>
#include <time.h>

#include "neuronsLIF.h"
#include "receptiveField.h"
#include "yarpDefault.h"

using namespace std;
using namespace yarp::os;

int main(int argc, char *argv[])
{
    bool run = true;

    neuronLIF neuron1;
    neuron1.setNeuronId("neuron1");
    bool spiked;

    neuron1.setDebug(false);
    neuron1.save2File(false);
    neuron1.setNeuronCenter(64.0, 64.0);

    yarpDefault network;
    
    Bottle *tempData;

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
                tempData = network.inputPort.read();
                Bottle *main = tempData->get(0).asList(); //read main list from bottle

                int size = main->size();
                double currentToUpdate = 0;

                for (int s = 0; s < size; s++)
                {
                    Bottle *cur = main->get(s).asList(); //get each sublist  
                    //create timestamp       
                    //TimeStamp ts;
                    //ts.setStamp(cur->find("time").asDouble());
    
                    string type = cur->find("type").asString().c_str(); //for each sublist get type
                    int X = cur->find("posX").asInt();
                    int Y = cur->find("posY").asInt();
                    int pol = cur->find("polarity").asInt();
                    int channel = cur->find("channel").asInt();
            //append timeStamp and Event into single bottle

//                    cout << X << " " << Y << " " << pol << " " << channel << " " << type << endl;  
                    
                    if (pol == 0 && (X < 64+16) && (X > 64-16) && (Y < 64+16) && (Y > 64-16) )
                    {

                        double toUpdateX = neuron1.getCenterX() - X + 16;
                        double toUpdateY = neuron1.getCenterY() - Y + 16;

                    //    cout << X << " " << Y << " " << neuron1.getCenterY()+toUpdateX << " " << neuron1.getCenterY()+toUpdateY << endl;

                        currentToUpdate = currentToUpdate + rf1.getWeightAt(toUpdateX, toUpdateY);


//                        network.imageToWrite.pixel(X, Y) = neuron1.getPotential(); //network.imageToWrite.pixel(X, Y) + 100*rf1.getWeightAt(toUpdateX, toUpdateY);

//                        cout << rf1.getWeightAt(16, 16) << endl;                        
                    }
                }
                    neuron1.updateNeuron(currentToUpdate);

                    cout << currentToUpdate << " " << neuron1.getPotential() << endl;

                    network.imageToWrite.pixel(64, 64) = neuron1.getPotential();

                    network.imagePort.write(network.imageToWrite);


        }
        system("PAUSE");
    }
    return EXIT_SUCCESS;
}

