
// Author: Himanshu Akolkar
 
// Code for getting receptive fields and applying them on iCub with DVS input.
 
 
#include "receptiveField.h"
#include <fstream>
 
using namespace yarp::os;
 
receptiveField::receptiveField()
{
 
// Initializing with parameters for a typical pyramidal cell
//size = 32;
fieldSizeX = 32;
fieldSizeY = 32;
valid = true;
weightVector.resize(fieldSizeX*fieldSizeY);
 
 
    //ctor
}
 
receptiveField::~receptiveField()
{
    //dtor
}
 
bool receptiveField::setFieldSize(int x, int y)
{
    fieldSizeX = x;
    fieldSizeY = y;
    return true;   
}
 
int receptiveField::getFieldSizeX()
{
    return fieldSizeX;
}
 
int receptiveField::getFieldSizeY()
{
    return fieldSizeY;
}
 
 bool receptiveField::normalizeWeights()
 {
    double sum = 0;
    for(int n=0; n < fieldSizeX*fieldSizeY; n++)
    {
        sum+=weightVector[n];
    }
     
     
    for(int n=0; n < fieldSizeX*fieldSizeY; n++)
    {
        weightVector[n] /= sum ;
    }
    return true;
     
 }
 
 bool receptiveField::multiplyWeights( double factor)
 {
     
    for(int n=0; n < fieldSizeX*fieldSizeY; n++)
    {
        weightVector[n] *= factor ;
    }
     
 }
   
bool receptiveField::isValid()
{
    return valid;
}
 
         
void receptiveField::setWeights()
{
    std::ifstream fid;
    fid.open(weightsFile.c_str());
     
    for(int n=0; n < fieldSizeX*fieldSizeY; n++)
    {
        fid >> weightVector[n];
    }
}
 
bool receptiveField::setWeightsFile(std::string filename)
{
    weightsFile = filename;
    valid = true;
    return true;
}
 
double receptiveField::getWeightAt(int x, int y)
{
    if(x > fieldSizeX || y > fieldSizeY)
    {
        return -1.0;
    }  
    return ( weightVector.at((x-1)*(fieldSizeX)+ y));
}

