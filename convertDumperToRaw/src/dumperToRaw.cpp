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
#include "math.h"

using namespace std;
using namespace yarp::os;
using namespace yarp::sig;
using namespace emorph::ecodec;

DumperToRaw::DumperToRaw()
{
        verbose = false;
        eventsRead = -1;
        error1 = 0;
        valid = false;
        wrap = true;
        wrapCount = 0;
        wrapAdd = 0;

        outFile = "data.log";
        outFileFid.open(outFile.c_str());            
                
               
}

void DumperToRaw::close()
{
        cout << "Closing ports and files." << endl;        
        verbose = false;
        eventsRead = -1;
        error1 = 0;
        valid = false;
        wrap = true;
        wrapCount = 0;
        wrapAdd = 0;


        outFileFid.close();

        outputPort.interrupt();        
        outputPort.close();
        return;      
}        

void DumperToRaw::setInFile(string inputFile)
{
    inFile = inputFile;
}

bool DumperToRaw::setOutputPort(string outPort)
{
    cout << "[dumper2raw]: opening port for writing data." << endl;   
    if(outputPort.open(outPort.c_str()))
        return true;
    
    return false;
}

void DumperToRaw::setVerbose(bool value)
{
    verbose = value;
    cout << "[dumper2raw]: Setting verbose to " << value << endl;
}

int DumperToRaw::char2dec(char input)
{
    unsigned int outDecimal;
    outDecimal = 0;
    switch (input)
    {
        case '0':
            outDecimal = 0;
            return outDecimal;

        case '1':
            outDecimal = 1;
            return outDecimal;

        case '2':
            outDecimal = 2;
            return outDecimal;

        case '3':
            outDecimal = 3;
            return outDecimal;

        case '4':
            outDecimal = 4;
            return outDecimal;

        case '5':
            outDecimal = 5;
            return outDecimal;

        case '6':
            outDecimal = 6;
            return outDecimal;

        case '7':
            outDecimal = 7;
            return outDecimal;

        case '8':
            outDecimal = 8;
            return outDecimal;

        case '9':
            outDecimal = 9;
            return outDecimal;

        case 'a':
            outDecimal = 10;
            return outDecimal;

        case 'b':
            outDecimal = 11;
            return outDecimal;

        case 'c':
            outDecimal = 12;
            return outDecimal;

        case 'd':
            outDecimal = 13;
            return outDecimal;

        case 'e':
            outDecimal = 14;
            return outDecimal;

        case 'f':
            outDecimal = 15;
            return outDecimal;

        case 'A':
            outDecimal = 10;
            return outDecimal;

        case 'B':
            outDecimal = 11;
            return outDecimal;

        case 'C':
            outDecimal = 12;
            return outDecimal;

        case 'D':
            outDecimal = 13;
            return outDecimal;

        case 'E':
            outDecimal = 14;
            return outDecimal;

        case 'F':
            outDecimal = 15;
            return outDecimal;

        default:
            outDecimal = -1;
            return outDecimal;
    }
}

void DumperToRaw::convertToDumper()
{   

    inFileFid.open(inFile.c_str());
    cout << "[dumper2raw]: Opening file. " <<  inFileFid.is_open() << endl;        
    inFileFid.seekg(0, inFileFid.beg);    
    eventsRead = 0;
    
    while(!inFileFid.eof()) // && eventsRead < 50000
    {        

        outputBottle.clear();
        outputBottle = outputPort.prepare();

        char timeByte;        
        inFileFid >> timeByte;
        if (char2dec(timeByte) == 8)
        {
//            cout << "Valid event. Starting conversion." << endl;
            
            inFileFid >> timeByte;                
            if(char2dec(timeByte)== 8)
            {   
                wrapCount++;    
                cout << "!!! Wrap event number " << wrapCount << " occurred !!!" << endl;
                cout << endl;

                for(int skp = 0; skp < 6; skp++)
                {
                    inFileFid >>timeByte;
                } // End of skip time for-loop
                valid = false;
                wrapAdd += pow(2, 24);                   
                
                //break;
            }
            else
            {
                valid = true;
            }

            // compute timeStamp
            if(valid)
            {
                unsigned int time = wrapAdd;
                unsigned int yPos = 0;
                unsigned int xPos = 0;
                unsigned int pol = 0;
                unsigned int channel = 0;

                for (int place = 5; place >=0; place--)
                {
                    inFileFid >> timeByte;
//                    cout << char2dec(timeByte) << " ";
                    time += char2dec(timeByte)*pow(16, place);                
                } // End of timestamp For-loop
                
                // Discard first 4 bytes of address data. reserved for other use
                for (int i = 0; i < 4; i++)
                {
                    char wordByte;
                    inFileFid >> wordByte;
                } // end of discard For-loop

                // Get address, polarity and channel
                //for (int i = 0; i < 4; i++)
                {
                    char wordByte1, wordByte2, wordByte3, wordByte4;

                    inFileFid >> wordByte1;
                    inFileFid >> wordByte2;
                    inFileFid >> wordByte3;
                    inFileFid >> wordByte4;

//                    cout << char2dec(wordByte1)<< " " << char2dec(wordByte2)<< " " << char2dec(wordByte3)<< " " << char2dec(wordByte4)<< " ";

                    yPos = ((char2dec(wordByte3)<<4) | char2dec(wordByte4) ) >>1;                        
                    channel = char2dec(wordByte4) & 8;
                    xPos = (char2dec(wordByte1) & 7) << 4 | char2dec(wordByte2);
                    pol = char2dec(wordByte1) & 1;
            
                    outputBottle.addInt(xPos);
                    outputBottle.addInt(yPos);
                    outputBottle.addInt(pol);
                    outputBottle.addInt(channel);                   
                    outputBottle.addInt(time);

                    outputPort.write();
//                cout << " " << time << " " << wrapAdd << " " << xPos << " " << yPos << " " << pol << " " << channel ;
                } // end of address For-loop
//                cout << endl;
                eventsRead++;
            }
        }
        else
        {
            if(inFileFid.eof())
            {
                break;
            }

            if(error1 < 1)
            {
                cout << "Event invalid. Moving to next event. Will stop if another error occurs." << endl;                
                error1++;
            }
            else
            {   
                cout << "Multiple errors while reading the file. Quitting. Total events read: " << eventsRead << endl;
                return;
            }
        }
    }// end of file
    cout << "File reading completed. Total events read = " << eventsRead << endl;
    return;
}


//empty line to make gcc happy
