// Author: Himanshu Akolkar

// Code for getting receptive fields and applying them on iCub with DVS input.


#include "receptiveField.h"
#include <fstream>

using namespace yarp::os;

receptiveField::receptiveField()
{

// Initializing with parameters for a typical pyramidal cell
//size = 32;

weightVector.resize(size*size);
fieldSizeX = 32;
fieldSizeY = 32;


    //ctor
}

receptiveField::~receptiveField()
{
    //dtor
}

void receptiveField::setWeights(std::string filename, yarp::sig::Vector weightvector)
{
	std::ifstream fid;
	fid.open(filename.c_str());
	
	for(int n=0; n < fieldSizeX*fieldSizeY; n++)
	{
		fid >> weightVector[n];
	}
}

void receptiveField::getWeightAt(int x, int y)
{
    if(x > fieldSizeX || y > fieldSizeY)
    {
    }	
}


