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

#ifndef ISTUFFMOBILEAPPUI_H
#define ISTUFFMOBILEAPPUI_H

#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknappui.h>
#include <f32file.h>
#include <flogger.h>
#include "CodeListener.h"


class CiStuffMobileContainer;
class CCodeListener;

//!  CiStuffMobileAppUi class is a mobile phone application user interface class which initiates the communication with the "iStuff Mobile" proxy program
/*!  This class initiates the "iStuff Mobile" mobile phone application by
		 providing a user interface to the user for communication.
*/

class CiStuffMobileAppUi : public CAknAppUi
{
    public: 

				//!  Second level constructor for CiStuffMobileAppUi class
				/*!  This method initiates the logging mechanism for the
						 mobile phone application, creates an instance of
						 CiStuffMobileContainer class and creates an instance 
						 of CCodeListener class.
						 
						 \sa CiStuffMobileContainer
						 \sa CCodeListener
				*/
        void ConstructL();
        
        ~CiStuffMobileAppUi();
        
        //!  Sets the connected class member
				/*!  This method sets the connected class member
						 to the boolean value that is passed as
						 parameter.
						 
						 \param iConnect as boolean.
				*/
				void SetConnected(TBool iConnect);

    private:

        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
        
        //!  Passes the key presses from the mobile phone to the "iStuff Mobile" proxy
				/*!  This method checks if the "iStuff Mobile" mobile phone
						 application is connected to the "iStuff Mobile" proxy.
						 If it is connected then what ever keys are pressed on
						 the UI are passed to the "iStuff Mobile" proxy program.
						 
						 \param aKeyEvent as TKeyEvent class type.
						 \param aType as TEventCode class type.
						 \return an indication whether key was consumed or not.
						 
						 See nokia series 60 documentation for more details on parameters.
				*/
        virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        //!  Handles the commands invoked by menu selection
				/*!  This method is invoked whenever an option from the
						 popup menus is selected. These menus are selected 
						 using the left and right soft keys on the mobile 
						 phone. Selection of some menu option generates a
						 command which is handled by this method.
						 
						 \param aCommand as TInt.
				*/
				void HandleCommandL(TInt aCommand);
				
			  //!  Constructs a directory.
				/*!  This method takes a path input and contructs
						 a directory on the mobile phone under that path.
						 
						 \param aPath as TDesC class type. This a typical string.
						 \return as success indication (0 if the creation was successful).
				*/
				TInt MakeDir(const TDesC& aPath);

				CiStuffMobileContainer* iAppContainer;
				CCodeListener* iProxyServer;
				TBool connected;
				RFileLogger iLog;
};

#endif