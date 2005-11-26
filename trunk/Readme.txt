For information on running and using the iStuff toolkit see "./Getting Started.pdf" in the versioned distribution.

This project redistributes some code and binaries from the iROS (iros.sourceforge.net) under the OSI Artistic License.

--------------------------
Change log

Version 1.0
- Initial Revision

Version 1.1
- Fixed ceheap2 build errors for Microsoft Visual C++ .NET

Version 1.2
- Added information to build applications in C for Mac OS X, 
  and Linux / Unix
- Separated proxies into Hardware / Software

Version 1.3
- Added iPhone proxy
- fixed absolute path error in XCode sample projects for the c++ samples.  Now all projects should have relative paths
- Renamed /Event Heap/ceheap2/Mac OS X/Readme.txt to /Event Heap/ceheap2/Mac OS X/XCode Instructions.txt
- Modified Patch Panel to publish chain events externally
- Fixed a Patch Panel script bug involving global variables
- added /Event Heap/java/java_sample to demonstrate Basic Event Heap concepts in java
- renamed ceheap2 directory to c++ for better clarity
- added gnu make files for the tutorial applications in /Event Heap/c++/Mac OS X/samples/

Version 1.4
- Fixed bug in x10 code
- fixed gnu make files to statically link the idk / ceheap2 libraries to prevent the need for installation of dynamic libraries. 
- fixed serious bug with Patch Panel scripts using empty strings ("")
- fixed Event Heap/c++/Linux/Readme file for a syntax error in the commands to download source.
- Added support for Powerbook Tilt sensor
- Added support for Keynote in PowerPointController and renamed it to "PresentationController"
- Added limited initial support for Phidgets Hardware
- Added support for Teleo Hardware

