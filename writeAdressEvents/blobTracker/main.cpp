#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>

//#include "unmask.h"
#include "eventCodec.h"
#include "eventBottle.h"
#include "blob_tracker.h"
#include "tracker_pool.h"

//#include "./iCubMotor/include/iCubMotor.h"

//using namespace aquilacubmotor;

int main(int numArgs, char** args)
{
  // Initial parameters of the Blob Tracker and the Tracker Pool
  std::string filename = "output.txt";
  
  if(numArgs > 1){
    filename = args[1];
  }

	
  // File for outputing the data
  FILE *output_file;
  output_file = fopen (filename.c_str(), "w");
  if (output_file == NULL) 
    perror ("Error opening file");
  
  // We create the trackers
  TrackerPool tracker_pool_left(sig_x, sig_y, sig_xy, alpha_pos, alpha_shape, k, 
				max_dist, fixed_shape, tau_act, up_thresh, down_thresh, 
				alpha_rep, d_rep, max_nb_trackers, nb_ev_reg);
  TrackerPool tracker_pool_right(sig_x, sig_y, sig_xy, alpha_pos, alpha_shape, k, 
				 max_dist, fixed_shape, tau_act, up_thresh, down_thresh, 
				 alpha_rep, d_rep, max_nb_trackers, nb_ev_reg);

  // Threshold for updating the position
  int min_nb_ev = 1;

  // We create the network
  yarp::os::Network yarp;
  

  // We create the port in which we will receive the DVS events
  yarp::os::BufferedPort<eventBottle> dvs_port;
  eventBottle *evBottle;
  // We set its name
  std::string local_dvs_port_name = "/dvsReadLocal:i";
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

  // We create the ports that will send the images to YARP
  // Left eye
  yarp::os::Port image_port_left_out;
  std::string image_port_name_left_out = "/BlobTracker/imagePortLeft:o";
  image_port_left_out.open(image_port_name_left_out.c_str());
  // Right eye
  yarp::os::Port image_port_right_out;
  std::string image_port_name_right_out = "/BlobTracker/imagePortRight:o";
  image_port_right_out.open(image_port_name_right_out.c_str());

  // We create the images and give them their size
  // Output
  // Left
  yarp::sig::ImageOf<yarp::sig::PixelRgb> image_left_out;
  image_left_out.resize(128,128);	
  image_left_out.zero();
  // Right
  yarp::sig::ImageOf<yarp::sig::PixelRgb> image_right_out;
  image_right_out.resize(128,128);	
  image_right_out.zero();

  // Define cluster init position.
  // Num clusters	= 5 (const init);
  const int numClusters = 5;
  // Cluster events = 0 (variable init);
  yarp::sig::Vector numEventsPerCluster;
  numEventsPerCluster.resize(5);
  yarp::sig::Vector currentEventNumbers, previousEventNumbers;
  currentEventNumbers.resize(128,128);

  // Variable controlling the loop
  bool run = true;

  // Variables that will hold the parameters of the ellipse
  // Left
  std::vector<double> a_l, b_l, alpha_l, cen_x_l, cen_y_l;
  // Right
  std::vector<double> a_r, b_r, alpha_r, cen_x_r, cen_y_r;
  int numIters = 0;
  int confidenceVal = 0;
  bool moveEyes = false;
  double cen_x_prev, cen_y_prev; 

  while(run && numIters < 10000000){
	   

   evBottle = dvs_port.read();
    numIters++;
    yarp::os::Bottle *bottle = (*evBottle).get_packet();

    emorph::ecodec::eEventQueue q;
    emorph::ecodec::eEvent::decode(*bottle, q);

    int sizeOfQ = q.size();
    fprintf(output_file, "%d \n", sizeOfQ); 
        //printf("Received %i events \n", sizeOfQ);

    // If the number of events is lower than a predefined threshold, then we assume we are getting just noise, and we do nothing
    if(sizeOfQ > min_nb_ev){
      int ev_x, ev_y, pol, channel;
      long long ev_t;
      bool address_ev_found = false;
      bool ts_found = false;
      
      // We go through all the events
      for (int ii=0; ii < sizeOfQ; ii++){
	// We need the adress event first
	if (q[ii]->getType() == "AE"){
	  // We decode the event
	  emorph::ecodec::AddressEvent *ev = static_cast<emorph::ecodec::AddressEvent*>(q[ii]); 
	  if (ev->isValid()){
	    ev_x = 127-ev->getX();
	    ev_y = ev->getY();
	    pol = ev->getPolarity();
	    channel = ev->getChannel();
	    address_ev_found = true;
	  }
	}
	// Once the addres event has been found, we look for the timestamp
	if (q[ii]->getType() == "TS" && address_ev_found){
	  // We decode the event
	  emorph::ecodec::TimeStamp *ts = static_cast<emorph::ecodec::TimeStamp*>(q[ii]); 
	  if (ts->isValid()){
	    ev_t = ts->getStamp();
	    ts_found = true;
	  }
	}

	// If we have both the adress and the timestamp, we update the trackers
	if(address_ev_found && ts_found){
	  if (channel == 0) {
	    tracker_pool_left.update(ev_x, ev_y, ev_t);
	    image_left_out.pixel(ev_y, ev_x).g = pol==0?127:255;
	  }
	  else {
	    tracker_pool_right.update(ev_x, ev_y, ev_t);
            image_right_out.pixel(ev_y, ev_x).g = pol==0?127:255;
	  }
	  address_ev_found = false;
	  ts_found = false;
	}
      }

      // We update the images of the ellipses
      tracker_pool_left.display(image_left_out);
      tracker_pool_right.display(image_right_out);
      if(moveEyes == true)
	{
	  //		cubMotor->moveEyes(cen_x_l, cen_y_l);
	  //		Time::delay(10);
	}
    }
    image_port_left_out.write(image_left_out);
    image_port_right_out.write(image_right_out);
    image_left_out.zero();
    image_right_out.zero();

  }
  fclose(output_file);
}
