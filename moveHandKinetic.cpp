#include <math>
#include <iostream>

#include <yarp/os/all.h>

#define PI 3.141529

using namespace yarp::os;

int main()
{
	Network yarp;
	Port writeToArmCntrlr;
	writeToArmCntrlr.open("/sendToContrlr");
	yarp.connect("/sendToContrlr", "/armCtrl/left_arm/xd:i);	


	double x = -10;
	double y, z;

	Bottle b;
	b.clear(0);

	while(totalRuns < 1000)	
	{
		for (int thet = 0; thet < 2*PI; thet+=(5/180)*PI)
		{
			y = 5*cos(thet);
			z = 5*sin(thet);
			b.addDouble(x);	
			b.addDouble(y);	
			b.addDouble(z);
			writeToArmCntrlr.write(b);
			Time::delay(2);
			b.clear();	

		}

	}

}
