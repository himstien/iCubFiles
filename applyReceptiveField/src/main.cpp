#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

#include "neuronsLIF.h"
#include "receptiveField.h"
#include "yarpDefault.h"

using namespace std;
using namespace yarp::os;

int main(int argc, char *argv[])
{
    bool run = true;

    int numNeurons = 2;

    vector<neuronLIF> neurons;


    neuronLIF neuron1;
    neuron1.setNeuronId("neuron1");
    bool spiked;

    neuron1.setDebug(false);
    neuron1.save2File(false);
    neuron1.setNeuronCenter(64.0, 64.0);
    
  //  neurons.push_back(&neuron1);

    yarpDefault network;
    
    Bottle *tempData;

    receptiveField rf1;
    if(rf1.isValid())
    {
        cout << "Created a valid receptive field" << endl;
    }

        
    rf1.setWeightsFile("../testCurved1.txt");
    rf1.setWeights();
    
//    rf1.multiplyWeights(0.5);
    
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
                    for (int numNrn = 0; numNrn < numNeurons; numNrn++)
                    {
                        neuronLIF neuron = neuron1; 
                        
// = neuron1; //neurons.at(numNrn);
                        
                        if (channel == 0 && pol == 0 && (X < neuron.getCenterX()+16) && (X > neuron.getCenterX()-16) && (Y < neuron.getCenterX()+16) && (Y > neuron.getCenterX()-16) )
                        {

                            double toUpdateX = neuron.getCenterX() - X + 16;
                            double toUpdateY = neuron.getCenterY() - Y + 16;

                    //    cout << X << " " << Y << " " << neuron1.getCenterY()+toUpdateX << " " << neuron1.getCenterY()+toUpdateY << endl;

                            currentToUpdate = currentToUpdate+rf1.getWeightAt(toUpdateX, toUpdateY);


    

//                        network.imageToWrite.pixel(X, Y) = network.imageToWrite.pixel(X, Y) + 17*rf1.getWeightAt(toUpdateX, toUpdateY);

//                        if (network.imageToWrite.pixel(X, Y) < 0 )
//                        {
//                            network.imageToWrite.pixel(X, Y) = 0;
//                        }
                        }

                    }
                }

                        neuron1.updateNeuron(currentToUpdate);
//                network.imageToWrite.pixel(64, 64) = 60*neuron1.getPotential();
                        cout <<  currentToUpdate << endl;    


                        for (int x = 0; x < 32; x++)
                        {
                            for (int y = 0; y < 32; y++) 
                            {
                                  yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(64-x+16, 64-y+16);
                                  //network.imageToWrite.pixel(64-x+16, 64-y+16) = 127+neuron1.getPotential()*rf1.getWeightAt(x, y);
                                  pixel.r = 0.5+neuron1.getPotential()*rf1.getWeightAt(x, y);

                            }   
                        }

               

//                        if (network.imageToWrite.pixel(X, Y) < 0 )
//                        {
//                            network.imageToWrite.pixel(X, Y) = 0;
//                        }

                 network.imagePort.write(network.imageToWrite);


        }
        system("PAUSE");
    }
    return EXIT_SUCCESS;
}

