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

#ifndef BT_SERVICE_LIST_CONTAINER_H
#define BT_SERVICE_LIST_CONTAINER_H

#include <coecntrl.h>
#include <aknlists.h>
#include <eiklbo.h>
#include <e32std.h>
#include <flogger.h>
#include <barsread.h>

class CCodeListener;

//!  CBTServiceListContainer class is the UI Container containing list of bluetooth serial port services
/*!  This class is a container UI which is displayed when
		 discovery of serial port services is under process.
		 This class contains a list of all the BT serial port
		 services and allows user to select a service to 
		 connect to.
*/
class CBTServiceListContainer: public CCoeControl, public MEikListBoxObserver
{

	public:
		
		/** @name CBTServiceListContainer class first level constructors
		*   These methods create an object of CBTServiceListContainer class
				and initializes some class variables.
		
				\param aLog as RFileLogger object pointer.
				\param aCodeListener as CCodeListener object pointer.
				
				\return CBTServiceListContainer object pointer.
		*/
		//@{
		static CBTServiceListContainer* NewL(RFileLogger* aLog, CCodeListener* aCodeListener);
		static CBTServiceListContainer* NewLC(RFileLogger* aLog, CCodeListener* aCodeListener);
		//@}
		
		//!  Second level constructor for CBTServiceListContainer class
		/*!  This method initializes the container by contructing a list
				 of port number and names. It also constructs a label.
				 
				 \param aRect as TRect object. Represents the area to which
						 		container should be drawn.
		*/
		void ConstructL(const TRect& aRect);
		
		~CBTServiceListContainer();
		
		//!  Add an item to the list
		/*!  This method adds an item to the list. The item in this
				 case is the port number and port name of a bluetooth
				 service.
				 
				 \param aServicePort as TUint. Represents a service port.
				 \param aServiceName as TUint16 pointer. Represents a 
				 				service name.
		*/
		void AddItemToList(TUint aServicePort, TUint16* aServiceName);

	private:

		//! CBTServiceListContainer class constructor
		/*! The constructor initializes some class variables with
				parameters passed.
		
				\param aLog as RFileLogger object pointer.
				\param aCodeListener as CCodeListener object pointer.
		*/
		CBTServiceListContainer(RFileLogger* aLog, CCodeListener* aCodeListener);

		//!  Returns the number of component in the container
		/*!  This method returns the number of component in the
				 container.
				 
				 \return an integer indicating number of components.
		*/
		TInt CountComponentControls() const;
		
		//!  Returns the pointer to a component inside the container
		/*!  This method returns a to pointer to the component inside
				 the container.
				 
				 \param aIndex as an TInt. Represents the index of the
				 				components. Indexs start from 0 with component
				 				constructed first to have a lower index than the
				 				one constructed later.

				 \return pointer to the component.
		*/
		CCoeControl* ComponentControl(TInt aIndex) const;
		
		//!  Draws the container
		/*!  This method Draws the container on the screen with the
				 white background.
				 
				 \param aRect as TRect class type. Represents the area 
				 				to be used for drawing the container.
		*/
		void Draw(const TRect& aRect) const;
		
		//!  Resizes the components inside the container
		/*!  This method is called when the size of the container
				 changes. It adjusts the size of the components inside 
				 the container.
		*/
		void SizeChanged();
		
		//!  Sets up scroll bars for the list
		/*!  This method is sets up scroll bars for the list.
		*/
		void SetupScrollBarsL();

		//!  Forwards the key pressed on the container to the list
		/*!  This method forwards all the key presses by the user
				 while on the container to the list.
				 
				 \param aKeyEvent as TKeyEvent object. Represents the
				 				key pressed.
				 \param aType as TEventCode type. Represents the type
				 				of the key.
		*/
		TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
		
		//!  Handles the events generated by the listbox
		/*!  This method handles all the events generated by the
				 listbox. In this case it gets the item that user 
				 selected from the list, gets the number part from 
				 that item and passes the number to the CCodeListener
				 object as the port number to connect to.
				 
				 \param aListBoxEvent as TListBoxEvent type. 
				 				Represents the type of the listbox event.
		*/
		void HandleListBoxEventL(CEikListBox* /*aListBox*/, TListBoxEvent aListBoxEvent);
		
		CAknColumnListBox* iPortList;
		CEikLabel* iLabel;
		CCodeListener* iCodeListener;

		RFileLogger* iLog;

		CCodeListener* aCodeListener;

};

#endif