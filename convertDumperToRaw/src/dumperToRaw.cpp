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

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace emorph::ecodec;

DumperToRaw::DumperToRaw()
{
        verbose = false;
               
}

void DumperToRaw::setInFile(string inputFile)
{
    inFile = inputFile;
}

void DumperToRaw::setVerbose(bool value)
{
    verbose = value;
    cout << "[dumper to raw]: Set verbose to " << value << endl;
}

void DumperToRaw::convertToRaw()
{   

    inFileFid.open(inFile.c_str());
    cout << inFileFid.is_open() << endl;
    
    string line;
    
    int lineCount = 0;



    bool ok = false;

    while (!inFileFid.eof())
    {
        
        // get one bottle worth data from file
        getline(inFileFid, line);

        int wordCount = 0;
        // parse line into x y p t    
        if (verbose)
        {
            char startCheck = line[wordCount++];
            if (startCheck == '0')
            {
                cout << "Line Ok! " << lineCount++ << endl;            
                ok = true;                
            }
        }    
            
        char space = line[wordCount++];
            
        string timeOfBottle;

        if (ok)
        {
             while (line[wordCount] != ' ')
             {
                timeOfBottle+=line[wordCount];
                wordCount++;
             }
             ok = false;                
        }

        cout << line.find('X') << endl;

//        cout << timeOfBottle << endl;

    } 

/*
    for (int b=0; b<size;b++)
    {
        Bottle *cur = main->get(b).asList(); //get each sublist  
        //fprintf(stdout, "Bottle: %s\n", cur->toString().c_str());
        
        //create timestamp       
        TimeStamp ts;
        ts.setStamp(cur->find("time").asDouble());

        string type = cur->find("type").asString().c_str(); //for each sublist get type  
        //create Bottle to append Timestamp and Event
        Bottle tmp;
        //encode TimeStamp 
        tmp = ts.encode();
        if (type=="AE")
        {
            //create addressEvent for specific type
            AddressEvent evt; 
            //start filling addressEvent with data from sublists
            evt.setX(cur->find("posX").asInt());
            evt.setY(cur->find("posY").asInt());
            evt.setPolarity(cur->find("polarity").asInt());
            evt.setChannel(cur->find("channel").asInt());
            //append timeStamp and Event into single bottle
            tmp.append(evt.encode());
        }

        if (type=="CLE-G")
        {
            //create addressEvent for specific type
            ClusterEventGauss evt; 
            //start filling addressEvent with data from sublists
            evt.setChannel(cur->find("channel").asInt());
            evt.setXCog(cur->find("xCog").asInt());
            evt.setYCog(cur->find("yCog").asInt());
            evt.setNumAE(cur->find("numAE").asInt());
            evt.setXSigma2(cur->find("xSigma2").asInt());
            evt.setYSigma2(cur->find("ySigma2").asInt());
            evt.setXYSigma(cur->find("xySigma").asInt());
            
            //append timeStamp and Event into single bottle
            tmp.append(evt.encode());
        }


        //append the bottle tmp with TimeStamp and Event of a single spike to a bottle that contains the events of the whole packet 
        event.append(tmp);
    }
    //create and fill in dataTmp (eventBottle) with data from event (Bottle) 
    //fprintf(stdout, "\n\n\nEvent: %s\n", event.toString().c_str());
    eventBottle dataTmp(&event);
    //copy dataTmp to eventBottle out
    out = dataTmp;
    //send it all out
    outPort.write();
    mutex.post();
*/


}

//empty line to make gcc happy
