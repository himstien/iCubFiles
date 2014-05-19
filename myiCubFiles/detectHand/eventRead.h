#include <iostream>
#include <yarp/os/all.h>
#include "eventBottle.h"
//#include </home/Desktop/Himanshu/eventBottleHandler.h>
//#include <math>
using namespace std;
using namespace yarp::os;

class eventReader : public BufferedPort <eventBottle>{

public:

//eventReader();
//~eventReader();

virtual void onRead(eventBottle &b){
this->createFile();

Bottle bot;
bot = * b.get_packet();
cout << "events read... " << b.get_sizeOfPacket() << endl;
//cout << bot.size() << endl;
totalPackets += bot.size();
fileOut << bot.toString() << endl;

}

void createFile(){
    if(!fileOut.is_open())
    {
        cout << "Creating a new file to write... " << endl;
        fileOut.open("/home/akolkar/Desktop/tempWriteFile.txt");
    }

}

unsigned int get_totalPacketsRead(){
return totalPackets;
}

private:

unsigned int totalPackets;
ofstream fileOut;

};
