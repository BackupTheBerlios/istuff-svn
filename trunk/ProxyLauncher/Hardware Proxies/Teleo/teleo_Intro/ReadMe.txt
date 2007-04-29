User's Guide
Teleo Introductory Module with iStuff framework


Installation:

What you need to install?
-iStuff Framework, Download from http://istuff.berlios.de/
-Driver of Teleo, Download from http://www.makingthings.com/products/downloads/max_externals.htm
       The part "Teleo Max Library and USB Driver" you can download for windows and Mac OS X

Configuration:
 
 Connect the power module to the power and connect the USB module to the USB   port of your computer. (If they are connected the lights on the power and USB module will be turned on.)

 Connecting Analog In Device
       
1)First connect the Analog input device (i.e. slider) to the Teleo Multi IO Module:
Connect the ground to the last one, which is further than other 2.
Connect the power to the other end of it.
Connect the analogue input 0 to the signal.
Signal is usually in the middle of power and ground but not necessarily
Now your Analog input device is ready now.
For more information about how to connect see http://www.makingthings.com/products/documentation/teleo_intro_user_guide/index.html#ain

Connecting Digital In Device

connect the Digital In Device (i.e.button) to the Teleo Multi IO Module:
Connect the ground and one digital input.
For more information about how to connect see http://www.makingthings.com/products/documentation/teleo_intro_user_guide/index.html#din
For running this time you need to add -din <port number> like -dout 0 (See Building and Running).

Connecting Digital Out Device

connect the Digital Out Device(i.e. LED) to the Teleo Multi IO Module:
For more information about how to connect see http://www.makingthings.com/products/documentation/teleo_intro_user_guide/index.html#dout
For running this time you need to add -dout <port number> like -dout 0 (See Building and Running).

Connecting PWM Device

connect the PWM Device to the Teleo Multi IO Module:
For more information about how to connect see http://www.makingthings.com/products/documentation/teleo_intro_user_guide/index.html#pwm
For running this time you need to add -pwmout <port number> like -pwmout 0 (See Building and Running).




Building and Running:
Before being able to build and run the program you need to do some changes.
First of all go to the directory ~/iStuff Framework v1.3beta/Hardware Proxies/Teleo/Mac OS X , you can find teleo.cpp there which you need to build it and run it. Open a new Shell and change path to ~/iStuff Framework v1.3beta/Hardware Proxies/Teleo/Mac OS X/build and type ./teleo -server localhost -name <the name of this event client> -ain0
If you are using the port number 0 of analogue input.
For other existing options you can use the following options:

teleo [-server server_name] [-device usb_device] [-ain #] [-din #] [-pwmout #] [-dout #]
  -server : name of event heap server (default: localhost)
  -name   : name of this event client for the subscription templates to distinguish between multiple Teleo clients connected to the same event heap (default: hostname)
  -device : usb device that Teleo device is connected to (default: search all USB devices)
  -ain    : ID of analog input, from 0 to 3 (can be specified multiple times)
  -din    : ID of digital input, from 0 to 3 (can be specified multiple times)
  -pwmout : ID of pulse width modulated output, from 0 to 1 (can be specified multiple times)
  -dout   : ID of digital output, from 0 to 3 (can be specified multiple times)

You can also use more than one of these ports at the same time 

