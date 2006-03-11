/*
 * Copyright (c) 2006
 * Media informatics Department
 * RWTH Aachen Germany
 * http://media.informatik.rwth-aachen.de
 *
 * Redistribution and use of the source code and binary, with or without
 * modification, are permitted under OSI Artistic License 
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

#include "KeyListener.h"

CKeyListener* CKeyListener::NewLC()
{
   CKeyListener* self = new (ELeave) CKeyListener();
   CleanupStack::PushL(self);
   return self;
}

CKeyListener* CKeyListener::NewL()
{
   CKeyListener* self = NewLC();
   CleanupStack::Pop(self);
   return self;
}

CKeyListener::CKeyListener() : CActive(0)
{}

CKeyListener::~CKeyListener()
{
	Cancel();
}

void CKeyListener::ConstructL(CCodeListener* aCodeListener)
{
	iCodeListener = aCodeListener;
	CActiveScheduler::Add(this);
}

void CKeyListener::DoCancel()
{
	// clean up
	//wg->CancelCaptureKey(EKeyLeftArrow);
	//wg->Destroy();
	ws.EventReadyCancel();
	//ws.Close();
}

void CKeyListener::StartL()
{
	// connect to window server
	User::LeaveIfError(ws.Connect());

	// create a window group for the thread
	wg = new (ELeave) RWindowGroup(ws);
	wg->Construct((TUint32)&wg, EFalse);

	// capture a key
	User::LeaveIfError(wg->CaptureKey(EKeyLeftArrow, 0, 0));

	// hide this window group from the app switcher
	wg->SetOrdinalPosition(-1);
	wg->EnableReceiptOfFocus(EFalse);
	
	iStatus = KRequestPending;
	ws.EventReady(&iStatus);
	SetActive();
}


void CKeyListener::RunL()
{
	if (iStatus.Int()==KErrNone)
	{
			TWsEvent e;
			ws.GetEvent(e);

			TUint16 c;
			TKeyEvent* aKeyEvent=e.Key();
			c = aKeyEvent->iCode;

			//iCodeListener->SendKeyToProxy(aKeyEvent->iCode, 1);
			//iLog.WriteFormat(_L("KeyCode Received = %d"),c);
	}
	ws.EventReady(&iStatus);
	SetActive();
}

void CKeyListener::StopL()
{
	DoCancel();
}