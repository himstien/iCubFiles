//##############################################################################################################################################################################################################//
//Aquila - An Open-Source GPU-Accelerated Toolkit for Cognitive and Neuro-Robotics Research																														//
//																																																				//
//Copyright (c) <2012>, Anthony Morse                                                                                                                                                                                //
//All rights reserved.																																															//
//																																																				//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:																//
//																																																				//
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.																				//
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.	//
//																																																				//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR	//
//A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT	//
//LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR	//
//TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.																//
//                                                                                                                                                                                                              //
//The views and conclusions contained in the software and documentation are those of the authors and should not be interpreted                                                                                  //
//as representing official policies,either expressed or implied, of the FreeBSD Project.                                                                                                                        //
//##############################################################################################################################################################################################################//

#ifndef AQUILA_LITE_CUBCART_H
#define AQUILA_LITE_CUBCART_H

#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/sig/Vector.h>
#include <yarp/math/Math.h>

#include <yarp/dev/Drivers.h>
#include <yarp/dev/CartesianControl.h>
#include <yarp/dev/PolyDriver.h>

#include <gsl/gsl_math.h>

#include <stdio.h>
#include <iostream>

YARP_DECLARE_DEVICES(icubmod)
using namespace std;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::math;

namespace aquilacubcart
{
#define CTRL_THREAD_PER     0.01    // [s]
#define PRINT_STATUS_PER    1.0     // [s]
#define MAX_TORSO_PITCH     30.0    // [deg]
#define T		    2.4
#define XD		   -0.1

class CubCartThread: public RateThread,
                     public CartesianEvent
{
protected:
    PolyDriver         Lclient;
    PolyDriver         Rclient;
    ICartesianControl *icartL;
    ICartesianControl *icartR;
    Port inputPort;

    Vector Lxd, Rxd, x0;
    Vector Lod, Rod, o0;

    int startup_context_left_id, startup_context_right_id;

    double t;
    double t0;
    double t1;

    virtual void cartesianEventCallback();

public:

    //CubCartThread(const double period) : RateThread(int(period*1000.0));
    CubCartThread(const double period);
    virtual bool threadInit();
    virtual void afterStart(bool s);
    virtual void run();
    virtual void threadRelease();
    void getTarget();
    void generateTarget();
    double norm(const Vector &v);
    void limitTorsoPitch();
    void printStatus();

};

class CubCart: public RFModule
{
protected:
    CubCartThread *thr;
public:
    virtual bool configure(ResourceFinder &rf);
    virtual bool close();

    virtual double getPeriod();
    virtual bool   updateModule();
};


}
#endif//AQUILA_LITE_CUBCART_H
