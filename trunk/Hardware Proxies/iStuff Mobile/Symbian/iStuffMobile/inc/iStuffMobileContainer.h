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

#ifndef ISTUFFMOBILECONTAINER_H
#define ISTUFFMOBILECONTAINER_H

#include <coecntrl.h>
#include <aknlists.h>
#include <apgwgnam.h>
#include <flogger.h>
#include "Global.h"
   
class CEikLabel;

//!  CiStuffMobileContainer class is the default UI container for "iStuff Mobile" mobile phone application
/*!  This class is the default UI which is displayed when the application
		 is launched.
*/
class CiStuffMobileContainer : public CCoeControl, MCoeControlObserver
    {
    public:
        
				//!  Second level constructor for CiStuffMobileContainer class
				/*!  This method initiates the GUI by loading the image that
						 has to be displayed into the background of the container.
						 It also contructs a label and puts it into the contanier.
						 
						 \param aRect as TRect object. Represents the area to which
						 				container should be drawn.
				*/
				void ConstructL(const TRect& aRect);
        
        ~CiStuffMobileContainer();
				
				//!  Sends the GUI to the background
				/*!  Whenver this method is called it send the application
						 UI to the background in the mobile phone. The application
						 is active even when in background.
				*/
				void SendToBackground();
		
				CEikLabel* iLabel;

    private:

        //!  Resizes the components inside the container
				/*!  This method is called when the size of the container
						 changes. It adjusts the size of the components inside 
						 the container.
				*/
        void SizeChanged();
        
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
        
        //!  Draws the GUI
				/*!  This methos Draws the container on the screen with the
						 background image.
						 
						 \param aRect as TRect class type. Represents the area 
						 				to be used for drawing the container.
				*/
        void Draw(const TRect& aRect) const;
        
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
				CFbsBitmap* iBackground;
    };

#endif