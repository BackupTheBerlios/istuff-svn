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
#include "CodeListener.h"

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

void CKeyListener::ConstructL(CCodeListener* aCodeListener,RFileLogger* aLog)
{
	iCodeListener = aCodeListener;
	iLog = aLog;
	CActiveScheduler::Add(this);
}

void CKeyListener::DoCancel()
{
	// clean up
	ws.EventReadyCancel();
	wg->Close();
}

void CKeyListener::StartL()
{
	// connect to window server
	User::LeaveIfError(ws.Connect());

	// create a window group for the thread
	wg = new (ELeave) RWindowGroup(ws);
	wg->Construct((TUint32)&wg, EFalse);
	
	InterceptKeys();

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

			if(e.Type() == 1)
			{
				TUint16 c;
				TKeyEvent* aKeyEvent=e.Key();
				c = aKeyEvent->iCode;

				iCodeListener->SendKeyToProxy((TUint16)aKeyEvent->iCode,(TUint16) e.Type());
			}
			else
			{
				iCodeListener->SendKeyToProxy((TUint16)0,(TUint16) e.Type());
			}
			
	}
	else
			iLog->WriteFormat(_L("Error %d while capturing key presses"),iStatus.Int());

	ws.EventReady(&iStatus);
	SetActive();
}

void CKeyListener::StopL()
{
	DoCancel();
}

void CKeyListener::InterceptKeys()
{
	// capture a key

	for(TInt i=48;i<=57;i++)					//looping over keypad keys from 0-9
	{
		User::LeaveIfError(wg->CaptureKey(i, 0, 0));
		User::LeaveIfError(wg->CaptureKeyUpAndDowns(i, 0, 0));
	}
	
	for(TInt i=63495,j=0; i<=63498; i++,j++)	//looping over joypad keys left,right,up and down
	{
		User::LeaveIfError(wg->CaptureKey(i, 0, 0));
		User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyLeftArrow + j, 0, 0));
	}

	for(TInt i=63586,j=0 ;i<=63587; i++,j++)	//Yes and No keys i.e. green and red
	{
		User::LeaveIfError(wg->CaptureKey(i, 0, 0));
		User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyYes+j, 0, 0));
	}

	User::LeaveIfError(wg->CaptureKey(EKeyBackspace, 0, 0));			//the backspace key i.e. c
	User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyBackspace, 0, 0));
	
	User::LeaveIfError(wg->CaptureKey(35, 0, 0));						//hase key
	User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyHash, 0, 0));

	User::LeaveIfError(wg->CaptureKey(EKeyDevice3, 0, 0));				//joystick enter key
	User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyDevice3, 0, 0));

	User::LeaveIfError(wg->CaptureKey(EKeyLeftShift, 0, 0));			//the pencil key
	User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyLeftShift, 0, 0));

	User::LeaveIfError(wg->CaptureKey(EKeyApplication0, 0, 0));			//menu key
	User::LeaveIfError(wg->CaptureKeyUpAndDowns(EStdKeyApplication0, 0, 0));
}