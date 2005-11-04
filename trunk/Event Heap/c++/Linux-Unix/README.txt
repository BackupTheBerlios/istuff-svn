You can build a version of the Event Heap libraries directly
- Download the ceheap files from iros.sourceforge.net
  Under /iros/cpp/ceheap2 and /iros/cpp/idk using the following commands:
cvs -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/iros login 
cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/iros co -P iros/cpp/ceheap2 
cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/iros co -P iros/cpp/idk 

- the file /iros/cpp/ceheap2/readme.unix provides further instructions

Important:
in order for automake to work you need at least version 1.6.  You can test your version with the following command:

localhost:~ ballagas% automake --version 
automake (GNU automake) 1.9.4 
Written by Tom Tromey . 