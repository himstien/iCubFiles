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

#include <string>
#include "cartesian.h"
#include <yarp/os/Network.h>

namespace aquilacubcart
{


   void CubCartThread::cartesianEventCallback()
   {
        fprintf(stdout,"20%% of trajectory attained\n");
   }


   CubCartThread::CubCartThread(const double period) : RateThread(int(period*1000.0))
   {
        // we wanna raise an event each time the arm is at 20%
        // of the trajectory (or 70% far from the target)
        cartesianEventParameters.type="motion-ongoing";
        cartesianEventParameters.motionOngoingCheckPoint=0.2;
   }

   bool CubCartThread::threadInit()
    {
        inputPort.open("/cart");

        // open a client interface to connect to the cartesian server of the simulator
        // we suppose that:
        //
        // 1 - the iCub simulator is running
        //     (launch iCub_SIM)
        //
        // 2 - the cartesian server is running
        //     (launch simCartesianControl)
        //     
        // 3 - the cartesian solver for the left arm is running too
        //     (launch iKinCartesianSolver --context simCartesianControl/conf --part left_arm)
        //
        Property Loption("(device cartesiancontrollerclient)");
        Loption.put("remote","/icub/cartesianController/left_arm");
        Loption.put("local","/cartesian_client/left_arm");

        Property Roption("(device cartesiancontrollerclient)");
        Roption.put("remote","/icub/cartesianController/right_arm");
        Roption.put("local","/cartesian_client/right_arm");

        if (!Lclient.open(Loption) || !Rclient.open(Roption))
            return false;

        // open the view
        Lclient.view(icartL);
        Rclient.view(icartR);

        // latch the controller context in order to preserve
        // it after closing the module
        // the context contains the dofs status, the tracking mode,
        // the resting positions, the limits and so on.
        icartL->storeContext(&startup_context_left_id);
		icartR->storeContext(&startup_context_right_id);
		
        // set trajectory time
        icartL->setTrajTime(2.0);
        icartR->setTrajTime(2.0);

        // get the torso dofs
        Vector newDof, curDof;
        icartL->getDOF(curDof);
        newDof=curDof;

        // enable the torso yaw and pitch
        // disable the torso roll
        newDof[0]=1;    //forward back
        newDof[1]=0;    //side to side tilt!
        newDof[2]=1;    //turn

        // impose some restriction on the torso pitch
        limitTorsoPitch();

        // send the request for dofs reconfiguration
        icartL->setDOF(newDof,curDof);
        icartR->setDOF(newDof,curDof);

        // print out some info about the controller
        Bottle info;
        icartL->getInfo(info);
        fprintf(stdout,"info = %s\n",info.toString().c_str());
        icartR->getInfo(info);
        fprintf(stdout,"info = %s\n",info.toString().c_str());   

        // register the event, attaching the callback
        icartL->registerEvent(*this);
		icartR->registerEvent(*this);
		
        Lxd.resize(3);
        Rxd.resize(3);
        Lod.resize(4);
        Rod.resize(4);

        //some default "safe" position
        Lxd[0] = -0.3;
        Lxd[1] = -0.1;
        Lxd[2] = 0.1;
        Rxd[0] = -0.3;
        Rxd[1] = -0.1;
        Rxd[2] = 0.1;
        
        
        // we keep the orientation of the left arm constant:
        // we want the middle finger to point forward (end-effector x-axis)
        // with the palm turned down (end-effector y-axis points leftward);
        // to achieve that it is enough to rotate the root frame of pi around z-axis
        Lod[0]=0.0; Lod[1]=0.0; Lod[2]=1.0; Lod[3]=M_PI;    //plam down
        Rod[0]=0.0; Rod[1]=1.0; Rod[2]=0.0; Rod[3]=M_PI;    //palm down

        return true;
    }

    void CubCartThread::afterStart(bool s)
    {
        if (s)
            fprintf(stdout,"Thread started successfully\n");
        else
            fprintf(stdout,"Thread did not start\n");

        t=t0=t1=Time::now();
    }

    void CubCartThread::run()
    {
        t=Time::now();

        getTarget();
        //generateTarget();

        // go to the target :)
        // (in streaming)
        //icartL->goToPose(xd,od);
        // some verbosity
        printStatus();
    }

    void CubCartThread::threadRelease()
    {    
        // we require an immediate stop
        // before closing the client for safety reason
        icartL->stopControl();
		icartR->stopControl();
		
        // it's a good rule to restore the controller
        // context as it was before opening the module
        icartL->restoreContext(startup_context_left_id);
		icartR->restoreContext(startup_context_right_id);
        Lclient.close();
        Rclient.close();
    }


    void CubCartThread::getTarget()
    {   
        Bottle command;

        printf("current command: left %f %f %f, right %f %f %f\n", Lxd[0], Lxd[1], Lxd[2], Rxd[0], Rxd[1], Rxd[2]);

        if(inputPort.read(command))
        {
            if(command.get(0).asString()=="left")
            {
                icartR->stopControl();  //stop the right arm
                printf("recieved command: left %f %f %f\n", command.get(1).asDouble(), command.get(2).asDouble(), command.get(3).asDouble());

                Lxd[0] = command.get(1).asDouble() - 0.065;    //left arm negative in front
                Lxd[1] = command.get(2).asDouble() - 0.065;    //left arm negative on correct side of body (x)
                Lxd[2] = command.get(3).asDouble();    //positive from waist up

				// sanity check the position before moving there
                if(Lxd[0] < -0.5) Lxd[0] = -0.5;
				if(Lxd[0] > -0.1) Lxd[0] = -0.1;
				if(Lxd[1] < -0.4) Lxd[1] = -0.4;
                if(Lxd[1] > 0.1) Lxd[1] = 0.1;
				if(Lxd[2] < -0.2) Lxd[2] = -0.2;
				if(Lxd[2] > 0.4) Lxd[2] = 0.4;

                icartL->goToPose(Lxd,Lod);
                Time::delay(3);              
                icartL->stopControl();  //stop the left arm
            }
            else if(command.get(0).asString()=="right")
            {
                icartL->stopControl();  //stop the left arm
                printf("recieved command: right %f %f %f\n", command.get(1).asDouble(), command.get(2).asDouble(), command.get(3).asDouble());

                Rxd[0] = command.get(1).asDouble() - 0.04;    //right arm negative in front
                Rxd[1] = command.get(2).asDouble() + 0.05;    //right arm positive on correct side of body
                Rxd[2] = command.get(3).asDouble();    //positive from waist up

				// sanity check the position before moving there
                if(Rxd[0] < -0.5) Rxd[0] = -0.5;
				if(Rxd[0] > -0.1) Rxd[0] = -0.1;
				if(Rxd[1] > 0.4) Rxd[1] = 0.4;
				if(Rxd[1] < 0.0) Rxd[1] = 0.0;
				if(Rxd[2] < -0.2) Rxd[2] = -0.2;
				if(Rxd[2] > 0.4) Rxd[2] = 0.4;

                icartR->goToPose(Rxd,Rod);
                Time::delay(3);
                icartR->stopControl();  //stop the right arm
            }
        }
    }


    void CubCartThread::generateTarget()
    {   
        // translational target part: a circular trajectory
        // in the yz plane centered in [-0.3,-0.1,0.1] with radius=0.1 m
        // and frequency 0.1 Hz
        
       // xd[0]=-0.3;
       // xd[1]=-0.1+0.1*cos(2.0*M_PI*0.1*(t-t0));
       // xd[2]=+0.1+0.1*sin(2.0*M_PI*0.1*(t-t0));
                 
        // we keep the orientation of the left arm constant:
        // we want the middle finger to point forward (end-effector x-axis)
        // with the palm turned down (end-effector y-axis points leftward);
        // to achieve that it is enough to rotate the root frame of pi around z-axis
       // od[0]=0.0; od[1]=0.0; od[2]=1.0; od[3]=M_PI;
    }

    double CubCartThread::norm(const Vector &v)
    {
        return sqrt(dot(v,v));
    }

    void CubCartThread::limitTorsoPitch()
    {
        int axis=0; // pitch joint
        double min, max;

        // sometimes it may be helpful to reduce
        // the range of variability of the joints;
        // for example here we don't want the torso
        // to lean out more than 30 degrees forward

        // we keep the lower limit
        icartL->getLimits(axis,&min,&max);
        icartL->setLimits(axis,min,MAX_TORSO_PITCH);
    }

    void CubCartThread::printStatus()
    {        
        if (t-t1>=PRINT_STATUS_PER)
        {
            Vector x,o,xdhat,odhat,qdhat;

            // we get the current arm pose in the
            // operational space
            icartL->getPose(x,o);

            // we get the final destination of the arm
            // as found by the solver: it differs a bit
            // from the desired pose according to the tolerances
            icartL->getDesired(xdhat,odhat,qdhat);

            double e_x=norm(xdhat-x);
            double e_o=norm(odhat-o);

            fprintf(stdout,"+++++++++\n");
            fprintf(stdout,"xd          [m] = %s\n",Lxd.toString().c_str());
            fprintf(stdout,"xdhat       [m] = %s\n",xdhat.toString().c_str());
            fprintf(stdout,"x           [m] = %s\n",x.toString().c_str());
            fprintf(stdout,"od        [rad] = %s\n",Lod.toString().c_str());
            fprintf(stdout,"odhat     [rad] = %s\n",odhat.toString().c_str());
            fprintf(stdout,"o         [rad] = %s\n",o.toString().c_str());
            fprintf(stdout,"norm(e_x)   [m] = %g\n",e_x);
            fprintf(stdout,"norm(e_o) [rad] = %g\n",e_o);
            fprintf(stdout,"---------\n\n");

            fprintf(stdout,"xd          [m] = %s\n",Rxd.toString().c_str());
            fprintf(stdout,"xdhat       [m] = %s\n",xdhat.toString().c_str());
            fprintf(stdout,"x           [m] = %s\n",x.toString().c_str());
            fprintf(stdout,"od        [rad] = %s\n",Rod.toString().c_str());
            fprintf(stdout,"odhat     [rad] = %s\n",odhat.toString().c_str());
            fprintf(stdout,"o         [rad] = %s\n",o.toString().c_str());
            fprintf(stdout,"norm(e_x)   [m] = %g\n",e_x);
            fprintf(stdout,"norm(e_o) [rad] = %g\n",e_o);
            fprintf(stdout,"---------\n\n");

            t1=t;
        }
    }

    bool CubCart::configure(ResourceFinder &rf)
    {
        Time::turboBoost();

        thr=new CubCartThread(CTRL_THREAD_PER);
        if (!thr->start())
        {
            delete thr;
            return false;
        }

        return true;
    }

    bool CubCart::close()
    {
        thr->stop();
        delete thr;

        return true;
    }

    double CubCart::getPeriod()
    { 
       return 1.0;
    }
    bool   CubCart::updateModule() 
    { 
       return true; 
    }


}
