#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <time.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <yarp/dev/Drivers.h>
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/PolyDriver.h>

YARP_DECLARE_DEVICES(icubmod)

//#include "unmask.h"
#include "eventCodec.h"
#include "eventBottle.h"
#include "IzhikevicNeuron.h"

int main(int numArgs, char** args)
{
	YARP_REGISTER_DEVICES(icubmod)
	int last_t_display;
	int firstTimeStamp;
	yarp::os::Network yarp;
	std::string filename = "dvs_hand_states.txt";

	yarp::sig::Vector leftHandWeights; leftHandWeights.resize(128*128); leftHandWeights.zero();
	yarp::sig::Vector rightHandWeights; rightHandWeights.resize(128*128); rightHandWeights.zero();
		
	yarp::sig::Vector handNeurons;
	handNeurons.resize(1000);
	
	
	
	for (int x=0; x < 10; x++)
	{	
		for (int y=0; y < 10; y++)
		{
			for (int z=0; z < 10; z++)
			{
				handNeurons[10*x+10*y+z] = 0;
			}
		}
	}

	yarp::sig::ImageOf<yarp::sig::PixelRgb> image_hand_neurons;
	image_hand_neurons.resize(70,70);	
	yarp::os::Port image_hand_neurons_port;
	image_hand_neurons_port.open("/image_hand_neurons");

	yarp::sig::ImageOf<yarp::sig::PixelRgb> image_hand_weights;
	image_hand_weights.resize(128,128);	
	yarp::os::Port image_hand_weights_port;
	image_hand_weights_port.open("/image_hand_weights");	
	
	IzhikevicNeuron izhHandNeurons[70][70];
	IzhikevicNeuron handIzhNeuronLeft, handIzhNeuronRight;

  // File for outputing the data
	FILE *output_file;
  	output_file = fopen (filename.c_str(), "w");
	if (output_file == NULL) 
	    perror ("Error opening file");
  
  // We create the port in which we will receive the DVS events
  	yarp::os::BufferedPort<eventBottle> dvs_port;
  	eventBottle *evBottle;

  // We set its name
  	std::string local_dvs_port_name = "/dvsReadLocalHandLearning:i";
  	(dvs_port).open(local_dvs_port_name.c_str());
  	printf("Created port %s to get data from DVS!!\n\n", local_dvs_port_name.c_str());

  // And we try to connect it to the port generating the events
  	std::string remote_dvs_port_name = "/aexGrabber/eventBottle:o";
  	bool connectionOk = yarp.connect(remote_dvs_port_name.c_str(), local_dvs_port_name.c_str());

  	printf("Waiting for aexGrabber port to go alive!!!\n");	
  	while (!connectionOk){
    		connectionOk = yarp.connect(remote_dvs_port_name.c_str(), local_dvs_port_name.c_str());
  	}
  	printf("Connected to iCub's DVS port\n");

	yarp::dev::PolyDriver	client;	
	yarp::dev::PolyDriver	clientRight;	
	yarp::dev::IPositionControl *ipos;
	yarp::dev::IPositionControl *iposRight;
	
	yarp::os::Property option("(device remote_controlboard)");
	option.put("remote","/icub/left_arm");
	option.put("local","/cartesian_client/left_arm");
	
	if(!client.open(option))
		{printf("Cartestian controller not running! Quitting now. \n"); return(0);}
	
	client.view(ipos);
	
//	yarp::os::Property option("(device remote_controlboard)");
	option.put("remote","/icub/right_arm");
	option.put("local","/cartesian_client/right_arm");
	
	if(!clientRight.open(option))
		{printf("Cartestian controller not running! Quitting now. \n"); return(0);}
	
	clientRight.view(iposRight);


	yarp::os::BufferedPort<yarp::os::Bottle> handPose;
 	yarp::os::Bottle *handPos;

 // We set its name
  	std::string local_hand_port_name = "/handReadLocal:i";
  	(handPose).open(local_hand_port_name.c_str());
  	printf("Created port %s to get data from hand motion!!\n\n", local_hand_port_name.c_str());

 // And we try to connect it to find hand position

// And we try to connect it to the port generating the events
  	std::string remote_hand_port_name = "/icub/cartesianController/left_arm/state:o";
  	connectionOk = yarp.connect(remote_hand_port_name.c_str(), local_hand_port_name.c_str());

  	printf("Waiting for hand port to go alive!!!  Check if robotInterface/iCubInterface is running! %d\n", connectionOk);	
  	while (!connectionOk){
    		connectionOk = yarp.connect(remote_hand_port_name.c_str(), local_hand_port_name.c_str());
  	}
  	printf("Connected to iCub's hand port\n");


////////////////////////////////////////////////////////////////////////////////////
	yarp::os::BufferedPort<yarp::os::Bottle> handEvents;


  	std::string local_hand_events_port_name = "/handReadEvents:i";
  	(handEvents).open(local_hand_events_port_name.c_str());
  	printf("Created port %s to get data from hand events!!\n\n", local_hand_events_port_name.c_str());

 // And we try to connect it to the port generating the events
  	std::string remote_hand_events_port_name = "/icub/cartesianController/left_arm/events:o";
  	connectionOk = yarp.connect(remote_hand_events_port_name.c_str(), local_hand_events_port_name.c_str());

  	printf("Waiting for hand port to go alive!!!  Check if robotInterface/iCubInterface and iKinCartesianSolver  is running! %d\n", connectionOk);	
  	while (!connectionOk){
    		connectionOk = yarp.connect(remote_hand_events_port_name.c_str(), local_hand_events_port_name.c_str());
  	}
  	printf("Connected to iCub's hand events port\n");
  
	
  // Variable controlling the loop
  	bool run = true;

  // Variables that will hold the coordinates of the collisions
	double minX = 0; double minY = 0; double minZ = 0;
	double maxX = 0; double maxY = 0; double maxZ = 0;

  	int numIters = 0;

  	while(run){

		image_hand_neurons.zero();
		evBottle = dvs_port.read();
		handPos = handPose.read();
		
		double handX = ((*handPos).get(0).asDouble()*100) + 35;
		double handY = ((*handPos).get(1).asDouble()*100) + 35;	
		double handZ = ((*handPos).get(2).asDouble()*100) + 35;
		
		if ( ((*handPos).get(0).asDouble()*100) < minX)
		{
			minX = ((*handPos).get(0).asDouble()*100);
		}
		if ( ((*handPos).get(1).asDouble()*10) < minY)
		{
			minY = ((*handPos).get(1).asDouble()*100);
		}
		if ( ((*handPos).get(2).asDouble()*10) < minZ)
		{
			minZ = ((*handPos).get(2).asDouble()*100);
		}
	//	std::printf("Min Hand Location: %f:%f:%f \n", minX, minY, minZ);
		

		if ( ((*handPos).get(0).asDouble()*100) > maxX)
		{
			maxX = ((*handPos).get(0).asDouble()*100);
		}
		if ( ((*handPos).get(1).asDouble()*100) > maxY)
		{
			maxY = ((*handPos).get(1).asDouble()*100);
		}
		if ( ((*handPos).get(2).asDouble()*100) > maxZ)
		{
			maxZ = ((*handPos).get(2).asDouble()*100);
		}
	//	std::printf("Max Hand Location: %f:%f:%f \n", maxX, maxY, maxZ);


		handNeurons[handX*10 + handY*10 + handZ] = handNeurons[handX*10 + handY*10 + handZ] + 1;    		
		
		bool movingLeft=true;
		bool movingRight=true;

		ipos->checkMotionDone(&movingLeft);
		iposRight->checkMotionDone(&movingRight);

		unsigned int t = yarp::os::Time::now();
		for (int xN=0; xN < 70; xN++)
		{
			for (int yN=0; yN < 70; yN++)
			{
				for (int zN=0; zN < 70; zN++)
				{
	
					double xhat = handX - xN;
					double yhat = handY - yN;
					double zhat = handZ - zN;

					double inputCurrent = 1000*(sqrt((xhat*xhat+yhat*yhat+zhat*zhat)))*exp(-sqrt(xhat*xhat+yhat*yhat)/2);
					izhHandNeurons[xN][yN].updatePotential(inputCurrent,t);
				//	printf("Updated potential\n");
					image_hand_neurons.pixel(xN, yN).r =  izhHandNeurons[xN][yN].getPotential()*5;		 			
				}
			}
		}	
		
		image_hand_neurons_port.write(image_hand_neurons);
		numIters++;
	    	yarp::os::Bottle *bottle = (*evBottle).get_packet();
	    	emorph::ecodec::eEventQueue q;
    	
    	int sizeOfQ;
    	
    	if(bottle){
			emorph::ecodec::eEvent::decode(*bottle, q);
	        	sizeOfQ = q.size();
    	}
    	else{
			sizeOfQ = 0;
    	}
    
    // If the number of events is lower than a predefined threshold, then we assume we are getting just noise, and we do nothing
    	if(sizeOfQ > 0){

		ipos->checkMotionDone(&movingLeft);
		iposRight->checkMotionDone(&movingRight);

      		int ev_x, ev_y, pol, channel, ev_t;

      		bool address_ev_found = false;
      		bool ts_found = false;
		bool first_ts_found = false;
		
      // We go through all the events
      		for (int ii = sizeOfQ-1; ii > -1; ii--){
	// We need the adress event first
				if (q[ii]->getType() == "AE"){
	  // We decode the event
	  				emorph::ecodec::AddressEvent *ev = static_cast<emorph::ecodec::AddressEvent*>(q[ii]); 
	  				if (ev->isValid()){
	    					ev_x = 127-ev->getX();
	    					ev_y = ev->getY();
	    					pol = ev->getPolarity();
	    					channel = ev->getChannel();
            					fprintf(output_file, "%d\n", ((ev_x/4)*32+(ev_y/4))*(pol+1));
	    					address_ev_found = true;
	  				}
				}
	// Once the addres event has been found, we look for the timestamp
				if (q[ii]->getType() == "TS" && address_ev_found){
	  // We decode the event
	  				emorph::ecodec::TimeStamp *ts = static_cast<emorph::ecodec::TimeStamp*>(q[ii]); 
	  				if (ts->isValid()){
	    					ev_t = ts->getStamp();
						if(!first_ts_found)
							firstTimeStamp = ev_t;

	    					ts_found = true;
						first_ts_found = true;
	  				}
				}

	// If we have both the adress and the timestamp, we update the trackers
				if(address_ev_found && ts_found){
	  				if(ev_x>=0 && ev_x <= 127 && ev_y>=0 && ev_y <= 127 && channel ==0){ //

						handIzhNeuronLeft.updatePotential((!movingLeft)*1000.0, ev_t);
						handIzhNeuronRight.updatePotential((!movingRight)*1000.0, ev_t);

						printf("Arm Moving?? = %d : %f : %f : %f\n", !movingRight, exp(-(ev_t-handIzhNeuronRight.getLastSpikeTime())/150), (ev_t-handIzhNeuronRight.getLastSpikeTime()), rightHandWeights[ev_x*128+ev_y] );
						if(!movingLeft)
						{
							leftHandWeights[ev_x*128+ev_y] = leftHandWeights[ev_x*128+ev_y] + 15*exp( -(ev_t-handIzhNeuronLeft.getLastSpikeTime() )/150);	
						}
						else
						{	
							leftHandWeights[ev_x*128+ev_y] = leftHandWeights[ev_x*128+ev_y] - 7 + 10*exp( -(ev_t-handIzhNeuronLeft.getLastSpikeTime()-ev_t )/150);
						}

						if(!movingRight)
						{
							rightHandWeights[ev_x*128+ev_y] = rightHandWeights[ev_x*128+ev_y] + 15*exp( -(ev_t-handIzhNeuronRight.getLastSpikeTime() )/150);	
						}
						else
						{	
							rightHandWeights[ev_x*128+ev_y] = rightHandWeights[ev_x*128+ev_y] - 7 + 10*exp( -(ev_t-handIzhNeuronRight.getLastSpikeTime() )/150);	
						}


						image_hand_weights.pixel(ev_y, ev_x).r = (leftHandWeights[ev_x*128+ev_y]>0)?leftHandWeights[ev_x*128+ev_y]:0;
//						image_hand_weights.pixel(ev_y, ev_x).r = image_hand_weights.pixel(ev_y, ev_x).r - rightHandWeights[ev_x*128+ev_y];						
						image_hand_weights.pixel(ev_y, ev_x).b = (rightHandWeights[ev_x*128+ev_y]>0)?rightHandWeights[ev_x*128+ev_y]:0;											

          				}
	  				address_ev_found = false;
	  				ts_found = false;
	  				if(ev_t - last_t_display >= 0 || ev_t - last_t_display < 0){
	    // We update the images of the ellipses
	    				//	last_t_display = ev_t;
	  				}
				}
			}
		} image_hand_weights_port.write(image_hand_weights);
	}
	fclose(output_file);	
}
