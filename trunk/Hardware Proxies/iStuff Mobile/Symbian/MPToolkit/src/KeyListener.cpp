#include "KeyListener.h"

EXPORT_C CKeyListener* CKeyListener::NewLC()
{
   CKeyListener* self = new (ELeave) CKeyListener();
   CleanupStack::PushL(self);
   self->ConstructL();
   return self;
}

EXPORT_C CKeyListener* CKeyListener::NewL()
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

	iLog.CloseLog();
	iLog.Close();
}

void CKeyListener::ConstructL()
{
	iLog.Connect();
	iLog.CreateLog(_L("MPToolkit"),_L("KeyListener"),EFileLoggingModeOverwrite);
	iLog.Write(_L("created"));
	
	CActiveScheduler::Add(this);
}

void CKeyListener::DoCancel()
{
	// clean up
	ws.EventReadyCancel();
	CleanupStack::PopAndDestroy(3); //ws, wg, wn
}

void CKeyListener::StartL()
{
	// connect to window server
	User::LeaveIfError(ws.Connect());
	CleanupClosePushL(ws);

	// create a window group for the thread
	RWindowGroup wg(ws);
	wg.Construct((TUint32)&wg, EFalse);
	CleanupClosePushL(wg);

	// capture a key
	User::LeaveIfError(wg.CaptureKey(EKeyLeftArrow, 0, 0));

	// hide this window group from the app switcher
	wg.SetOrdinalPosition(-1);
	wg.EnableReceiptOfFocus(EFalse);
	CApaWindowGroupName* wn=CApaWindowGroupName::NewLC(ws);
	wn->SetHidden(ETrue);
	wn->SetWindowGroupName(wg);
	StartListening();
}

void CKeyListener::StartListening()
{
	// listen for the key presses
	ws.EventReady(&iStatus);
	SetActive();
}

void CKeyListener::RunL()
{
	User::WaitForAnyRequest();
	if (iStatus.Int()==KErrNone)
	{
			TWsEvent e;
			ws.GetEvent(e);

			TInt c;
			TKeyEvent* aKeyEvent=e.Key();
			c=aKeyEvent->iCode;

			iLog.WriteFormat(_L("KeyCode Received = %d"),c);
	}
	StartListening();
}

void CKeyListener::StopL()
{
	DoCancel();
}