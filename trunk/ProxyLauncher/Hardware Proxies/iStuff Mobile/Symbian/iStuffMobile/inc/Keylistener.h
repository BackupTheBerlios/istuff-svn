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

#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <e32base.h>
#include <flogger.h>
#include <w32std.h>
#include <apgwgnam.h>

class CCodeListener;

//!  CKeyListener class enables and disables the key capturing feature.
/*!  CKeyListener class object is constructed when the opcode 
		 OPCODE_START_KEYCAPTURE is received from the proxy. This 
		 class is responsible for enabling and disabling of the key
		 capturing fuctionality on the mobile phone. This class is
		 also an active object.
*/
class CKeyListener : public CActive
{
	public:
		
		/** @name CKeyListener class first level constructors
		*   These methods create an object of CKeyListener class.
		
				\return CKeyListener object pointer.
		*/
		//@{
		static CKeyListener* NewLC();
		static CKeyListener* NewL();
		//@}
		
		~CKeyListener();
		
		//!  CKeyListener class second level constructor
		/*!  This methods initializes couple of class members with 
				 the parameters passed and adds CKeyListener object to
				 the Active Scheduler.
		
				 \param aCodeListener as CCodeListener object pointer.
				 \param aLog as RFileLogger object pointer.
				 
		*/
		void ConstructL(CCodeListener* aCodeListener,RFileLogger* aLog);
		
		//!  Starts capturing key presses
		/*!  This method starts capturing key presses from the 
				 mobile phone.
		*/
		void StartL();
		
		//!  Stops capturing key presses
		/*!  This method stops capturing key presses from the 
				 mobile phone.
		*/
		void StopL();

	private:

		CKeyListener();
		
		//!  Registers for capturing keys
		/*!  This method registers to capture keys from the mobile
				 phone. It is invoked once.
		*/
		void InterceptKeys();
		
		//!  Callback method from the CActiveScheduler
		/*!  This method is a callback method which is invoked by 
				 the Active Scheduler on completion of an unsynchronized
				 request. In this context this request is waiting for a
				 key events. This method upon receiving the key event initiates
				 the process of relaying it to the "iStuff Mobile" proxy.
		*/
		void RunL();
		
		//!  Cancels all the pending wait requests
		/*!  This method cancels all the pending wait requests for
				 the key events.
		*/
		void DoCancel();

		CCodeListener*	iCodeListener;
		RWsSession		ws;
		RWindowGroup*	wg;
		RFileLogger*	iLog;
		TInt32 keyHandles[21];
		TInt32 keyUADHandles[21];
};

#endif