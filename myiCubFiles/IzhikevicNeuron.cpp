#include "IzhikevicNeuron.h"

IzhikevicNeuron::IzhikevicNeuron()
{

// Initializing with parameters for a typical pyramidal cell
Vrest = -60;
Vthreshold = -40;
potential = Vrest;
a = 0.03;
b = -2;
c = -50;
d = 100;
k = 0.7;
C=100;
lastSpikeTime = 0;
numSpikes = 0;
    //ctor
}

IzhikevicNeuron::~IzhikevicNeuron()
{
    //dtor
}

double IzhikevicNeuron::getPotential()
{
return potential;
    //dtor
}

double IzhikevicNeuron::getLastSpikeTime()
{
return lastSpikeTime;
    //dtor
}

int IzhikevicNeuron::getNumSpikes()
{
return numSpikes;
    //dtor
}


bool IzhikevicNeuron::setParameters(double* parameters)
{
    int nargin = sizeof(parameters)/sizeof(double);

switch(nargin){
    case 1: a = parameters[0]; break;
    case 2: a = parameters[0]; b = parameters[1]; break;
    case 3: a = parameters[0]; b = parameters[1]; c = parameters[2]; break;
    case 4: a = parameters[0]; b = parameters[1]; c = parameters[2]; d = parameters[3]; break;
    case 5: a = parameters[0]; b = parameters[1]; c = parameters[2]; d = parameters[3]; k = parameters[4]; break;
    case 6: a = parameters[0]; b = parameters[1]; c = parameters[2]; d = parameters[3]; k = parameters[4]; tau = parameters[5]; break;
    case 7: a = parameters[0]; b = parameters[1]; c = parameters[2]; d = parameters[3]; k = parameters[4]; tau = parameters[5]; C = parameters[6]; break;
    default: break;
    }
    return 1;

}


bool IzhikevicNeuron::updatePotential(double inputCurrent, unsigned long int currentTime)
{
    double vdot = (k*(potential-Vrest)*(potential-Vthreshold) - inhibitor + (double) inputCurrent)/C;
    double udot = a*(b*(potential-Vrest)-inhibitor);

    potential = potential + vdot;
    inhibitor = inhibitor + udot;

    if (potential > Vthreshold){
        lastSpikeTime = (long unsigned int) currentTime;
        numSpikes = numSpikes+1;
        potential = c;
        inhibitor = inhibitor + d;
    }

    return 1;
}
