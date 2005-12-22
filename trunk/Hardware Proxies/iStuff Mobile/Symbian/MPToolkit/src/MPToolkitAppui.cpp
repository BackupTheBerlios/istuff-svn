/*
* ============================================================================
*  Name     : CMPToolkitAppUi from MPToolkitAppui.cpp
*  Part of  : MPToolkit
*  Created  : 01.11.2005 by Faraz Ahmed Memon
*  Implementation notes:
*     Initial content was generated by Series 60 Application Wizard.
*  Version  :
*  Copyright: i10 RWTH Aachen
* ============================================================================
*/

#include "MPToolkitAppui.h"
#include "MPToolkitContainer.h" 
#include <MPToolkit.rsg>
#include "MPToolkit.hrh"
#include <avkon.hrh>


void CMPToolkitAppUi::ConstructL()
{
	BaseConstructL();

	iProxyServer = new CCodeListener(this);
	iProxyServer->ConstructL(iEikonEnv);

    iAppContainer = new (ELeave) CMPToolkitContainer;
    iAppContainer->SetMopParent( this );
    iAppContainer->ConstructL( ClientRect() );
    AddToStackL( iAppContainer );
}

CMPToolkitAppUi::~CMPToolkitAppUi()
{
    if (iAppContainer)
    {
        RemoveFromStack( iAppContainer );
        delete iAppContainer;
    }
	
	delete iProxyServer;
}

void CMPToolkitAppUi::DynInitMenuPaneL(TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
{

}


TKeyResponse CMPToolkitAppUi::HandleKeyEventL(const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
{
    return EKeyWasNotConsumed;
}

void CMPToolkitAppUi::HandleCommandL(TInt aCommand)
{
    switch ( aCommand )
    {
        case EAknSoftkeyBack:
		{
			iAppContainer->SendToBackground();
			break;
		}
        case EEikCmdExit:
        {
            Exit();
            break;
        }
        case EMPToolkitCmdAppConnect:
        {
			iProxyServer->ConnectToServer();
            break;
        }
		case EMPToolkitCmdAppDisconnect:
		{
			iProxyServer->DisconnectFromServer();
            break;
        }
        default:
	        break;
    }
}

void CMPToolkitAppUi::SetConnected(TBool iConnect)
{
	if(iConnect)
		iAppContainer->iLabel->SetTextL( _L("Status :\nConnected") );
	else
		iAppContainer->iLabel->SetTextL( _L("Status :\nNot Connected") );
}
