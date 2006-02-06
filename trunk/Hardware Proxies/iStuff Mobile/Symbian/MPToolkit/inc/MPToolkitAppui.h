/*
* ============================================================================
*  Name     : CMPToolkitAppUi from MPToolkitAppui.h
*  Part of  : MPToolkit
*  Created  : 01.11.2005 by Faraz Ahmed Memon
*  Description:
*     Declares UI class for application.
*  Version  :
*  Copyright: i10 RWTH Aachen
* ============================================================================
*/

#ifndef MPTOOLKITAPPUI_H
#define MPTOOLKITAPPUI_H

#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknappui.h>
#include "CodeListener.h"


class CMPToolkitContainer;
class CCodeListener;	

class CMPToolkitAppUi : public CAknAppUi
{
    public: 

        void ConstructL();
        ~CMPToolkitAppUi();
		void SetConnected(TBool iConnect);

    private:

        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);
        virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
		void HandleCommandL(TInt aCommand);

		CMPToolkitContainer* iAppContainer;
		CCodeListener* iProxyServer;
		TBool connected;
};

#endif