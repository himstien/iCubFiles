// STDP 2D DVS and HAND

// *** include standard header files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
//#include <signal.h>

// *** include yarp headers
#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>

//#include "IzhikevicNeuron.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;

Vector vecImageWeights;

int main(int argc, char** argv)
{
	unsigned long int initTimeSTDP = Time::now();
    bool verbose = false;

	ifstream file_readWeightsFile;
	file_readWeightsFile.open("weights2.dat", ifstream::in);
//    ofstream file_outFile, file_writeData;
    Network yarp;
	
	Vector weights;
	weights.resize(2476000,5);
	
	if(file_readWeightsFile) {
		file_readWeightsFile.seekg(0, file_readWeightsFile.end);
		int length = file_readWeightsFile.tellg();
		file_readWeightsFile.seekg(0, file_readWeightsFile.beg);
	
		char * buffer = new char [length];
		file_readWeightsFile.read(buffer, length);		
	
	for (int i=0; i < length; i++)
	{
		for(int j = 0; j < 10; j++){
		cout << buffer[i] << " ";
		}
		cout << endl;
	}
		cout << length << endl;
 }

file_readWeightsFile.close();


}

