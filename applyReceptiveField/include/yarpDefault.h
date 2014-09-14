#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/Time.h>
//#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>

#include <iCub/emorph/eventBottle.h>
#include <iCub/emorph/eventCodec.h>

class yarpDefault
{
    public:
        yarpDefault();
        ~yarpDefault();
  
      yarp::os::BufferedPort<yarp::os::Bottle> inputPort;    
        yarp::sig::ImageOf<yarp::sig::PixelRgb> imageToWrite;
        
        yarp::os::Port imagePort;    
        
//        yarp::os::BufferedPort<yarp::os::Bottle> bufferPort;

};
