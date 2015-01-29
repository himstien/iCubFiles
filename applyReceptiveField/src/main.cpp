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
using namespace emorph;

#define THRESHOLD 5.0

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
    string sourceEventsPort = rf.find("sourcePort").asString();

    double sampleBy = rf.find("sampleBy").asDouble();

    X = rf.find("X").asInt();
    Y = rf.find("Y").asInt();
 
    X = X/sampleBy + (64 - 128/(2*sampleBy));
    Y = Y/sampleBy + (64 - 128/(2*sampleBy));


    if(inputPortName == "")
        inputPortName = "/inputEvents";

    if(imagePortName == "")
        imagePortName = "/imageRF";

    if(outputPrt == "")
        outputPrt = "/outputState";

    if(X == 0)
         X = 64;
     
    if(Y == 0)
        Y = 80;

    if(sourceEventsPort == "")
        sourceEventsPort = "/aexGrabber/vBottle:o";
    

//********* TO DO : Need too remove this to a for loop. Vector push_back not working for some reason.

    vector<receptiveField*> receptiveFields;
    string weightsFile;
    //    receptiveFields.resize(24);
 
    receptiveField rf1;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF1.txt" ;
    rf1.setWeightsFile(weightsFile.c_str());
    rf1.setWeights();
//        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf1);

    receptiveField rf2;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF2.txt" ;
    rf2.setWeightsFile(weightsFile.c_str());
    rf2.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf2);


    receptiveField rf3;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF16.txt" ;
    rf3.setWeightsFile(weightsFile.c_str());
    rf3.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf3);

    receptiveField rf4;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF4.txt" ;
    rf4.setWeightsFile(weightsFile.c_str());
    rf4.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf4);

    receptiveField rf5;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF7.txt" ;
    rf5.setWeightsFile(weightsFile.c_str());
    rf5.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf5);

    receptiveField rf6;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF8.txt" ;
    rf6.setWeightsFile(weightsFile.c_str());
    rf6.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf6);

    receptiveField rf7;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF7.txt" ;
    rf7.setWeightsFile(weightsFile.c_str());
    rf7.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf7);

    receptiveField rf8;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF8.txt" ;
    rf8.setWeightsFile(weightsFile.c_str());
    rf8.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf8);

    receptiveField rf9;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF9.txt" ;
    rf9.setWeightsFile(weightsFile.c_str());
    rf9.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf9);

    receptiveField rf10;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF10.txt" ;
    rf10.setWeightsFile(weightsFile.c_str());
    rf10.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf10);

    receptiveField rf11;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF11.txt" ;
    rf11.setWeightsFile(weightsFile.c_str());
    rf11.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    receptiveFields.push_back(&rf11);

    receptiveField rf12;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF12.txt" ;
    rf12.setWeightsFile(weightsFile.c_str());
    rf12.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf12);

    receptiveField rf13;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF13.txt" ;
    rf13.setWeightsFile(weightsFile.c_str());
    rf13.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf13);

    receptiveField rf14;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF14.txt" ;
    rf14.setWeightsFile(weightsFile.c_str());
    rf14.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf14);

    receptiveField rf15;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF15.txt" ;
    rf15.setWeightsFile(weightsFile.c_str());
    rf15.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf15);

    receptiveField rf16;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF16.txt" ;
    rf16.setWeightsFile(weightsFile.c_str());
    rf16.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf16);

    receptiveField rf17;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF17.txt" ;
    rf17.setWeightsFile(weightsFile.c_str());
    rf17.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf17);

    receptiveField rf18;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF18.txt" ;
    rf18.setWeightsFile(weightsFile.c_str());
    rf18.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf18);

    receptiveField rf19;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF19.txt" ;
    rf19.setWeightsFile(weightsFile.c_str());
    rf19.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf19);

    receptiveField rf20;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF20.txt" ;
    rf20.setWeightsFile(weightsFile.c_str());
    rf20.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf20);

    receptiveField rf21;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF21.txt" ;
    rf21.setWeightsFile(weightsFile.c_str());
    rf21.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf19);

    receptiveField rf22;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF22.txt" ;
    rf22.setWeightsFile(weightsFile.c_str());
    rf22.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf22);

    receptiveField rf23;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF23.txt" ;
    rf23.setWeightsFile(weightsFile.c_str());
    rf23.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf23);

    receptiveField rf24;
    weightsFile = "/home/icub/robot/iCubFiles/applyReceptiveField/./curvedRFs/cRF24.txt" ;
    rf24.setWeightsFile(weightsFile.c_str());
    rf24.setWeights();
    //        cout << "Receptive Field " << r << " is valid? " <<  rf1.isValid() << endl;
    //receptiveFields.push_back(&rf24);

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
    //neurons.push_back(&neuron7);

    neuronLIF neuron8;
    neuron8.setNeuronId("neuron8");
    neuron8.setDebug(false);
    neuron8.save2File(false);
    neuron8.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron8);

    neuronLIF neuron9;
    neuron9.setNeuronId("neuron9");
    neuron9.setDebug(false);
    neuron9.save2File(false);
    neuron9.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron9);

    neuronLIF neuron10;
    neuron10.setNeuronId("neuron10");
    neuron10.setDebug(false);
    neuron10.save2File(false);
    neuron10.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron10);

    neuronLIF neuron11;
    neuron11.setNeuronId("neuron11");
    neuron11.setDebug(false);
    neuron11.save2File(false);
    neuron11.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron11);

    neuronLIF neuron12;
    neuron12.setNeuronId("neuron12");
    neuron12.setDebug(false);
    neuron12.save2File(false);
    neuron12.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron12);

    neuronLIF neuron13;
    neuron13.setNeuronId("neuron13");
    neuron13.setDebug(false);
    neuron13.save2File(false);
    neuron13.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron13);

    neuronLIF neuron14;
    neuron14.setNeuronId("neuron14");
    neuron14.setDebug(false);
    neuron14.save2File(false);
    neuron14.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron14);

    neuronLIF neuron15;
    neuron15.setNeuronId("neuron15");
    neuron15.setDebug(false);
    neuron15.save2File(false);
    neuron15.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron15);

    neuronLIF neuron16;
    neuron16.setNeuronId("neuron16");
    neuron16.setDebug(false);
    neuron16.save2File(false);
    neuron16.setNeuronCenter(X, Y);
    //neurons.push_back(&neuron16);



    numNeurons = neurons.size();

    yarpDefault network(inputPortName, imagePortName, outputPrt, sourceEventsPort);

    yarp::os::Bottle outBottle;
    network.output = outBottle;
        

    vBottle *tempData;
    vector <double> potentials;    
    potentials.resize(numNeurons);

    vector <double> spikes;
    spikes.resize(numNeurons);

    double maxPotential = THRESHOLD;
    int indexMax = -1;


	receptiveField *rField0 = receptiveFields.at(0);
	receptiveField *rField1 = receptiveFields.at(1);
	
	
//    rf1.multiplyWeights(0.5);
    while(run)
    {

        spikes.clear();
        spikes.resize(numNeurons);

        //  cout << "Reading from port" << endl;

        tempData = network.inputPort.read();
        //  cout << "Read from port" << endl;

        //create event queue
        emorph::vQueue q;
        //create queue iterator
        emorph::vQueue::iterator qi;

        bool collectEvents = true;
        int timeNow = time(0);
        //Bottle mn;// = tempData->get(0).asList(); //read main list from bottle;
        //Bottle events = tempData->get(0).asList();
        //mn = *events;

        // get the event queue in the vBottle bot
        tempData->getAll(q);

        //                cout << "Initial size  " << mn.size() << " events." << endl;

         /*
        while(collectEvents)
        {
            for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
            {
                neuronLIF *neuron = neurons.at(rfUpdate);
          //      neuron->resetNeuron();
            }

            int timeCurrent	= time(0);
            if ( timeCurrent - timeNow > 0) //mn.size() > 0 ||
            {
                collectEvents = false;
            }
            else
            {
                //				cout << "Wait time: " << timeCurrent - timeNow << endl;
                //tempData = network.inputPort.read();
                //Bottle *events = tempData->get(0).asList(); //read main list from bottle;
                //cout << "Appending " << events->size() << " events. " <<  endl;
                //mn.append(*events);
                //cout << mn.size() << endl;
            }
        }
        // */
        Bottle outB2;
        Bottle &outB = network.outputNeuronStatePort.prepare();
        outB.clear();

        //int size = 0;
        //size = mn.size();
        double currentToUpdate = 0;

        if(verbose)
            cout << "Processing " << q.size()<< " events." << endl;

        double sumCurrent = 0;
        for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
        {
            receptiveField *rField = receptiveFields.at(rfUpdate);
            neuronLIF *neuron = neurons.at(rfUpdate);
            //neuron->resetNeuron();

            for (qi = q.begin(); qi != q.end(); qi++)
            {

               // Bottle *cur = mn.get(s).asList(); //get each sublist

                unsigned int ev_t = (*qi)->getStamp();

                //string type = cur->find("type").asString().c_str(); //for each sublist get type
                //int posY = cur->find("posX").asInt();
                //int posX = cur->find("posY").asInt();
                //posY = 127-posY;
                //int pol = cur->find("polarity").asInt();
                //int channel = cur->find("channel").asInt();

                AddressEvent *aep = (*qi)->getAs<AddressEvent>();
                int posX    = aep->getX();
                int posY    = aep->getY(); posY = 127 - posY;
                int pol     = aep->getPolarity();
                int channel = aep->getChannel();

                //			if(rfUpdate == 1)
                //			{


                if(verbose)
                {
                    cout << "[main]: Updating neuron: " << rfUpdate << " from total " << numNeurons << "." << endl;
                    cout << "[main]: Updating neuron with ID: " << neuron->getNeuronId() << endl;
                }

                if ((posX < neuron->getCenterX()+16) && (posX > neuron->getCenterX()-16) && (posY < neuron->getCenterY()+16) && (posY > neuron->getCenterY()-16) && channel == 0 && pol == 1)
                {

                    double toUpdateX = posX - (neuron->getCenterX() - 16);
                    double toUpdateY = posY - (neuron->getCenterY() - 16);

                    currentToUpdate = rField->getWeightAt(toUpdateX, toUpdateY)* (pol*2-1);
                    sumCurrent += currentToUpdate;
                    //                            if(toUpdateY < 16)
                    //                                currentToUpdate = currentToUpdate+rField->getWeightAt(toUpdateX, toUpdateY+16);
                    //                            else
                    //                                currentToUpdate = currentToUpdate+rField->getWeightAt(toUpdateX, toUpdateY-16);


                    neuron->updateNeuron(currentToUpdate);

                    //neuron->updateNeuron(2);
                    // /*
                    potentials.at(rfUpdate) = neuron->getPotential();

                    //************  Debugging
                    // /*
                    //                            cout << "   Current now: " << currentToUpdate << " TotalCurrent: " << sumCurrent << " Potential: " << potentials.at(rfUpdate) << endl;
                    //                            cout << "   X: " << posX << " Y: " << posY << " Polarity: " << pol << " Weights: " << rField0->getWeightAt(toUpdateX, toUpdateY) + rField1->getWeightAt(toUpdateX, toUpdateY) << endl;
                   // yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(posX, posY);
                   // pixel.r = 0;
                   // pixel.g = 100+100*rField1->getWeightAt(toUpdateX, toUpdateY)*(pol*2-1);
                   // pixel.b = 100+100*rField0->getWeightAt(toUpdateX, toUpdateY)*(pol*2-1);

                    // */

                }
                network.imagePort.write(network.imageToWrite);
            }//end of bottle events

            outB2.addDouble(neuron->getPotential());
            //outB2.addDouble(spikes.at(rfUpdate));

            if(potentials.at(rfUpdate) > maxPotential)
            {
                indexMax = rfUpdate;
                maxPotential = potentials.at(rfUpdate);
            }

            //                 cout << " RfIndex: " << rfUpdate << " maxPotential: " << potentials.at(rfUpdate) << " index selected: " << indexMax << endl;

            //                    neuron->resetNeuron();

            // Add small dot at center of receptive field
            ///*
                                  for (int x = -2; x < 2; x++)
                                  {
                                      for (int y = -2; y < 2; y++)
                                      {
                                          yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(X+x, Y+y);
                                          pixel.r = 255;
                                          pixel.g = 0;
                                          pixel.b = 0;
                                       }
                                  }
                                  network.imagePort.write(network.imageToWrite);
              // */
        } // end of update of all neurons

        for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
        {
            neuronLIF *neuron = neurons.at(rfUpdate);
            cout << "RF" << rfUpdate << ": " << neuron->getNumSpikes() << " : " << neuron->getPotential() << " " ;
            //cout << spikes.at(rfUpdate) <<  " " << neuron->getNumSpikes() << " ";
        }
        cout << endl;

        if(indexMax > -1)
        {

            receptiveField *rfToShow = receptiveFields.at(indexMax);

            // Add receptive field to image

       //     /*
                                  for (int x = 0; x < 32; x++)
                                  {
                                      for (int y = 0; y < 32; y++)
                                      {
                                          yarp::sig::PixelRgb& pixel = network.imageToWrite.pixel(X-16+x, Y-16+y);
                                                    //network.imageToWrite.pixel(64-x+16, 64-y+16) = 127+neuron1.getPotential()*rf1.getWeightAt(x, y);

                                              pixel.r = 127+100*(rfToShow->getWeightAt(x,y)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                              pixel.g = 127+100*(rfToShow->getWeightAt(x,y)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));
                                              pixel.b = 127+100*(rfToShow->getWeightAt(x,y)); //abs(int(50.0*neuron->getPotential()*rf1.getWeightAt(x, y)));

                                      }
                                  }
              // */
            network.imagePort.write(network.imageToWrite);
            indexMax = -1;
            maxPotential = THRESHOLD;
            // Reset all neurons if one reaches threshold
            for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
            {
                neuronLIF *neuron = neurons.at(rfUpdate);
                //neuron->resetNeuron();
            }
        }
        else
        {
            // Clear image at receptive field

          //  /*
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
                                  network.imagePort.write(network.imageToWrite);


                           // */
            //                    maxPotential = maxPotential*0.95;

            for (int rfUpdate = 0; rfUpdate < numNeurons; rfUpdate++)
            {
                neuronLIF *neuron = neurons.at(rfUpdate);
                //neuron->resetNeuron();
            }
        }

        // *    /

        outB = outB2;
        if(network.outputNeuronStatePort.getOutputCount())
        {
            network.outputNeuronStatePort.write();
        }
        //			}
        outB2.clear();
    }
    //    system("PAUSE");

    return EXIT_SUCCESS;
}

