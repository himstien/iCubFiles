/*
 * Copyright (C) 2011 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Chiara Bartolozzi
 * email:  chiara.bartolozzi@iit.it
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

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

#include <time.h>
#include <string>
#include <fstream>

using namespace yarp::os;

using namespace std;

int main(int argc, char * argv[])
{

    int h = 1;
    
    Bottle  bot;
    cout << "Size of bottle : " << sizeof(bot) << " as compared to size of an integer: " << sizeof(int) << endl;

    bot.addInt(1);

    cout << "Size of bottle after Int [sizeof(bot) : "<< sizeof(bot) << endl;
    
    cout << "Size of bottle itself [bot.size]: "<< bot.size() << endl;

    bot.addDouble(1);

    cout << "Size of bottle after second Int [sizeof(bot) : "<< sizeof(bot) << endl;

    cout << "Size of bottle after second int itself [bot.size]: "<< bot.size() << endl;

    return 0;
}
//empty line to make gcc happy
