
/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Himanshu Akolkar
 * email:  himanshu.akolkar@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

//#ifndef __ICUB_DUMPERTORAW_MOD_H__
//#define __ICUB_DUMPERTORAW_MOD_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/RateThread.h>
#include <yarp/os/Time.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Stamp.h>
#include <yarp/sig/Vector.h>
#include <yarp/sig/Image.h>

#include <yarp/os/RpcClient.h>

#include <iCub/emorph/eventBottle.h>
#include <iCub/emorph/eventCodec.h>

#include <time.h>
#include <string>
#include <fstream>


class DumperToRaw
{
    private:
        std::ifstream inFileFid;
        std::string inFile;
        bool verbose;
    
    public:
        DumperToRaw();
        void setInFile(std::string); 
        void convertToRaw();
        void setVerbose(bool);
    
};