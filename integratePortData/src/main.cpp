#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <sstream>
#include <math.h>


#include <vector>

#include <yarp/sig/all.h>
#include <yarp/os/Time.h>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>

#include <cv.h>
#include <cvaux.h>
#include <highgui.h>


using namespace std;
using namespace yarp::os;

using namespace yarp::sig;
using namespace yarp::sig::draw;
using namespace yarp::sig::file;

using namespace cv;

int main(int argc, char *argv[])
{

ImageOf<PixelRgb> imageBall;
yarp::sig::file::read(imageBall,"ballImg.ppm");

ImageOf<PixelRgb> imageRubiks;
yarp::sig::file::read(imageRubiks,"rubiksImg.ppm");

ImageOf<PixelRgb> imageNone;
imageNone.resize(300,300);


//********* TO DO : Need too remove this to a for loop. Vector push_back not working for some reason.

Network yarp;

int numRFs = 13;

vector<double> potentials;
vector<double> none; 
vector<double> rubiks; 
vector<double> ball; 

potentials.resize(numRFs);
none.resize(numRFs);
rubiks.resize(numRFs);
ball.resize(numRFs);

none.at(0)=0.4; none.at(1)=0.31; none.at(2)=0.655; none.at(3)=0.328; none.at(4)=0.443;
none.at(5)=0.238; none.at(6)=0.423; none.at(7)=0.446; none.at(8)=0.386; none.at(9)=0.3807;
none.at(10)=0.413; none.at(11)=0.337; none.at(12)=0.413; 

rubiks.at(0)=4.80; rubiks.at(1)=6.475; rubiks.at(2)=6.33; rubiks.at(3)=7.23; rubiks.at(4)=0.8194;
rubiks.at(5)=0.7645; rubiks.at(6)=0.9549; rubiks.at(7)=0.7023; rubiks.at(8)=0.7952; rubiks.at(9)=1.0103;
rubiks.at(10)=0.7848; rubiks.at(11)=0.6680; rubiks.at(12)=0.7848;

ball.at(0)=4.86; ball.at(1)=6.02; ball.at(2)=6.03; ball.at(3)=7.28; ball.at(4)=0.8026;
ball.at(5)=0.8056; ball.at(6)=1.0193; ball.at(7)=0.7575; ball.at(8)=0.9064; ball.at(9)=1.1285;
ball.at(10)=0.8812; ball.at(11)=0.702; ball.at(12)=0.8812;


yarp::os::Bottle outBottle;
yarp::os::BufferedPort<Bottle> out; out.open("/featuresOut");

yarp::os::BufferedPort< ImageOf<PixelRgb> > object; object.open("/objectClass");

yarp::os::BufferedPort<Bottle> out1; out1.open("/temp1"); yarp::os::BufferedPort<Bottle> out13; out13.open("/temp13");
yarp::os::BufferedPort<Bottle> out14; out14.open("/temp14");
yarp::os::BufferedPort<Bottle> out3; out3.open("/temp3"); yarp::os::BufferedPort<Bottle> out15; out15.open("/temp15");
yarp::os::BufferedPort<Bottle> out4; out4.open("/temp4"); yarp::os::BufferedPort<Bottle> out16; out16.open("/temp16");
yarp::os::BufferedPort<Bottle> out5; out5.open("/temp5"); yarp::os::BufferedPort<Bottle> out17; out17.open("/temp17");
yarp::os::BufferedPort<Bottle> out6; out6.open("/temp6"); yarp::os::BufferedPort<Bottle> out18; out18.open("/temp18");
yarp::os::BufferedPort<Bottle> out7; out7.open("/temp7"); yarp::os::BufferedPort<Bottle> out19; out19.open("/temp19");
yarp::os::BufferedPort<Bottle> out8; out8.open("/temp8"); yarp::os::BufferedPort<Bottle> out20; out20.open("/temp20");
yarp::os::BufferedPort<Bottle> out9; out9.open("/temp9"); 
yarp::os::BufferedPort<Bottle> out10; out10.open("/temp10");
yarp::os::BufferedPort<Bottle> out11; out11.open("/temp11");
yarp::os::BufferedPort<Bottle> out12; out12.open("/temp12");
yarp::os::BufferedPort<Bottle> out2; out2.open("/temp2"); 


yarp.connect("/outputRF1", "/temp1"); yarp.connect("/outputRF12", "/temp12");
yarp.connect("/outputRF2", "/temp2");
yarp.connect("/outputRF13", "/temp13");
yarp.connect("/outputRF3", "/temp3"); yarp.connect("/outputRF14", "/temp14");
yarp.connect("/outputRF4", "/temp4"); yarp.connect("/outputRF15", "/temp15");
yarp.connect("/outputRF5", "/temp5"); 
yarp.connect("/outputRF6", "/temp6"); yarp.connect("/outputRF17", "/temp17");
yarp.connect("/outputRF7", "/temp7"); yarp.connect("/outputRF18", "/temp18");
yarp.connect("/outputRF8", "/temp8"); yarp.connect("/outputRF19", "/temp19");
yarp.connect("/outputRF9", "/temp9"); yarp.connect("/outputRF20", "/temp20");
yarp.connect("/outputRF10", "/temp10"); 
yarp.connect("/outputRF11", "/temp11"); 


	int countBall = 0;
	int countCube = 0;
	int countNone = 0;

//    rf1.multiplyWeights(0.5);
bool run = true;

while(run)
{        
	Bottle *neuron1 = out1.read(); 
	Bottle *neuron2 = out2.read(); 
	Bottle *neuron3 = out3.read(); 
	Bottle *neuron4 = out4.read(); 
	Bottle *neuron5 = out5.read(); 
	Bottle *neuron6 = out6.read(); 
	Bottle *neuron7 = out7.read();
	Bottle *neuron8 = out8.read();
	Bottle *neuron9 = out9.read();
	Bottle *neuron10 = out10.read();
	Bottle *neuron11 = out11.read();		
	Bottle *neuron12 = out12.read();
	Bottle *neuron13 = out13.read();
	Bottle *neuron14 = out14.read();
	Bottle *neuron15 = out15.read();
//	Bottle *neuron16 = out16.read();
	Bottle *neuron17 = out17.read();
	Bottle *neuron18 = out18.read();
	Bottle *neuron19 = out19.read();
	Bottle *neuron20 = out20.read();


ImageOf<PixelRgb> &img = object.prepare();

Bottle &oB = out.prepare();

outBottle.clear();

double activity = 0;

for (int r = 0; r < 6; r++) // number of RFs
	{		
// 	 potentials.at(r) = neuron1->get(r).asDouble()+neuron7->get(r).asDouble() + neuron3->get(r).asDouble() + neuron4->get(r).asDouble()+neuron5->get(r).asDouble()+neuron6->get(r).asDouble()+neuron7->get(r).asDouble()+neuron8->get(r).asDouble()+neuron9->get(r).asDouble()+neuron10->get(r).asDouble()+neuron11->get(r).asDouble()+neuron12->get(r).asDouble()+neuron13->get(r).asDouble()+neuron14->get(r).asDouble()+neuron15->get(r).asDouble()+neuron17->get(r).asDouble()+neuron18->get(r).asDouble();

     double t1 = neuron7->get(r).asDouble()+neuron8->get(r).asDouble() + neuron9->get(r).asDouble() + neuron10->get(r).asDouble()+neuron11->get(r).asDouble();

     double t2 = neuron1->get(r).asDouble()+neuron3->get(r).asDouble() + neuron4->get(r).asDouble() + neuron5->get(r).asDouble()+neuron6->get(r).asDouble();

     double t3 = neuron12->get(r).asDouble()+neuron13->get(r).asDouble() + neuron14->get(r).asDouble() + neuron15->get(r).asDouble()+neuron17->get(r).asDouble();

     double t4 = neuron18->get(r).asDouble()+neuron19->get(r).asDouble() + neuron20->get(r).asDouble();

potentials.at(r) = (t1 + t2 + t3 + t4 );
activity+=potentials.at(r);
//outBottle.addDouble(potentials.at(r));
}

double sumVal = 0;

for (int r = 0; r < 6; r++) // number of RFs
{
    sumVal += potentials.at(r);
}

for (int r = 0; r < 6; r++) // number of RFs
{
    outBottle.addDouble(potentials.at(r));
}
outBottle.addDouble(sumVal);

double meanPotential = 0;

double n = 3*potentials.at(0) + 3*potentials.at(1) + 3*potentials.at(2);
double m = 3*potentials.at(3) + 3*potentials.at(4) + 3*potentials.at(5);

outBottle.addDouble(n);
outBottle.addDouble(m);

oB = outBottle;

if(out.getOutputCount())
        out.write();

if(n >10 && activity > 40 && m > 10)
{
//	for (int r = 0; r < 2; r++)
//	{
		
//		outBottle.addDouble(potentials.at(0));

//		outBottle.addDouble(potentials.at(3));

//		outBottle.addDouble(potentials.at(1));

//		outBottle.addDouble(potentials.at(2));

//		outBottle.addDouble(potentials.at(4));

//		outBottle.addDouble(potentials.at(5));
//	}

	double diffNone; double diffRubiks; double diffBall;
	diffNone = 0; diffRubiks = 0; diffBall = 0;


    //outBottle.addDouble(n);
    //outBottle.addDouble(m);
	

/*    for (int r = 0; r < numRFs; r++)
	{
		diffNone += (none.at(r)-potentials.at(r))*(none.at(r)-potentials.at(r));
		diffRubiks += (rubiks.at(r)-potentials.at(r))*(rubiks.at(r)-potentials.at(r));
		diffBall += (ball.at(r)-potentials.at(r))*(ball.at(r)-potentials.at(r));
	}
// */


//	cout << diffNone << " " << diffRubiks << " " <<  diffBall << " " << activity << " " << n << endl;

 /*
	if(diffRubiks < diffNone && diffRubiks < diffBall)
	{
		cout << "------------------Rubiks" << endl;
		img = imageRubiks;
		if(object.getOutputCount())
			object.write();
	
	}
	else if (diffBall < diffNone)
	{
		cout << "******************Ball" << endl;
		img = imageBall;
		if(object.getOutputCount())
			object.write();

	}
	else
	{
		cout << "None" << endl;
		img = imageNone;
		if(object.getOutputCount())
			object.write();
	}
	// */

if(countBall <= 0)
	countBall = 0;

if(countCube <= 0)
	countCube = 0;

if(countNone <= 0)
	countNone = 0;

    if(n/m > 1)
	{
		countBall++;
		
        //cout << "------------------Ball" << " " << (n*n/(m)) << " " << (m*m/(n)) << endl;
		img = imageBall;
        if(countBall > 0)
		{	if(object.getOutputCount())
				object.write();

		countCube--;
		countNone--;
        //Time::delay(3);
		}
	}
    else if (n/m > 0.5)
	{

		countCube++;

        //cout << "******************Rubiks" << " " << (n*n/(m)) << " " << (m*m/(n)) << endl;
		img = imageRubiks;
        if(countCube > 0)
		{
		if(object.getOutputCount())
			object.write();

		countBall--;
		countNone--;		
        //Time::delay(3);
		}
	}
	else
	{
		cout << "None" << endl;

		countNone++;
		
        if(countNone > 0)
		{
		img = imageNone;
		if(object.getOutputCount())
			object.write();

		countCube--;
		countBall--;

		}
	}

//outBottle.addDouble(activity);
//cout << activity << endl;


	}
}
}
