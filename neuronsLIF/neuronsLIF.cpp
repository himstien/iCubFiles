
#include "neuronLIF.h"

class neuronLIF::neuronLIF()
{
// Init neuron related variables
	restingPotential = 0;
	potential = restingPotential;
	lastTimeStamp = 0;
	timeFromLastSpike = 0;
	totalSpikes = 0;
	initTimeStamp = 0;
	inputCurrent = 0;
	membraneTimeConstant = 1;
	
// Init display parameters
	display = false;
	
// Init file save parameters	
	updated = false;
	save2file = false;
	string fileName = "";
}

bool neuronLIF::updateNeuron(double curr)
{
	
}

bool neuronLIF::updateNeuron()
{
}

bool save2File()
{
}

unsigned int getTimeStamp()
{
	return lastTimeStamp;
}
	
	
	