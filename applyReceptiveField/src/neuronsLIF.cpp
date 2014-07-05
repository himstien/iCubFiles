
#include "neuronsLIF.h"
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>

neuronLIF::neuronLIF()
{
// Init neuron related variables
	restingPotential = 0;
	potential = restingPotential;
	thresholdPotential = 1000;
	lastTimeStamp = 0;
	lastUpdateTime = 0;
	timeFromLastSpike = 0;
	totalSpikes = 0;
	initTimeStamp = 0;
//	inputCurrent = 0;
	membraneTimeConstant = 1;
	
	setInputCurrent();
// Init display parameters
	display = false;
	
// Init file save parameters	
	updated = false;
	save2file = false;
	neuronId = "defaultNeuron";
    fileName = neuronId + ".dat";
    //saveFid.is_open();
    
    if (save2file)
       saveFid.open(fileName.c_str());  
// Debug ??
   debug = true;
}

neuronLIF::~neuronLIF()
{
       saveFid.close();                
}

bool neuronLIF::updateNeuron()
{
     if (debug)
        std::cout << "[neuron LIF]: Dummy function called" << std::endl;

     double curr = 0;
     if (curr <= 0)
     {
              return false;
     }
     
     potential = potential; //*exp(-abs(delT)/membraneTimeConstant) + curr;
     lastUpdateTime = time(0);
     
     if(potential > thresholdPotential)
     {
                  potential = restingPotential;
                  lastTimeStamp = lastUpdateTime;
                  if(save2file) writeToFile();
                  return true;
     }
     else
     {     
           if(save2file) writeToFile();
           return false;
     }
}

bool neuronLIF::updateNeuron(double curr, unsigned int timeNow)
{
     if (debug)
          std::cout << "[neuron LIF]: Update neurons with current " << curr << " and time " << lastUpdateTime << " " << timeNow << " " << timeNow - lastUpdateTime<< "  " << std::endl;
     
     if (curr <= 0)
     {
              lastUpdateTime = timeNow;
              return false;
     }
     
     double delT = timeNow - lastUpdateTime;
     if (delT < 0) delT = - delT;
             
     potential = potential*exp(-(delT/membraneTimeConstant) ) + curr;
     lastUpdateTime = timeNow;
     
     if(potential > thresholdPotential)
     {
                  potential = restingPotential;
                  lastTimeStamp = lastUpdateTime;
                  if(save2file) writeToFile();
                  return true;
     }
     else
     {     
           if(save2file) writeToFile();
           return false;
     }	
}

bool neuronLIF::updateNeuron(double curr, double delT)
{
     if (debug)
        std::cout << "[neuron LIF]: Update neuron with current and delT" << std::endl;
     
     if (delT < 0) delT = - delT;

     if (curr <= 0)
     {
              lastUpdateTime = lastUpdateTime + (unsigned int)delT;
              return true;
     }
     
     
     potential = potential*exp(-(delT/membraneTimeConstant)) + curr;
     lastUpdateTime = lastUpdateTime + (unsigned int)delT;

     if(potential > thresholdPotential)
     {
                  potential = restingPotential;
                  lastTimeStamp = lastUpdateTime;
                  if(save2file) writeToFile();
                  return true;
     }
     else
     {     
           if(save2file) writeToFile();
           return false;
     }
}


bool neuronLIF::updateNeuron(double curr)
{
     if (debug)
          std::cout << "[neuron LIF]: Update neurons with current: " << curr << std::endl;

     if (curr <= 0)
     {
              return false;
     }
     
     potential = potential*exp(-0.01/membraneTimeConstant) + curr;
     lastUpdateTime = time(0);
     if (debug)
        std::cout << "[neuron LIF]: Update potential of neuron to " << potential << std::endl; 
     
     if(potential > thresholdPotential)
     {
                  potential = restingPotential;
                  lastTimeStamp = lastUpdateTime;
                  if(save2file) writeToFile();
                  return true;
     }
     else
     {     
           if(save2file) writeToFile();
           return false;
     }
}

void neuronLIF::save2File(bool value)
{
     if(debug)
     std::cout << "[neuron LIF]: Setting write option to " << value << std::endl;
     save2file = value;     
}

void neuronLIF::setDebug( bool value)
{
     debug = value;
}

unsigned int neuronLIF::getTimeStamp()
{
	return lastTimeStamp;
}

double neuronLIF::getPotential()
{
	return potential;
}	
	
void neuronLIF::setInputCurrent()
{
     inputCurrent = 0;
}	

bool neuronLIF::setInputCurrent(double curr)
{
     inputCurrent = curr;
     return true;
}

bool neuronLIF::setThresholdPotential(double threshold)
{
     thresholdPotential = threshold;
     return true;
}

void neuronLIF::writeToFile()
{
     if(debug)
     std::cout << "[neuron LIF]: writing to File" << std::endl;
     
     if(!saveFid.is_open())
                saveFid.open(fileName.c_str());
                
     if(save2file)
          saveFid << lastUpdateTime << " " << potential << " " << lastTimeStamp << std::endl;
}        

bool neuronLIF::setNeuronId(std::string value)
{
     neuronId = value;
     fileName = neuronId + ".dat";
     return true;
}
