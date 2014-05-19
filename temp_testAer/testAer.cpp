// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * This class use the USB retina driver wrote by
 * Martin Ebner, IGI / TU Graz (ebner at igi.tugraz.at)
 *
 *  The term of the contract of the used source is :
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 * This driver is based on the 2.6.3 version of drivers/usb/usb-skeleton.c
 * (Copyright (C) 2001-2004 Greg Kroah-Hartman (greg@kroah.com))
 *
 */

#include "testAer.h"
//#include <yarp/os/all/h>

//#include <sys/types.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/types.h>
#include <inttypes.h>
//#include <stdint.h>

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

#include <sys/time.h>
#include <sched.h>

using namespace std;
using namespace yarp::os;
//using namespace emorph::ebuffer;

extern int errno; 
//EAGAIN		11	/* Resource temporarily unavailable */


#define INPUT_BIN_U32U32LE


int main () {
    
printf("testAer initialization .... \n");

    
     
    // passing the parameter to the class variable
    string portDeviceName = "/dev/aerfx2_0";
    	
	int file_desc = open(portDeviceName.c_str(), O_RDWR | O_NONBLOCK);

	if(file_desc < 0)
	{
		printf("Cannot open device file: %s \n", portDeviceName.c_str());
        return -1;
	}
    //initialisation of the module
    
    // 8192 number of max event that can be read
    //SIZE_OF_DATA is SIZE_OF_EVENT * 8bytes
    u32 monBufSize_b = SIZE_OF_EVENT * sizeof(struct aer);
    u32 monBufSize_a = SIZE_OF_EVENT * 2 * sizeof(struct atom);
    int sizeofstructatom = sizeof ( struct atom) ;	
	
    // pmon reads events from the device
    struct aer *pmon = (aer *)  malloc(monBufSize_b);
    if ( pmon == NULL ) {
        printf("pmon malloc failed \n");
    }
    struct atom *pmonatom = (atom *) malloc(monBufSize_a);
    if ( pmonatom == NULL ) {
        printf("pmon atom  malloc failed \n");
    }
	
	while(true)
	{
	   int r = read(file_desc, pmonatom, monBufSize_b);
    //printf("received %d bytes \n", r);
    //r = read(file_desc, &buffer, monBufSize_b);
    //printf("called read() with monBufSize_b == %d -> retval: %d\n", (int)monBufSize_b, (int)r);
    
	    if(r < 0) {
	        if (errno == EAGAIN) {
            // everything ok, just no data available at the moment...
            // we will be called again in a few miliseconds..
			printf("No data available!!!"); 
	            
	        } else {
        	    printf("error reading from aerfx2: %d\n", (int)errno);
	            perror("perror:");
	            return 1;
        	}
	    }   
		
	if(r % sizeofstructatom != 0) {
        printf("ERROR: read %d bytes from the AEX!!!\n", r);
    	}
	u32 monBufEvents = r/sizeofstructatom;
	u32 tempA;
  for (int i = 0; i < monBufEvents ; i++ ) {
  
           
        tempA = pmonatom[i].data;       
        
        printf("%08X \n",tempA);

     } 
    }
    
    //if (save) {	  
    //    fprintf(fout,"------------------------\n");
    //}
    
     //*******************************************************************************************************

   close(file_desc);

}
