#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>
#include <math.h>
#include <tr1/memory>

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

    ResourceFinder rf;
    rf.configure(argc, argv);

    int X;
    int Y;
    
//    string weightsFile = rf.find("file").asString();
    string inputPortName = rf.find("inputPort").asString();
    string imagePortName = rf.find("imagePort").asString();
    string outputPrt = rf.find("outputPort").asString();
    X = rf.find("X").asInt();
    Y = rf.find("Y").asInt();
 
    if(inputPortName == "")
        inputPortName = "/inputEvents";

    if(imagePortName == "")
        imagePortName = "/imageRF";

    if(outputPrt == "")
        outputPrt = "/outputState";

    if(X == 0)
         X = 64;
     
    if(Y == 0)
        Y = 64;


    




//********* TO DO : Need too remove this to a for loop. Vector push_back not working for some reason.

vector<receptiveField*> receptiveFields;
string weightsFile;
//    receptiveFields.resize(24);

receptiveField rf1;
weightsFile = "./curvedRFs/curvedRF1.txt" ;
rf1.setWeightsFile(weightsFile.c_str());
rf1.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf1);

receptiveField rf2;
weightsFile = "./curvedRFs/curvedRF2.txt" ;
rf2.setWeightsFile(weightsFile.c_str());
rf2.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf2);


receptiveField rf3;
weightsFile = "./curvedRFs/curvedRF3.txt" ;
rf3.setWeightsFile(weightsFile.c_str());
rf3.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf3);

receptiveField rf4;
weightsFile = "./curvedRFs/curvedRF4.txt" ;
rf4.setWeightsFile(weightsFile.c_str());
rf4.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf4);

receptiveField rf5;
weightsFile = "./curvedRFs/curvedRF5.txt" ;
rf5.setWeightsFile(weightsFile.c_str());
rf5.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf5);

receptiveField rf6;
weightsFile = "./curvedRFs/curvedRF6.txt" ;
rf6.setWeightsFile(weightsFile.c_str());
rf6.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf6);

receptiveField rf7;
weightsFile = "./curvedRFs/curvedRF7.txt" ;
rf7.setWeightsFile(weightsFile.c_str());
rf7.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf7);

receptiveField rf8;
weightsFile = "./curvedRFs/curvedRF8.txt" ;
rf8.setWeightsFile(weightsFile.c_str());
rf8.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf8);

receptiveField rf9;
weightsFile = "./curvedRFs/curvedRF9.txt" ;
rf9.setWeightsFile(weightsFile.c_str());
rf9.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf9);

receptiveField rf10;
weightsFile = "./curvedRFs/curvedRF10.txt" ;
rf10.setWeightsFile(weightsFile.c_str());
rf10.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf10);

receptiveField rf11;
weightsFile = "./curvedRFs/curvedRF11.txt" ;
rf11.setWeightsFile(weightsFile.c_str());
rf11.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf11);

receptiveField rf12;
weightsFile = "./curvedRFs/curvedRF12.txt" ;
rf12.setWeightsFile(weightsFile.c_str());
rf12.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
receptiveFields.push_back(&rf12);




vector<neuronLIF*> neurons;

neuronLIF neuron1;
neuron1.setNeuronId("neuron1");
neuron1.setDebug(false);
neuron1.save2File(false);
neuron1.setNeuronCenter(X, Y);
neurons.push_back(&neuron1); 

neuronLIF neuron2;
neuron2.setNeuronId("neuron2");
neuron2.setDebug(false);
neuron2.save2File(false);
neuron2.setNeuronCenter(X, Y);
neurons.push_back(&neuron2); 

neuronLIF neuron3;
neuron3.setNeuronId("neuron3");
neuron3.setDebug(false);
neuron3.save2File(false);
neuron3.setNeuronCenter(X, Y);
neurons.push_back(&neuron3); 

neuronLIF neuron4;
neuron4.setNeuronId("neuron4");
neuron4.setDebug(false);
neuron4.save2File(false);
neuron4.setNeuronCenter(X, Y);
neurons.push_back(&neuron4); 

neuronLIF neuron5;
neuron5.setNeuronId("neuron5");
neuron5.setDebug(false);
neuron5.save2File(false);
neuron5.setNeuronCenter(X, Y);
neurons.push_back(&neuron5); 

neuronLIF neuron6;
neuron6.setNeuronId("neuron6");
neuron6.setDebug(false);
neuron6.save2File(false);
neuron6.setNeuronCenter(X, Y);
neurons.push_back(&neuron6); 

neuronLIF neuron7;
neuron7.setNeuronId("neuron7");
neuron7.setDebug(false);
neuron7.save2File(false);
neuron7.setNeuronCenter(X, Y);
neurons.push_back(&neuron7); 

neuronLIF neuron8;
neuron8.setNeuronId("neuron8");
neuron8.setDebug(false);
neuron8.save2File(false);
neuron8.setNeuronCenter(X, Y);
neurons.push_back(&neuron8); 

neuronLIF neuron9;
neuron9.setNeuronId("neuron9");
neuron9.setDebug(false);
neuron9.save2File(false);
neuron9.setNeuronCenter(X, Y);
neurons.push_back(&neuron9); 

neuronLIF neuron10;
neuron10.setNeuronId("neuron10");
neuron10.setDebug(false);
neuron10.save2File(false);
neuron10.setNeuronCenter(X, Y);
neurons.push_back(&neuron10); 

neuronLIF neuron11;
neuron11.setNeuronId("neuron11");
neuron11.setDebug(false);
neuron11.save2File(false);
neuron11.setNeuronCenter(X, Y);
neurons.push_back(&neuron11); 

neuronLIF neuron12;
neuron12.setNeuronId("neuron12");
neuron12.setDebug(false);
neuron12.save2File(false);
neuron12.setNeuronCenter(X, Y);
neurons.push_back(&neuron12); 


numNeurons = neurons.size();

    yarpDefault network(inputPortName, imagePortName, outputPrt);

    yarp::os::Bottle outBottle;
    network.output = outBottle;
        


    Bottle *tempData;

    
//    rf1.multiplyWeights(0.5);
    while(run)
    {        

              //  cout << "Reading from port" << endl;
                tempData = network.inputPort.read();
              //  cout << "Read from port" << endl;

                Bottle *mn = tempData->get(0).asList(); //read main list from bottle

                int size = 0;
                size = mn->size();
                double currentToUpdate = 0;
                //cout << size << endl;                
                
                vector <double> potentials;
                potentials.resize(numNeurons);
                double maxPotential = 0.5;
                int indexMax = -1;

                for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
                {
                    receptiveField *rField = receptiveFields.at(rfUpdate);
                    neuronLIF *neuron = neurons.at(rfUpdate);                  


                    for (int s = 0; s < size; s++)
                    {

                        Bottle *cur = mn->get(s).asList(); //get each sublist  

                        string type = cur->find("type").asString().c_str(); //for each sublist get type
                        int X = cur->find("posX").asInt();
                        int Y = cur->find("posY").asInt();
                        int pol = cur->find("polarity").asInt();
                        int channel = cur->find("channel").asInt();
            

                        Bottle &outB = network.outputNeuronStatePort.prepare();
                        outB.clear();
                    
                        outB.addDouble(neuron->getPotential());

                        if(verbose)
                        {
                            cout << "[main]: Updating neuron: " << rfUpdate << " from total " << numNeurons << "." << endl;
                            cout << "[main]: Updating neuron with ID: " << neuron->getNeuronId() << endl;
                        }
                       
                        if ((X < neuron->getCenterX()+16) && (X > neuron->getCenterX()-16) && (Y < neuron->getCenterY()+16) && (Y > neuron->getCenterY()-16) )
                        {

                            double toUpdateX = neuron->getCenterX() - X + 16;
                            double toUpdateY = neuron->getCenterY() - Y + 16;

                            if(toUpdateY < 16)
                                currentToUpdate = currentToUpdate+rField->getWeightAt(toUpdateX, toUpdateY+16);
                            else
                                currentToUpdate = currentToUpdate+rField->getWeightAt(toUpdateX, toUpdateY-16);


                            neuron->updateNeuron(currentToUpdate);                            
// /*
                            potentials.at(rfUpdate) = neuron->getPotential();                            
                        }
                    }
//                    cout << potentials.at(rfUpdate) << endl;
                    if(potentials.at(rfUpdate) > maxPotential)
                    {                        
                        indexMax = rfUpdate;
                        maxPotential = potentials.at(rfUpdate);
                    }
                    cout << maxPotential << endl;
                }
                
                if(indexMax > -1)
                {
                    receptiveField *rfToShow = receptiveFields.at(indexMax);
                    for (int x = 0; x < 32; x++)
                    {
                        for (int y = 0; y < 32; y++) 
                        {
                            yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(X-16+x, Y-16+y);
                                      //network.imageToWrite.pixel(64-x+16, 64-y+16) = 127+neuron1.getPotential()*rf1.getWeightAt(x, y);
                            if (y < 16)
                            {
                                pixel.r = 127+100*(rfToShow->getWeightAt(x,y+16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                pixel.g = 127+100*(rfToShow->getWeightAt(x,y+16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                pixel.b = 127+100*(rfToShow->getWeightAt(x,y+16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y))); 
                            }
                            else
                            {
                                pixel.r = 127+100*(rfToShow->getWeightAt(x,y-16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                pixel.g = 127+100*(rfToShow->getWeightAt(x,y-16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                pixel.b = 127+100*(rfToShow->getWeightAt(x,y-16)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));  
                            }
                        }   
                    }

                }
                else
                {
                    for (int x = 0; x < 32; x++)
                    {
                        for (int y = 0; y < 32; y++) 
                        {
                            yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(X-16+x, Y-16+y);
                                      //network.imageToWrite.pixel(64-x+16, 64-y+16) = 127+neuron1.getPotential()*rf1.getWeightAt(x, y);
                            pixel.r = 0; 
                            pixel.g = 0; 
                            pixel.b = 0; 
                        }   
                    }

                }

// *    /

                if(network.outputNeuronStatePort.getOutputCount())
                        network.outputNeuronStatePort.write();

                  
                network.imagePort.write(network.imageToWrite);


       } 
    //    system("PAUSE");
    
    return EXIT_SUCCESS;
}

/*
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




        weightsFile1 = "./curvedRFs/curvedRF1.txt";

        weightsFile2 = "./curvedRFs/curvedRF2.txt";

        weightsFile3 = "./curvedRFs/curvedRF3.txt";

        weightsFile4 = "./curvedRFs/curvedRF4.txt";

        weightsFile5 = "./curvedRFs/curvedRF5.txt";

        weightsFile6 = "./curvedRFs/curvedRF6.txt";

        weightsFile7 = "./curvedRFs/curvedRF7.txt";

        weightsFile8 = "./curvedRFs/curvedRF8.txt";

        weightsFile9 = "./curvedRFs/curvedRF9.txt";

        weightsFile10 = "./curvedRFs/curvedRF10.txt";

        weightsFile11 = "./curvedRFs/curvedRF11.txt";

        weightsFile12 = "./curvedRFs/curvedRF12.txt";

        weightsFile13 = "./curvedRFs/curvedRF13.txt";

        weightsFile14 = "./curvedRFs/curvedRF14.txt";

        weightsFile15 = "./curvedRFs/curvedRF15.txt";

        weightsFile16 = "./curvedRFs/curvedRF16.txt";

        weightsFile17 = "./curvedRFs/curvedRF17.txt";

        weightsFile18 = "./curvedRFs/curvedRF18.txt";

        weightsFile19 = "./curvedRFs/curvedRF19.txt";

        weightsFile20 = "./curvedRFs/curvedRF20.txt";

        weightsFile21 = "./curvedRFs/curvedRF21.txt";

        weightsFile22 = "./curvedRFs/curvedRF22.txt";

        weightsFile23 = "./curvedRFs/curvedRF23.txt";

        weightsFile24 = "./curvedRFs/curvedRF24.txt";
// */
