/*
* ============================================================================
*  Name     : CMPToolkitContainer from MPToolkitContainer.h
*  Part of  : MPToolkit
*  Created  : 01.11.2005 by Faraz Ahmed Memon
*  Description:
*     Declares container control for application.
*  Version  :
*  Copyright: i10 RWTH Aachen
* ============================================================================
*/

#ifndef MPTOOLKITCONTAINER_H
#define MPTOOLKITCONTAINER_H


#include <coecntrl.h>
#include <aknlists.h>
#include <apgwgnam.h>
#include <flogger.h>
#include "Global.h"
   

class CEikLabel;

class CMPToolkitContainer : public CCoeControl, MCoeControlObserver
    {
    public:
        
		void ConstructL(const TRect& aRect);
        ~CMPToolkitContainer();
		
		void SendToBackground();
		CEikLabel* iLabel;

    private:

        void SizeChanged();
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void Draw(const TRect& aRect) const;
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
		CFbsBitmap* iBackground;
		RFileLogger iConLog;

    };

#endif