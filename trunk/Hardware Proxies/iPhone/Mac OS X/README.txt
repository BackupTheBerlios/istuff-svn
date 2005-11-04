
Step 1
Install the latest javax.comm library from RXTX on sourceforge:  
http://prdownloads.sourceforge.net/jmri/JavaCommInstaller2.hqx?download

Step 2
Create an incoming bluetooth serial port named Nokia6600
	- 10.4: use "System Preferences->Bluetooth->Sharing->Add Serial Port Service"
	- 10.3 and earlier: use /Applications/Bluetooth Serial Utility

-Set type to RS-232
-do not require pairing

Step 3
ensure that ../Symbian/iPhone.SIS (or iPhone-no-rotation.SIS) is installed on the Series 60 phone you would like to use

Step 4
Run "sh run.sh" to initialize the server side.

Step 5
Run "iPhone" on the phone and choose the appropriate device to connect to 

Step 6
Press in to detect a visual code from (http://www.visualcodes.net)

Step 7
Hold the joystick vertically down (not in) to use the Sweep technique (http://media.informatik.rwth-aachen.de/phonecam.html)
