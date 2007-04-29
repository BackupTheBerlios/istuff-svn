This software is ©2005 Christian Klein with modifications made by 
Pall Thayer http://www.this.is/pallit and Rafael Ballagas.
See source-code for license details (BSD license).

This software allows you to read the output from the Apple Motion Sensor (aka.
Sudden Motion Sensor, aka. AMS, aka. SMS) that has now become standard hardware
in all portable computers from Apple.

Compiling:
	A Makefile is included so all you have to do is cd to the 'motion' directory
	and type 'make'.
	
Usage:
	Different models of Apple's line of portable computers handle the motion
	sensor differently. Therefore you have to tell 'motion' what model to
	retrieve data for. The current options are:
		powerbook
		ibook
		hirespb
		
	cd to the directory containing the compiled binary and type:
		./motion
	for instructions.
	
	In a usage scenario, the model can be determined thus:
		/usr/sbin/system_profiler SPHardwareDataType|/usr/bin/grep -i 'machine name'
	If the output contains 'PowerBook' use ./motion powerbook
	If the output contains 'iBook' use ./motion ibook
	If the output contains 'Mac' use ./motion hirespb
	