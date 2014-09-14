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

    for (int i=0; i < 128; i++)
    {
            for (int j=0; j < 128; j++)    
            {
                PixelRgb& pixel = imageToWrite.pixel(i, j);
                pixel.r = 0.5;
                pixel.g = 0.5;
                pixel.b = 0.5;
            }
    }

    imagePort.open("/imageRF");

}

yarpDefault::~yarpDefault()
{
    inputPort.close();
    imagePort.close();
}
