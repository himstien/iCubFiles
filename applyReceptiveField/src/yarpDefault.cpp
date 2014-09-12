#include "yarpDefault.h"

using namespace emorph::ecodec;
using namespace yarp::os;
using namespace yarp::sig;


yarpDefault::yarpDefault()
{
    Network yarp;
  
    inputPort.open("/inputEvents");   
    yarp.connect("/eventBottleConverter/etb:o", "/inputEvents");

    imageToWrite.resize(128, 128);

    imagePort.open("/imageRF");

}

yarpDefault::~yarpDefault()
{
    inputPort.close();
    imagePort.close();
}
