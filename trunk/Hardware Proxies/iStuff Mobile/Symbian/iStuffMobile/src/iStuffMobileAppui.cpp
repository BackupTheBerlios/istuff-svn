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

// INCLUDE FILES
#include "iStuffMobileAppui.h"
#include "iStuffMobileContainer.h" 
#include <iStuffMobile.rsg>
#include "iStuffMobile.hrh"
#include <avkon.hrh>


void CiStuffMobileAppUi::ConstructL()
{
	BaseConstructL();

	MakeDir(_L("c:\\Logs\\"));
	MakeDir(_L("c:\\Logs\\iStuffMobile\\"));
	
	iLog.Connect();
	iLog.CreateLog(_L("iStuffMobile"),_L("ErrorLog"),EFileLoggingModeOverwrite);
	iLog.Write(_L("Log Created"));

	connected = EFalse;
	iProxyServer = new CCodeListener(this);
	iProxyServer->ConstructL(&iLog);

    iAppContainer = new (ELeave) CiStuffMobileContainer;
    iAppContainer->SetMopParent( this );
    iAppContainer->ConstructL( ClientRect() );
    AddToStackL( iAppContainer );
}

CiStuffMobileAppUi::~CiStuffMobileAppUi()
{
    if (iAppContainer)
    {
        RemoveFromStack( iAppContainer );
        delete iAppContainer;
    }
	
	delete iProxyServer;

	iLog.CloseLog();
	iLog.Close();
}

void CiStuffMobileAppUi::DynInitMenuPaneL(TInt /*aResourceId*/,CEikMenuPane* /*aMenuPane*/)
{

}


TKeyResponse CiStuffMobileAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
{
    if(iProxyServer->GetConnected())
	{
		iProxyServer->SendKeyToProxy(aKeyEvent.iCode,aType);
		return EKeyWasConsumed;
	}
	else
	{
		return EKeyWasNotConsumed;
	}
}

void CiStuffMobileAppUi::HandleCommandL(TInt aCommand)
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
        case EiStuffMobileCmdAppConnect:
        {
			iProxyServer->ConnectToServer();
            break;
        }
		case EiStuffMobileCmdAppDisconnect:
		{
			iProxyServer->DisconnectFromServer();
            break;
        }
        default:
	        break;
    }
}

void CiStuffMobileAppUi::SetConnected(TBool iConnect)
{
	if(iConnect)
		iAppContainer->iLabel->SetTextL( _L("Status :\nConnected") );
	else
		iAppContainer->iLabel->SetTextL( _L("Status :\nNot Connected") );
}

TInt CiStuffMobileAppUi::MakeDir(const TDesC& aPath)
{
	RFs fsSession;
	User::LeaveIfError(fsSession.Connect());
	CleanupClosePushL(fsSession);

	TInt ret = fsSession.MkDir(aPath);

	fsSession.Close();
	CleanupStack::PopAndDestroy(); // fsSession

	return ret;
}