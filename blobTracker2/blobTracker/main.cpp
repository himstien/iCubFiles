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

#include "./iCubMotor/include/iCubMotor.h"

using namespace aquilacubmotor;

int main(int numArgs, char** args)
{
  // Initial parameters of the Blob Tracker
  double x0 = 128/2;
  double y0 = 128/2;
  double sig_x = 5;
  double sig_y = 5;
  double sig_xy = 0;
  double alpha_pos = 0.01;
  double alpha_shape = 0.02;
  double max_dist = 30;
  double k = 2;

  std::string filename = "output.txt";
  
  ICubMotor *cubMotor = new ICubMotor(false, false);
	cubMotor->start();
	
  if(numArgs > 3){
    filename = args[3];
  }
  if(numArgs > 2){
    alpha_shape = atof(args[2]);
  }
  if(numArgs > 1){
    alpha_pos = atof(args[1]);
  }

	
  // File for outputing the data
  FILE *output_file;
  output_file = fopen (filename.c_str(), "w");
  if (output_file == NULL) 
    perror ("Error opening file");
  
  // We create the trackers
  TrackerPool tracker_pool_left(sig_x, sig_y, sig_xy, alpha_pos, alpha_shape, k, max_dist, 1, 1, true);
  TrackerPool tracker_pool_right(sig_x, sig_y, sig_xy, alpha_pos, alpha_shape, k, max_dist, 1, 1, true);

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
  yarp::os::Port image_port_left;
  std::string image_port_name_left = "/BlobTracker/imagePortLeft:o";
  image_port_left.open(image_port_name_left.c_str());
  // Right eye
  yarp::os::Port image_port_right;
  std::string image_port_name_right = "/BlobTracker/imagePortRight:o";
  image_port_right.open(image_port_name_right.c_str());

  // We should try to connect them as well, so we do not have to do it manually every time

  // We create the images and give them their size
  //Left
  yarp::sig::ImageOf<yarp::sig::PixelRgb> image_left;
  image_left.resize(128,128);	
  image_left.zero();
  // Right
  yarp::sig::ImageOf<yarp::sig::PixelRgb> image_right;
  image_right.resize(128,128);	
  image_right.zero();


  // I do not know what this is
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
    // With each event shift cluster position to new value.
    	
    evBottle = dvs_port.read();
	numIters++;
    yarp::os::Bottle *bottle = (*evBottle).get_packet();

    emorph::ecodec::eEventQueue q;
    emorph::ecodec::eEvent::decode(*bottle, q);

    int sizeOfQ = q.size();
	fprintf(output_file, "%d \n", sizeOfQ); 
    //    printf("Received %i events \n", sizeOfQ);

    // If the number of events is lower than a predefined threshold, then we assume we are getting just noise, and we do nothing
    if(sizeOfQ > min_nb_ev)
    {
      int ev_x, ev_y, pol, channel;

      // We go through all the events
      for (int ii=0; ii < sizeOfQ; ii++){
	if (q[ii]->getType() == "AE"){

	  // We decode the event
	  emorph::ecodec::AddressEvent *ev = static_cast<emorph::ecodec::AddressEvent*>(q[ii]); 
	  if (ev->isValid()){
	    ev_x = 127-ev->getX();
	    ev_y = ev->getY();

	    pol = ev->getPolarity();
	    channel = ev->getChannel();
		
	    if (channel == 0) {
	      tracker_pool_left.update(ev_x, ev_y);
	//	printf("updating events for left eye\n");
	    }
	    else {
	      tracker_pool_right.update(ev_x, ev_y);
		//printf("updating events for right eye\n");
	    }
	  }
	}	
      }

      // We update the images of the ellipses
     tracker_pool_left.display(image_left);
     BlobTracker b;
     double cen_x_l= 1.0, cen_y_l=1.0;	
     tracker_pool_left.get_tracker(b, 0);
     b.get_center(cen_x_l, cen_y_l);


     double cen_x_r= 100.0, cen_y_r=100.0;	
     tracker_pool_right.get_tracker(b, 0);
     b.get_center(cen_x_r, cen_y_r);

//     printf("cenx: %f ceny: %f\n", cenx, ceny);	
     tracker_pool_right.display(image_right);
	if(moveEyes == true)
	{
		cubMotor->moveEyes(cen_x_l, cen_y_l);
		Time::delay(10);
	}
    }
    image_port_left.write(image_left);
    image_port_right.write(image_right);
    image_left.zero();
    image_right.zero();

  }
  fclose(output_file);
}
