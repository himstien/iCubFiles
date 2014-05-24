// Author: Himanshu Akolkar

// Library for getting receptive fields and applying them on iCub with DVS input.


#include "receptiveField.h"

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

void receptiveField::setWeights(string filename, vector weightvector, int fieldSize)
{
	File fid;
	fid.open(filename.c_str(), 'r');
	
	for(int n=0; n < fieldSize*fieldSize; n++)
	{
		weightVector[n] = fscanf(fid, %d, 1);
	}
}


