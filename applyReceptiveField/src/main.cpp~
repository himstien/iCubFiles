#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <math.h>


#include <vector>

#include "receptiveField.h"
#include "yarpDefault.h"
#include "neuronsLIF.h"



using namespace std;
using namespace yarp::os;


int main(int argc, char *argv[])
{
    bool run = true;
    bool verbose = false;

    int numNeurons = 0;


    vector<neuronLIF*> neurons;

    neuronLIF neuron1;
    neuron1.setNeuronId("neuron1");
    neuron1.setDebug(false);
    neuron1.save2File(false);
    neuron1.setNeuronCenter(15.0, 15.0);
    neurons.push_back(&neuron1); 

    neuronLIF neuron2;
    neuron2.setNeuronId("neuron2");
    neuron2.setDebug(false);
    neuron2.save2File(false);
    neuron2.setNeuronCenter(15.0, 47.0);
    neurons.push_back(&neuron2); 
    
    neuronLIF neuron3;
    neuron3.setNeuronId("neuron3");
    neuron3.setDebug(false);
    neuron3.save2File(false);
    neuron3.setNeuronCenter(15.0, 79.0);
    neurons.push_back(&neuron3); 
    
    neuronLIF neuron4;
    neuron4.setNeuronId("neuron4");
    neuron4.setDebug(false);
    neuron4.save2File(false);
    neuron4.setNeuronCenter(15.0, 111.0);
    neurons.push_back(&neuron4); 

    neuronLIF neuron5;
    neuron5.setNeuronId("neuron5");
    neuron5.setDebug(false);
    neuron5.save2File(false);
    neuron5.setNeuronCenter(47.0, 15.0);
    neurons.push_back(&neuron5); 

    neuronLIF neuron6;
    neuron6.setNeuronId("neuron6");
    neuron6.setDebug(false);
    neuron6.save2File(false);
    neuron6.setNeuronCenter(47.0, 47.0);
    neurons.push_back(&neuron6); 
    
    neuronLIF neuron7;
    neuron7.setNeuronId("neuron7");
    neuron7.setDebug(false);
    neuron7.save2File(false);
    neuron7.setNeuronCenter(47.0, 79.0);
    neurons.push_back(&neuron7); 
    
    neuronLIF neuron8;
    neuron8.setNeuronId("neuron8");
    neuron8.setDebug(false);
    neuron8.save2File(false);
    neuron8.setNeuronCenter(47.0, 111.0);
    neurons.push_back(&neuron8); 
    
    neuronLIF neuron9;
    neuron9.setNeuronId("neuron9");
    neuron9.setDebug(false);
    neuron9.save2File(false);
    neuron9.setNeuronCenter(79.0, 15.0);
    neurons.push_back(&neuron9); 

    neuronLIF neuron10;
    neuron10.setNeuronId("neuron6");
    neuron10.setDebug(false);
    neuron10.save2File(false);
    neuron10.setNeuronCenter(79.0, 47.0);
    neurons.push_back(&neuron10); 
    
    neuronLIF neuron11;
    neuron11.setNeuronId("neuronv");
    neuron11.setDebug(false);
    neuron11.save2File(false);
    neuron11.setNeuronCenter(79.0, 79.0);
    neurons.push_back(&neuron11); 
    
    neuronLIF neuron12;
    neuron12.setNeuronId("neuron12");
    neuron12.setDebug(false);
    neuron12.save2File(false);
    neuron12.setNeuronCenter(79.0, 111.0);
    neurons.push_back(&neuron12); 

    neuronLIF neuron13;
    neuron13.setNeuronId("neuron13");
    neuron13.setDebug(false);
    neuron13.save2File(false);
    neuron13.setNeuronCenter(111.0, 15.0);
    neurons.push_back(&neuron13); 

    neuronLIF neuron14;
    neuron14.setNeuronId("neuron14");
    neuron14.setDebug(false);
    neuron14.save2File(false);
    neuron14.setNeuronCenter(111.0, 47.0);
    neurons.push_back(&neuron14); 
    
    neuronLIF neuron15;
    neuron15.setNeuronId("neuron7");
    neuron15.setDebug(false);
    neuron15.save2File(false);
    neuron15.setNeuronCenter(111.0, 79.0);
    neurons.push_back(&neuron15); 
    
    neuronLIF neuron16;
    neuron16.setNeuronId("neuron8");
    neuron16.setDebug(false);
    neuron16.save2File(false);
    neuron16.setNeuronCenter(111.0, 111.0);
    neurons.push_back(&neuron16); 

    numNeurons = neurons.size();

    Bottle *tempData;

    receptiveField rf1;
    if(rf1.isValid())
    {
        cout << "Created a valid receptive field" << endl;
    }

    ResourceFinder rf;
    rf.configure(argc, argv);
    
    string weightsFile = rf.find("file").asString();
    string inputPortName = rf.find("inputPort").asString();
    string imagePortName = rf.find("imagePort").asString();
    string outputPrt = rf.find("outputPort").asString();
 
    if(weightsFile == "")
        weightsFile = "../testCurved1.txt";

    if(inputPortName == "")
        inputPortName = "/inputEvents";

    if(imagePortName == "")
        imagePortName = "/imageRF";

    if(outputPrt == "")
        outputPrt = "/outputState";

//    cout << "WeightsFile: " << weightsFile.c_str() << ", inputPortFile: " << inputPortName.c_str() << ", outputPortName: " << outputPrt.c_str() << endl;

    yarpDefault network(inputPortName, imagePortName, outputPrt);

    yarp::os::Bottle outBottle;
    network.output = outBottle;
        
    rf1.setWeightsFile(weightsFile.c_str());
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
            
                    Bottle &outB = network.outputNeuronStatePort.prepare();
                    outB.clear();
                    for (int numNrn = 0; numNrn < numNeurons; numNrn++)
                    {

                        neuronLIF *neuron = neurons.at(numNrn);                  
                        outB.addDouble(neuron->getPotential());
                        if(verbose)
                        {
                            cout << "[main]: Updating neuron: " << numNrn << " from total " << numNeurons << "." << endl;
                            cout << "[main]: Updating neuron with ID: " << neuron->getNeuronId() << endl;
                        }
                       
                        if ((X < neuron->getCenterX()+16) && (X > neuron->getCenterX()-16) && (Y < neuron->getCenterY()+16) && (Y > neuron->getCenterY()-16) )
                        {

                            double toUpdateX = neuron->getCenterX() - X + 16;
                            double toUpdateY = neuron->getCenterY() - Y + 16;

//                            cout << X << " " << Y << " " << neuron->getCenterX() << " " << neuron->getCenterY() << " " << toUpdateX << " " << toUpdateY << endl;
                            currentToUpdate = currentToUpdate+rf1.getWeightAt(toUpdateX, toUpdateY);

                            neuron->updateNeuron(currentToUpdate);
                            
/*
                            for (int x = 0; x < 32; x++)
                            {
                                for (int y = 0; y < 32; y++) 
                                {
                                  yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(neuron->getCenterY()-y+16, neuron->getCenterX()-x+16);
                                  //network.imageToWrite.pixel(64-x+16, 64-y+16) = 127+neuron1.getPotential()*rf1.getWeightAt(x, y);
                                  pixel.r = abs(int(100.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                  pixel.g = abs(int(100.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                  pixel.b = abs(int(0.1*neuron->getPotential()*rf1.getWeightAt(x, y))); 
                                }   
                            }
*/
                            
//                        network.imageToWrite.pixel(X, Y) = network.imageToWrite.pixel(X, Y) + 17*rf1.getWeightAt(toUpdateX, toUpdateY);

//                        if (network.imageToWrite.pixel(X, Y) < 0 )
//                        {
//                            network.imageToWrite.pixel(X, Y) = 0;
//                        }
                        }
                        
                    }
                    if(network.outputNeuronStatePort.getOutputCount())
                        network.outputNeuronStatePort.write();

                   // cout << endl;
                }

                    
//                network.imageToWrite.pixel(64, 64) = 60*neuron1.getPotential();



               

//                        if (network.imageToWrite.pixel(X, Y) < 0 )
//                        {
//                            network.imageToWrite.pixel(X, Y) = 0;
//                        }

     //            network.imagePort.write(network.imageToWrite);


        }
        system("PAUSE");
    }
    return EXIT_SUCCESS;
}


