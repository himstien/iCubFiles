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

using namespace std;
using namespace yarp::sig;
using namespace yarp::os;
using namespace yarp::dev;
//using namespace emorph::ecodec;

int main(int numArgs, char** args)
{
  // Initial parameters of the Blob Tracker
  double x0 = 128/2;
  double y0 = 128/2;
  double sig_x = 5;
  double sig_y = 5;
  double sig_xy = 0;
  double alpha_pos = 0.001;
  double alpha_shape = 0.000;

//  if(numArgs > 1)
//  {
//	alpha_pos = (double) *args[0];
//	alpha_shape = (double) *args[1];
//  } 
//  else if (numArgs > 0)
//  {
//	alpha_pos = (double) *args[0];
//   }
  // Constant for the representation of the ellipses
  double K = 2.2;

  BlobTracker blob_tracker(x0, y0, sig_x, sig_y, sig_xy, alpha_pos, alpha_shape);

  // Threshold for updating the position
  double min_p = 0.0;

  int min_nb_ev = 1;

  // Vector containing the degrees (in radians) for plotting the ellipse
  std::vector<double> theta;

  for(int ii=0; ii<360; ii++){
    theta.push_back(ii*M_PI/180);
  }
   

  Network yarp;
  string dvsPort = "/aexGrabber/eventBottle:o";

  //ImageOf<PixelRGB> clusterImage;


  BufferedPort<eventBottle> readDVS;
  (readDVS).open("/dvsReadLocal:i");
  printf("Created port /dvsReadLocal:i to get data from DVS!!\n\n");

  bool connectionOk = yarp.connect(dvsPort.c_str(), "/dvsReadLocal:i");

    printf("Waiting for aexGrabber port to go alive!!!\n");	
  while (!connectionOk){

    connectionOk = yarp.connect(dvsPort.c_str(), "/dvsReadLocal:i");

  }
	printf("Connected to iCub's DVS port\n");

  Port imagePort;
  imagePort.open("/David/imagePort:o");
  yarp::sig::ImageOf<yarp::sig::PixelRgb> image;
  image.resize(128,128);	
  image.zero();

  // Define cluster init position.
  // Num clusters	= 5 (const init);
  const int numClusters = 5;
  // Cluster events = 0 (variable init);
  Vector numEventsPerCluster;
  numEventsPerCluster.resize(5);

  Vector currentEventNumbers, previousEventNumbers;
  currentEventNumbers.resize(128,128);

  eventBottle *evBottle;

  bool run = true;

  double a, b, alpha, cen_x, cen_y;

  printf("About to enter the while loop\n");
  while(run){

//    printf("Read\n");
    // With each event shift cluster position to new value.
    evBottle = readDVS.read();
//    printf("Done\n");
    cout << (*evBottle).get_sizeOfPacket() << endl;

    Bottle *bottle = (*evBottle).get_packet();

    emorph::ecodec::eEventQueue q;
    emorph::ecodec::eEvent::decode(*bottle, q);

    int sizeOfQ = q.size();
//    printf("Received %i events \n", sizeOfQ);

    // If the number of events is lower than a predefined threshold, then we assume we are getting just noise, and we do nothing
    if(sizeOfQ > min_nb_ev){
      int ev_x, ev_y, pol, channel;

      // We go through all the events
      for (int ii=0; ii < sizeOfQ; ii++){
	if (q[ii]->getType() == "AE"){
	  	
	  emorph::ecodec::AddressEvent *ev = static_cast<emorph::ecodec::AddressEvent*>(q[ii]); 
	  if (ev->isValid())
	  {
		ev_x = ev->getY();
          	ev_y = 127-ev->getX();

		pol = ev->getPolarity();
		channel = ev->getChannel();
		if (channel == 0)
		{
	  		double p = blob_tracker.compute_p(ev_x, ev_y);
			printf("Probabilities %f\n", p);
	  		if(p>min_p && blob_tracker.dist2Event(ev_x, ev_y) < 30){
	    			blob_tracker.update_position(ev_x, ev_y);
	  		}
                        blob_tracker.get_ellipse_parameters(cen_x, cen_y, a, b, alpha);
			printf ("X = %d, Y=%d, Cen_X= %f, Cen_Y= %f \n", ev_x, ev_y, cen_x, cen_y);
				image.pixel(ev_x, ev_y).r = 255; 
		}
	  }
	}	
      }

      // We update the image of the ellipse



      blob_tracker.get_ellipse_parameters(cen_x, cen_y, a, b, alpha);
      a*=K;
      b*=K;
	
      double c_a = cos(alpha);
      double s_a = sin(alpha);

	
      for(int ii=0; ii<theta.size(); ii++){
	double x0 = cen_x + a*cos(theta[ii]);
	double y0 = cen_y + b*sin(theta[ii]);

	int x = round(x0*c_a - y0*s_a);
	int y = round(x0*s_a + y0*c_a);
	if(x>0 && x<128 && y>0 && y<128)
	image.pixel(x, y).b = 255; 

      }
    }
    printf("Sending image \n");
    imagePort.write(image);
      image.zero();
  }
  
  //
  //eventPacket.();
  // Add event to this cluster
  // Main cluster = max event clusters

	
  // Get [x,y] for each eye

  // Do gaze control using these values.

  // Reset all clusters
 

}
