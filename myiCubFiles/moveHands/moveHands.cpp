// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>
#include <yarp/os/Network.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>

#include <string>

using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::os;

int main(int argc, char *argv[]) 
{
    Network yarp;

    Property params;
    params.fromCommand(argc, argv);

    if (!params.check("robot"))
    {
        fprintf(stderr, "Please specify the name of the robot\n");
        fprintf(stderr, "--robot name (e.g. icub)\n");
        return -1;
    }
    std::string robotName=params.find("robot").asString().c_str();
    std::string remotePorts="/";
    remotePorts+=robotName;
    remotePorts+="/left_arm";

    std::string localPorts="/test/client";

    Property options;
    options.put("device", "remote_controlboard");
    options.put("local", localPorts.c_str());   //local port names
    options.put("remote", remotePorts.c_str());         //where we connect to

    // create a device
    PolyDriver robotDevice(options);
    if (!robotDevice.isValid()) {
        printf("Device not available.  Here are the known devices:\n");
        printf("%s", Drivers::factory().toString().c_str());
        return 0;
    }

    IPositionControl *pos;
    IEncoders *encs;

    bool ok;
    ok = robotDevice.view(pos);
    ok = ok && robotDevice.view(encs);

    if (!ok) {
        printf("Problems acquiring interfaces\n");
        return 0;
    }

    int nj=0;
    pos->getAxes(&nj);
    Vector encoders;
    Vector command;
    Vector tmp;
    encoders.resize(nj);
    tmp.resize(nj);
    command.resize(nj);
    
    int i;
    for (i = 0; i < nj; i++) {
         tmp[i] = 50.0;
    }
    pos->setRefAccelerations(tmp.data());

    for (i = 0; i < nj; i++) {
        tmp[i] = 20.0;
        pos->setRefSpeed(i, tmp[i]);
    }
    
    //pos->setRefSpeeds(tmp.data()))
    
    //fisrst read all encoders
    //
    printf("waiting for encoders");
    while(!encs->getEncoders(encoders.data()))
    {
        Time::delay(0.1);
        printf(".");
    }
    printf("\n;");

    command=encoders;
    //now set the shoulder to some value
    command[0]=-65;
    command[1]=20;
    command[2]=8;
    command[3]=70;
    
    pos->positionMove(command.data());
    Time::delay(5);

    bool done=false;

    while(!done)
    {
        pos->checkMotionDone(&done);
        Time::delay(0.1);
    }

    int times=0;
    while(true)
    {
        times++;
        if (times%2)
        {
             
             command[1]=command[1]-40;
             command[2]=command[2]+40;
             command[3]=command[3]+40;
             command[4]=command[4]+40;
             command[5]=command[5]+40;   
             command[6]=command[6]+40;
             command[7]=command[7]+40;
             command[8]=command[8]+40;
             command[9]=command[9]+40;
             command[10]=command[10]+40;
             command[11]=command[11]+40;
             command[12]=command[12]+40;
             command[13]=command[13]+40;            
        }
        else
        {
             command[1]=command[1]+40;
             command[2]=command[2]-40;
             command[3]=command[3]-40;
             command[4]=command[4]-40;
             command[5]=command[5]-40;
             command[6]=command[6]-40;
             command[7]=command[7]-40;
             command[8]=command[8]-40;
             command[9]=command[9]-40;
             command[10]=command[10]-40;
             command[11]=command[11]-40;
             command[12]=command[12]-40;
             command[13]=command[13]-40;            

        }

        pos->positionMove(command.data());

        int count=50;
        while(count--)
            {
                Time::delay(0.2);
                bool ret=encs->getEncoders(encoders.data());
                
                if (!ret)
                {
                    fprintf(stderr, "Error receiving encoders, check connectivity with the robot\n");
                }
                else
                { 
                    printf("%.1lf %.1lf %.1lf %.1lf\n", encoders[0], encoders[1], encoders[2], encoders[4]);
                }
            }
    }

    robotDevice.close();
    
    return 0;
}
