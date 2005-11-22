/* motion.c
 *
 * a little program to display the coords returned by
 * the powerbook motion sensor
 *
 * A fine piece of c0de, brought to you by
 *
 *               ---===---
 * *** teenage mutant ninja hero coders ***
 *               ---===---
 *
 * All of the software included is copyrighted by Christian Klein <chris@5711.org>.
 *
 * Copyright 2005 Christian Klein. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Christian Klein.
 * 4. The name of the author must not be used to endorse or promote
 *    products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Modified for iBook compatibility by Pall Thayer <http://www.this.is/pallit>
 * Modified for Hi Res Powerbook compatibility by Pall Thayer
 * Modified to continue running and repeat every .1 sec by Rafael Ballagas
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>
#include <IOKit/IOKitLib.h>

/* update interval */
#define INTERVAL_USEC 100000

struct data {
	char x;
	char y;
	char z;
	char pad[57];
};

void printUsage(){
		printf("\tUsage (make sure you are running Mac OS X 10.4.3):\n\t\tFor Powerbooks type: ./motion powerbook\n\t\tFor iBooks type: ./motion ibook\n\t\tFor Hi Resolution PowerBooks type: ./motion hirespb\n");
}

int main(int argc,char *argv[])
{
	int kernFunc;
	char *servMatch;
	kern_return_t result;
	mach_port_t masterPort;
	io_iterator_t iterator;
	io_object_t aDevice;
	io_connect_t  dataPort;
	struct timeval	timeout;
	fd_set read_fds, write_fds, ex_fds;
	int sockfd;
	FD_ZERO(&read_fds);
	FD_ZERO(&write_fds);
	FD_ZERO(&ex_fds);

	IOItemCount structureInputSize;
	IOByteCount structureOutputSize;

	struct data inputStructure;
	struct data outputStructure;
	
	if(argc > 2) {
		printUsage();
		return 0;
	}

	if(!strcmp(argv[1], "powerbook")) {
		kernFunc = 21;
		servMatch = "IOI2CMotionSensor";
	}else if(!strcmp(argv[1], "ibook")){
		kernFunc = 21;
		servMatch = "IOI2CMotionSensor";
	}else if(!strcmp(argv[1], "hirespb")){
		kernFunc = 21;
		servMatch = "PMUMotionSensor";
	}
		
	result = IOMasterPort(MACH_PORT_NULL, &masterPort);

	CFMutableDictionaryRef matchingDictionary = IOServiceMatching(servMatch);

	result = IOServiceGetMatchingServices(masterPort, matchingDictionary, &iterator);

	if (result != KERN_SUCCESS)
	{
		fputs("IOServiceGetMatchingServices returned error.\n", stderr);
		return 0;
	}

	/*
	while( ( aDevice = IOIteratorNext(iterator) )  != 0)
	{
		printf("%d\n", aDevice);
	}
	*/
	
	aDevice = IOIteratorNext(iterator);
	IOObjectRelease(iterator);

	if(aDevice == 0)
	{
		fputs("No motion sensor available\n", stderr);
		return 0;
	}

	result = IOServiceOpen(aDevice, mach_task_self(), 0, &dataPort);
	IOObjectRelease(aDevice);

	if(result != KERN_SUCCESS)
	{
		fputs("Could not open motion sensor device\n", stderr);
		return 0;
	}


	structureInputSize = sizeof(struct data);
	structureOutputSize = sizeof(struct data);

	memset(&inputStructure, 0, sizeof(inputStructure));
	memset(&outputStructure, 0, sizeof(outputStructure));
	
	timeout.tv_sec = 0;
	timeout.tv_usec = INTERVAL_USEC;
	// Create a dummy socket for a file descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	
	while(1)
	{
		int returnCode;
		
		result = IOConnectMethodStructureIStructureO(
						
				dataPort,
				kernFunc,				/* index to kernel function */
				structureInputSize,
				&structureOutputSize,
				&inputStructure,
				&outputStructure
			);

		if(result != KERN_SUCCESS)
		{
			puts("no coords");
		} else {
			printf("%d %d %d\n", outputStructure.x, outputStructure.y, outputStructure.z);
			fflush(stdout);
		}
		
		returnCode = select(sockfd, &read_fds, &write_fds, &ex_fds, &timeout);

	}
	IOServiceClose(dataPort);
		
	return 0;
}

