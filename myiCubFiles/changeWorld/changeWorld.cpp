#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>
//#include <random>
  /* Get all OS and signal processing YARP classes */
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

int main() {
	
//	std::default_random_engine generator;
//	std::normal_distribution<double> distribution(0.0, 10);

    Network yarp; // set up yarp
    Port ballMove;
    Port handPose;

    handPose.open("/handLocation");	
    ballMove.open("/ball_move");
    
    Network::connect("/handLocation", "/icubSim/world");	
    Network::connect("/ball_move", "/icubSim/world");

	Bottle getlhand("world get lhand");
    Bottle reply; Bottle del_all("world del all");
double radius = 0.05; double x=0; double y=0.95; double z=0.5; int r=1; int g=0; int b=0; 
    Bottle createBall("world mk ssph 0.03 0 0 0.5 1 0 0"); // create a sphere with params: radius (x y z) (r g b)
    ballMove.write(del_all, reply);
    ballMove.write(createBall, reply);

    Bottle grabBall("world grab ssph 1 left 1");
    ballMove.write(grabBall, reply);
	
	
    double timeStart = Time::now();

    while (1) { 
//	handPose.write(getlhand, reply);
//	cout << reply.toString() << endl;

	double t = Time::now() - timeStart;
	double dx = cos(3*t);
	double dy = sin(3*t);

	Bottle moveObj("world set ssph 1");
	moveObj.addDouble(x+dx/10);
	moveObj.addDouble(y+dy/10);
	moveObj.addDouble(z);
	ballMove.write(moveObj, reply);
	ballMove.write(grabBall, reply);
    }
    return 0;
}
