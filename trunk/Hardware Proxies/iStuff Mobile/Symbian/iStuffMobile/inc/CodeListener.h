/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OPI Artistic License 
 * (http://www.opensource.org/licenses/artistic-license.php) provided that 
 * the source code retains the above copyright notice and the following 
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:	  Faraz Ahmed Memon
 *			  Tico Ballagas
 *
 * Version:	  1.0
 */

#ifndef CODELISTENER_H
#define CODELISTENER_H

#include <es_sock.h>
#include <in_sock.h>
#include <BTExtNotifiers.h>
#include <bt_sock.h>
#include <flogger.h>
#include <apacmdln.h>
#include <EikDll.h>
#include <apgcli.h>

#include "Global.h"
#include "iStuffMobileAppUi.h"
#include "iStuffMobileContainer.h"
#include "SoundPlayer.h"
#include "KeyListener.h"
#include "BtDiscoverer.h"
#include "BtServiceListContainer.h"

class CiStuffMobileAppUi;

//!  CCodeListener class is the main class from "iStuff Mobile" mobile phone application.
/*!  This class is the main class from "iStuff Mobile" mobile phone application. Following
		 are the functions of this class:
		 -# Extend the CActive class to run object of this class in a co-operative threading
		 		environment.
		 -# Listen to the Opcodes sent by the "iStuff Mobile" proxy and initiate appropriate
		 		actions.
		 -# Enable two way communication with the "iStuff Mobile" proxy.
*/

class CCodeListener : public CActive
{
	public:
		//!  CCodeListener class constructor.
		/*!  The constuctor initializes some class members with the
				 parameters passed to it. It also intializes the CActive
				 superclass constructor with a priority of 0 (Normal).
				 
				 \param aApplicationUi as a pointer to CiStuffMobileAppUi type object.
				 \param aApplicationContainer as a pointer to CiStuffMobileContainer type object.
		*/
		CCodeListener(CiStuffMobileAppUi* aApplicationUi, CiStuffMobileContainer* aApplicationContainer);
		
		~CCodeListener();

		//!  Second level constructor for CCodeListener class
		/*!  This method initiates the iLog member viariable
				 and adds the class to the CActiveScheduler.
				 CActiveScheduler schedules all the active objects
				 that are added to it.
				 
				 \param aLog as a pointer to RFileLogger type object.
		*/
		void ConstructL(RFileLogger* aLog);
		
		//!  Initiates the connection with "iStuff Mobile" proxy application.
		/*!  This method initiates a bluetooth communication with
				 "iStuff Mobile" proxy running on a PC. This method is
				 called by the CiStuffMobileAppUi class object whenever
				 the "Connect" menu option is selected from the left pop-
				 up menu.
		*/
		void ConnectToServer();
		
		//!  Connects to a particular serial port service running on "iStuff Mobile" proxy.
		/*!  This method connects to a particular bluetooth serial 
				 port service running on the "iStuff Mobile" proxy.
				 
				 \param portNo as TUint8. Denotes the port number to connect to.
		*/
		void ConnectToService(TUint8 portNo);
		
		//!  Diconnects the "iStuff Mobile" mobile phone application from the proxy.
		/*!  This method disconnects the "iStuff Mobile" mobile
				 phone application from the "iStuff Mobile" proxy
				 application and closes all the open ports.
		*/
		void DisconnectFromServer();
		
		//!  Passes a key press on the mobile phone to the "iStuff Mobile" proxy application.
		/*!  This method passes a key press on the mobile phone 
				 to "iStuff Mobile" proxy application. This method is
				 called by CiStuffMobileAppUi or the CKeyListener
				 class objects.
				 
				 \param code as TUint16. Represents the code of the 
				 				key pressed.
				 \param aType as TUint16. Represents the type of key 
				 				press (0 means key down, 1 means key pressed, 
				 				2 means key released).
		*/
		void SendKeyToProxy(TUint16 code,TUint16 aType);
		
		//!  Check the status of connection with the proxy
		/*!  This method check if the "iStuff Mobile" mobile 
				 phone application is connected to the proxy.
				 
				 \return a ETrue or EFalse depending on status of connection.
		*/
		TBool GetConnected();

		//!  Lauches an external application
		/*!  This method is called when the Opcode received is 
				 OPCODE_LAUNCHAPP. This method launches an application
				 found at the path passed as parameters.
				 
				 \param path as TUint16 pointer. contains the path
				 				of the application to be launched including
				 				the application name.
		*/
		void LaunchApp(TUint16* path);

	private:
		
		//!  Receives a single Opcode.
		/*!  This method receives a single Opcode sent by the "iStuff 
				 Mobile" proxy and sets the current object active. When the
				 reading of the Opcode is completed, the RunL() method is
				 automatically invoked.
		*/
		void StartReceiving();
		
		//!  Decodes the Opcode sent by the proxy
		/*!  This method decodes the Opcode sent by "iStuff Mobile" 
				 proxy application and initiates an appropriate action.
		*/
		void DecodeOpcode();
		
		//!  Cancels all the pending read requests
		/*!  This method cancels all the pending read requests on
				 the socket.
		*/
		virtual void DoCancel();
		
		//!  Callback method from the CActiveScheduler
		/*!  This method is a callback method which is invoked by 
				 the Active Scheduler
		*/
		virtual void RunL();

		//!  Decodes a key press received from the proxy.
		/*!  This method is called when the Opcode received is 
				 OPCODE_KEY_RECEIVED. This method retrieves parameters
				 required for simulating a key press on the mobile 
				 phone and initiates the key simulation.
		*/
		void DecodeReceivedKey();
		
		//!  Simulates a key press on the mobile phone.
		/*!  This method is called from DecodeReceivedKey method.
				 It simulates the key press on the mobile phone. The
				 key press is sent to whatever application is in the
				 foreground.
				 
				 \param repeat as TUint16. Represents the repeat code 
				 				for the key press.
				 \param scancode as TUint16. Represents the scancode 
				 				for the key press.
				 \param code as TUint16. Represents the code of the 
				 				key press.
				 				
				 Refer to the Nokia Series 60 SDK documentation for 
				 details on Key Events.
		*/
		void SendKeyToPhone(TUint16 repeat,TUint16 scancode,TUint16 code);

		//!  Plays a sound file on the mobile phone.
		/*!  This method is called when the Opcode received is 
				 OPCODE_PLAYSOUND. This method retrieves the path
				 sent by the proxy and intiates the playback of a
				 sound file on the mobile phone.
		*/
		void PlaySoundFile();
		
		//!  Stops the playback of the sound file.
		/*!  This method is called when the Opcode received is 
				 OPCODE_STOPSOUND. This method stops the playback
				 of a sound file which was initiated by PlaySoundFile()
				 method.
		*/
		void StopSoundFile();
		
		//!  Closes an external application
		/*!  This method is called when the Opcode received is 
				 OPCODE_CLOSEAPP. This method closes an application
				 with the name passed as parameter. Name is typically
				 the caption of the application.
				 
				 \param name and TUint16 pointer. contains the name
				 				of the application to be closed.
		*/
		void CloseApp(TUint16* name);
		
		//!  Initiates the key capturing procedure.
		/*!  This method is called when the Opcode received is 
				 OPCODE_START_KEYCAPTURE. This method starts capturing
				 keys that are pressed on the mobile phone and relays
				 them to the "iStuff Mobile" proxy application.
		*/
		void StartKeyCapture();
		
		//!  Stops the key capture.
		/*!  This method is called when the Opcode received is 
				 OPCODE_STOP_KEYCAPTURE. This method stops the key
				 capture and relay of keys to the "iStuff Mobile"
				 proxy.
		*/
		void StopKeyCapture();

		//!  Initiates the profile change process on the mobile phone.
		/*!  This method is called when the Opcode received is 
				 OPCODE_CHANGEPROFILE. This method retreives the 
				 profile number sent by the proxy and initiates the
				 process to change the profile to the profile number
				 provided. Profile number is the number of profile in
				 the nokia series 60 mobile phone "Profiles" application.
		*/
		void ChangeProfile();
		
		//!  Completes the profile change process.
		/*!  This method is invoked after the timer set by the
				 ChangeProfile() method expires. It continues the
				 process of changing profile and finishes it.
				 
				 \param aObject as TAny pointer. In this case it is
				 pointer to the CCodeListener type object.
				 
				 \return a TInt. 
		*/
		static TInt ContinueChangeProfile(TAny* aObject);
		
		//!  Retreives a path from the socket.
		/*!  This method is invoked whenever a path is expected
				 from the "iStuff Mobile" proxy.
				 
				 \return a TUint16 pointer. Represents a path as a string. 
		*/
		TUint16* GetPath();

		CiStuffMobileAppUi* iApplicationUi;
		CiStuffMobileContainer* iApplicationContainer;

		TBuf8<1> data;
		RSocketServ iSocketServ;
		RSocket iSocket;

		RNotifier iDeviceSelector;
		TBTDeviceResponseParamsPckg iResponse;
		TBool isConnected;
		CBTDiscoverer* iServices;
		CBTServiceListContainer* iBtSlContainer;

		CSoundPlayer* iSoundPlayer;
		CKeyListener* iKeyListener;
		CDesCArrayFlat*	iAppList;

		RFileLogger* iLog;
		
		CPeriodic*	iPeriodic;
		TUint8		iProfileNo;
};
#endif