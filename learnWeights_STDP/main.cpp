#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <time.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>

//#include "unmask.h"
#include "eventCodec.h"
#include "eventBottle.h"
#include "IzhikevicNeuron.h"

int main(int numArgs, char** args)
{
	int last_t_display;
	yarp::os::Network yarp;
	std::string filename = "dvsEvents.txt";

	yarp::os::vector tStamps;
	yarp::os::vector addressX;	
	yarp::os::vector addressY;	
	yarp::os::vector polarities;	

//	yarp::sig::ImageOf<yarp::sig::PixelRgb> image_hand_neurons;
//	image_hand_neurons.resize(70,70);	
//	yarp::os::Port image_hand_neurons_port;
//	image_hand_neurons_port.open("/image_hand_neurons");
	
//	IzhikevicNeuron izhHandNeurons[70][70];

  // File for outputing the data
	FILE *output_file;
  	output_file = fopen (filename.c_str(), "w");
	if (output_file == NULL) 
	    perror ("Error opening file");
  
  // We create the port in which we will receive the DVS events
  	yarp::os::BufferedPort<eventBottle> dvs_port;
  	eventBottle *evBottle;

  // We set its name
  	std::string local_dvs_port_name = "/dvsReadLocalLearning:i";
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


 // We set its name

  // Variable controlling the loop
  	bool run = true;

  // Variables that will hold the coordinates of the collisions
	double minX = 0; double minY = 0; double minZ = 0;
	double maxX = 0; double maxY = 0; double maxZ = 0;

  	int numIters = 0;

  	while(run){

		evBottle = dvs_port.read();
	
		unsigned int t = yarp::os::Time::now();

		numIters++;
    		yarp::os::Bottle *bottle = (*evBottle).get_packet();
    		emorph::ecodec::eEventQueue q;
    		int sizeOfQ;
    		if(bottle){
    			emorph::ecodec::eEvent::decode(*bottle, q);
        		sizeOfQ = q.size();
//	    		addressX.resize(sizeOfQ);
//	    		addressY.resize(sizeOfQ);
//	    		polarity.resize(sizeOfQ);
//	    		tStamps.resize(sizeOfQ);
    		}
    		else{
			sizeOfQ = 0;
    		}

    // If the number of events is lower than a predefined threshold, then we assume we are getting just noise, and we do nothing
    		if(sizeOfQ > 0){
      			int ev_x, ev_y, pol, channel, ev_t;

      			bool address_ev_found = false;
      			bool ts_found = false;
      // We go through all the events
      			for (int ii = 0; ii < sizeOfQ; ii++){
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
						addressX.push(ev_x);
						addressY.push(ev_y);
						polarity.push(pol);						
	  				}
				}
	// Once the addres event has been found, we look for the timestamp
				if (q[ii]->getType() == "TS" && address_ev_found){
	  // We decode the event
	  				emorph::ecodec::TimeStamp *ts = static_cast<emorph::ecodec::TimeStamp*>(q[ii]); 
	  				if (ts->isValid()){
	    					ev_t = ts->getStamp();
	    					ts_found = true;
						tStamps.push(ev_t);
	  				}
				}

	// If we have both the adress and the timestamp, we update the trackers
				if(address_ev_found && ts_found){
	  				if(ev_x>=0 && ev_x <= 127 && ev_y>=0 && ev_y <= 127){
          				}
	  				address_ev_found = false;
	  				ts_found = false;
	  				if(ev_t - last_t_display >= 0 || ev_t - last_t_display < 0){
	    // We update the images of the ellipses
	    					last_t_display = ev_t;
	  				}
				}
			}
		}
	}
	fclose(output_file);	
}
