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


#include "dumperToRaw.h"

using namespace yarp::os;

int main(int /*argc*/, char ** /*argv[]*/)
{

    DumperToRaw dumpToRaw;
    dumpToRaw.setVerbose(true);    

 //   std::cout << dumpToRaw.setOutputPort("/convertRawPort:o") << std::endl;
    
    int i=0;
    while(i < 2)
    {
        std::cout << i+1 << std::endl;
        dumpToRaw.setInFile("/home/icub/Documents/eventDumps/raw_Aex_Data/ball1.txt");
        dumpToRaw.setOutputPort("/convertRawPort:o");
        dumpToRaw.convertToDumper();
        dumpToRaw.close();
        i++;
    }

    return 0;
}
//empty line to make gcc happy
