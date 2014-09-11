// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006, 2007 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


/* 
Modified by Matt Tata (M.S.T. April 2014) to write audio to a memory mapped file in "quasi"
real time

The plan is to interact as little as possible with Paul's code so I don't break anything!
*/

#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <yarp/os/all.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/AudioGrabberInterfaces.h>
#include <yarp/sig/SoundFile.h>

//include the header for memory mapping (M.S.T.)
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>


//some parameters for mapping the audio data file (M.S.T.)
#define kFrameSizeToWrite_bytes 48000*4
#define kNumChannels 2
#define kNumSamples 48000
#define kSampleRate 48000 //this needs to be coordinated with the portaudio yarpdev!!
#define kBytesPerSample 2
#define kNumBytes kNumSamples*kNumChannels*kBytesPerSample
#define kFrameSizeToWrite_samples kFrameSizeToWrite_bytes/kBytesPerSample/kNumChannels

using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::sig::file;
using namespace yarp::dev;

int padding = 0;


class Echo : public TypedReaderCallback<Sound> {
private:
    PolyDriver poly;
    IAudioRender *put;
    BufferedPort<Sound> port;
    Semaphore mutex;
    bool muted;
    bool saving;
    std::deque<Sound> sounds;
    int samples;
    int channels;
	BufferedPort<Bottle> audioPortLeft;
    BufferedPort<Bottle> audioPortRight;
	Bottle audioBottleLeft;
	Bottle audioBottleRight;
	

public:
    Echo() : mutex(1) {
        put = NULL;
        port.useCallback(*this);
        port.setStrict();
        muted = false;
        saving = false;
        samples = 0;
        channels = 0;
        put = NULL;
    }

    bool open(Searchable& p) {
        bool dev = true;
        if (p.check("nodevice")) {
            dev = false;
        }
        if (dev) {
            poly.open(p);
            if (!poly.isValid()) {
                printf("cannot open driver\n");
                return false;
            }
            
            if (!p.check("mute")) {
                // Make sure we can write sound
                poly.view(put);
                if (put==NULL) {
                    printf("cannot open interface\n");
                    return false;
                }
            }
        }
            
        port.setStrict(true);
        if (!port.open(p.check("name",Value("/AudioAttention/listener")).asString())) {
            printf("Communication problem\n");
            return false;
        }
        
        if (p.check("remote")) {
            Network::connect(p.check("remote",Value("/remote")).asString(),
                             port.getName());
        }
        
        openPort();
        return true;
    }

	void openPort()
	{
		std::string portNameLeft = "/audioPortLeft";
		std::string portNameRight = "/audioPortRight";
		audioPortLeft.open(portNameLeft.c_str());
		audioPortRight.open(portNameRight.c_str());
	}
	
    void onRead(Sound& sound)
     {
       
        #ifdef TEST
        //this block can be used to measure time elapsed between two sound packets
        static double t1= yarp::os::Time::now();
        static double t2= yarp::os::Time::now();
        t1= yarp::os::Time::now();
        printf("onread %f\n", t2-t1);
        t2 = yarp::os::Time::now();
        #endif

        int ct = port.getPendingReads();
        //printf("pending reads %d\n", ct);
        while (ct>padding) {
            ct = port.getPendingReads();
            printf("Dropping sound packet -- %d packet(s) behind\n", ct);
            port.read();
        }
        mutex.wait();
        /*
          if (muted) {
          for (int i=0; i<sound.getChannels(); i++) {
          for (int j=0; j<sound.getSamples(); j++) {
          sound.put(0,j,i);
          }
          }
          }
        */
        if (true) {            
            std::cout << " Recieved data from grabber. Writing to bottle" << std::endl;
            putFrame2Yarp(sound);
        }
        mutex.post();
        Time::yield();
    }


    void putFrame2Yarp(Sound& sound) {
    	//*************************************************************
		//Matt's code:
		//added code here to write this frame into the mapped audio data file at the appropriate index

		unsigned char *rawData=(unsigned char*)malloc(kNumBytes);
		
		rawData=sound.getRawData();
		
		//sound.getRawData() returns a vector with all the left channel then all the right channel (i.e. not interleaved).  We need to rearrange to be L,R,L,R 
		//now unpack and rearrange the bytes in the frame
		
		
		short left[kNumSamples]; //temporarily store the two channels in separate vectors
		short right[kNumSamples];
		
		memcpy(left,(void *)&rawData[0],kNumSamples*2); //pull out 2 bytes for each sample (i.e. 16-bits)
		memcpy(right,(void *)&rawData[kNumBytes/2],kNumSamples*2);
		
		Bottle &tmpLeft = audioPortLeft.prepare(); 
		Bottle &tmpRight = audioPortRight.prepare(); 
		
		//now think in shorts
		short audioData[kNumSamples*2]= {0};	
		int writeHere=0;

		for(int i=0;i<kNumSamples;i++){
			
			audioData[writeHere]=left[i];
			audioBottleLeft.addInt(left[i]);
			writeHere++;
			
			audioData[writeHere]=right[i];
			audioBottleRight.addInt(right[i]);
			writeHere++;
			
		}
		
		tmpLeft = audioBottleLeft;
		tmpRight = audioBottleRight;
		
		audioPortLeft.write();
		audioPortRight.write();
		
		audioBottleLeft.clear();
		audioBottleRight.clear();
	}
	
    bool close() {
        port.close();
        mutex.wait(); // onRead never gets called again once it finishes       
       
        return true;
    }
};

int main(int argc, char *argv[]) {
    yarp::os::Network yarp;
 

    // see if user has supplied audio device
    Property p;
    if (argc>1) {
        p.fromCommand(argc,argv);
    }

    // otherwise default device is "portaudio"
    if (!p.check("device")) {
        p.put("device","portaudio");
        p.put("write",1);
        p.put("delay",1);
    }
    
    Echo echo;
    echo.open(p);


    bool done = false;

    while(!done)
    {
        //do nothing
    }


	return 0;
}
