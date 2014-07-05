// Author: Himanshu Akolkar

// Code for getting receptive fields and applying them on iCub with DVS input.


#include "receptiveField.h"
#include <fstream>

using namespace yarp::os;

receptiveField::receptiveField()
{

// Initializing with parameters for a typical pyramidal cell
size = 32;
weightVector.resize(size*size);
    //ctor
}

receptiveField::~receptiveField()
{
    //dtor
}

void receptiveField::setWeights(std::string filename, yarp::sig::Vector weightvector, int fieldSize)
{
	std::ifstream fid;
	fid.open(filename.c_str());
	
	for(int n=0; n < fieldSize*fieldSize; n++)
	{
		fid >> weightVector[n];
	}
}


