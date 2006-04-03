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

#include "CodeListener.h"

CCodeListener::CCodeListener(CiStuffMobileAppUi* app) : CActive(0)
{
	iApplicationUi = app;
	isConnected = EFalse;
}

CCodeListener::~CCodeListener()
{
	Cancel();
}

void CCodeListener::ConstructL(RFileLogger* aLog)
{
       iLog = aLog;
       CActiveScheduler::Add(this); // add to scheduler
}

void CCodeListener::StartReceiving()
{
	iSocket.Read(data,iStatus);
	SetActive();
}

void CCodeListener::RunL()
{
	if (iStatus.Int() != KErrNone)
	{
		iLog->WriteFormat(_L("Error %d while reading OPCODE"),iStatus.Int());
		DisconnectFromServer();
	}

	DecodeOpcode();
	StartReceiving();
}

void CCodeListener::DoCancel()
{
	iSocket.CancelAll();
}

void CCodeListener::DecodeOpcode()
{
	TUint8 value = data[0];

	switch(value)
	{
		case OPCODE_DISCONNECT:
			DisconnectFromServer();
			break;

		case OPCODE_BACKLIGHT_ON:
			User::ResetInactivityTime();
			break;
		
		case OPCODE_KEY_RECEIVED:
			DecodeReceivedKey();
			break;

		case OPCODE_PLAYSOUND:
			PlaySoundFile();
			break;
		
		case OPCODE_STOPSOUND:
			StopSoundFile();
			break;

		case OPCODE_LAUNCHAPP:
			LaunchApp(GetPath());
			break;

		case OPCODE_CLOSEAPP:
			CloseApp(GetPath());
			break;

		case OPCODE_START_KEYCAPTURE:
			StartKeyCapture();
			break;

		case OPCODE_STOP_KEYCAPTURE:
			StopKeyCapture();
			break;

		case OPCODE_CHANGEPROFILE:
			ChangeProfile();
			break;

		default:
			iLog->WriteFormat(_L("Unrecognized Code %d"),value);
			break;
	}
}

void CCodeListener::StartKeyCapture()
{
	if(iKeyListener == NULL)
	{
		iKeyListener = CKeyListener::NewL();
		iKeyListener->ConstructL(this,iLog);
		iKeyListener->StartL();
	}
	else
	{
		iLog->Write(_L("Key capture is already running"));
	}
}

void CCodeListener::StopKeyCapture()
{
	if(iKeyListener != NULL)
	{
		iKeyListener->StopL();
		delete iKeyListener;

		iKeyListener = NULL;
	}
	else
	{
		iLog->Write(_L("Key capture is not running"));
	}
}

void CCodeListener::LaunchApp(TUint16* path)
{
	TInt error = 0;
	TPtrC Ptr(path);

	CApaCommandLine * cmd=CApaCommandLine::NewL();
    cmd->SetLibraryNameL(Ptr);
    cmd->SetCommandL(EApaCommandRun);
    TRAP(error, EikDll::StartAppL(*cmd));

	if(error != KErrNone) 
	{
		iLog->WriteFormat(_L("Application \"%s\" could not be launched"),path);
	}
}

void CCodeListener::CloseApp(TUint16* path)
{
	TPtrC Ptr(path);
	TBool killed = EFalse;
	
	RApaLsSession RSession;
    TInt AAppCount = 0;//get the number of applications
    RSession.Connect();       
    RSession.AppCount(AAppCount);//number of tasks
       
    iAppList = new (ELeave) CDesCArrayFlat(AAppCount);
    RSession.GetAllApps();//get all the tasks in the RApaLsSession obj
   
    if(AAppCount > 0)
	{
        //if the task is present get info about it in AppInfo
        TApaAppInfo AppInfo;
        TApaTaskList aList(CEikonEnv::Static()->WsSession());

        for(TInt i=0;i<AAppCount;i++)
		{
            RSession.GetNextApp(AppInfo);
            TApaTask ATask3 = aList.FindApp(AppInfo.iUid);
            if(ATask3.Exists())
            {
				if(AppInfo.iCaption.Find(Ptr) != KErrNotFound)
				{
					ATask3.KillTask();
					killed = ETrue;
					break;
				}
            }
        }
    }

	if(!killed)
		iLog->WriteFormat(_L("Application \"%s\" was not found"),path);
}

void CCodeListener::DecodeReceivedKey()
{
	TRequestStatus iLocalStatus;
	TBuf8<6> localData;
	
	iSocket.Read(localData,iLocalStatus);
	User::WaitForRequest(iLocalStatus);

	TUint16 repeat = 0;
	repeat |= localData[0];
	repeat <<= 8;
	repeat |= localData[1];

	TUint16 scancode = 0;
	scancode |= localData[2];
	scancode <<= 8;
	scancode |= localData[3];

	TUint16 code = 0;
	code |= localData[4];
	code <<= 8;
	code |= localData[5];

	SendKeyToPhone(repeat,scancode,code);
}

void CCodeListener::SendKeyToPhone(TUint16 repeat, TUint16 scancode, TUint16 code)
{
	TKeyEvent event;
	event.iRepeats = repeat;
	event.iScanCode = scancode;
	event.iCode = code;

	TApaTask task(CCoeEnv::Static()->WsSession());
	task.SetWgId(CCoeEnv::Static()->WsSession().GetFocusWindowGroup());
	
	User::ResetInactivityTime();
	task.SendKey(event);
}

void CCodeListener::SendKeyToProxy(TUint16 code,TUint16 aType)
{
	TRequestStatus iLocalStatus;
	TBuf8<5> localData;
	localData.Append(OPCODE_KEY_PRESSED);
	localData.Append(code >> 8);
	localData.Append(code);
	localData.Append(aType >> 8);
	localData.Append(aType);

	iSocket.Write(localData,iLocalStatus);
	User::WaitForRequest(iLocalStatus);
}

void CCodeListener::PlaySoundFile()
{
	if(iSoundPlayer == NULL)
	{
		TPtrC Ptr(GetPath());
		iSoundPlayer = CSoundPlayer::NewL(Ptr);
	}
	else
	{
		iLog->Write(_L("Sound Player is already running"));
	}
}

void CCodeListener::StopSoundFile()
{
	if(iSoundPlayer != NULL)
	{
		iSoundPlayer->Stop();
		delete iSoundPlayer;
		
		iSoundPlayer = NULL;
	}
	else
	{
		iLog->Write(_L("Sound Player is not running"));
	}
}

void CCodeListener::ChangeProfile()
{
	TRequestStatus iLocalStatus;
	TBuf8<1> localData;

	iSocket.Read(localData,iLocalStatus);
	User::WaitForRequest(iLocalStatus);

	iProfileNo = localData[0];

	TBufC16<41> temp = _L("Z:\\System\\Apps\\ProfileApp\\ProfileApp.app");

	TUint16 * launchApp = (TUint16 *)temp.Ptr();
	launchApp[40] = 0;

	LaunchApp(launchApp);

	iPeriodic = CPeriodic::NewL(CActive::EPriorityLow);
    iPeriodic->Start(1000000,1000000,TCallBack(ContinueChangeProfile,this));
}


TInt CCodeListener::ContinueChangeProfile(TAny* aObject)
{

	CCodeListener* self = (CCodeListener*) aObject;
	TUint8 profileNo = self->iProfileNo;

	for(TInt i=0; i<profileNo-1; i++)
	{
		self->SendKeyToPhone(0,0,EKeyDownArrow);
	}
	
	for(TInt i=0; i<2; i++)
	{
		self->SendKeyToPhone(0,0,63557);
		User::After(1000000);
	}
	
	TBufC16<9> temp = _L("Profiles");

	TUint16 * closeApp = (TUint16 *)temp.Ptr();
	closeApp[8] = 0;

	User::After(1000000);
	self->CloseApp(closeApp);
	
	self->iPeriodic->Cancel();
	delete self->iPeriodic;
	self->iPeriodic = NULL;

	return 0;
}


TUint16* CCodeListener::GetPath()
{
	TRequestStatus iLocalStatus;
	TBuf8<1> localData;

	iSocket.Read(localData,iLocalStatus);
	User::WaitForRequest(iLocalStatus);

	TUint8 pathSize = localData[0];
	TUint16 *path = new TUint16[pathSize];

	for(TInt i=0;i<pathSize;i++)
	{
		iSocket.Read(localData,iLocalStatus);
		User::WaitForRequest(iLocalStatus);
		path[i] = localData[0];
	}

	return path;
}

void CCodeListener::ConnectToServer()
{
	if(!isConnected)
	{
		TRequestStatus iLocalStatus;
		
		User::LeaveIfError(iSocketServ.Connect());
		User::LeaveIfError(iSocket.Open(iSocketServ, _L("RFCOMM")));

		User::LeaveIfError(iDeviceSelector.Connect());
		TBTDeviceSelectionParamsPckg selectionFilter;
		TUUID serviceClass(0x1101); // SerialPort, uuid16: 0x1101, 
									// see Bluetooth_11_Assigned_Numbers.pdf,
									// 4.4 Service Classes
		selectionFilter().SetUUID(serviceClass);
		iDeviceSelector.StartNotifierAndGetResponse(iLocalStatus, KDeviceSelectionNotifierUid, selectionFilter, iResponse);
		User::WaitForRequest(iLocalStatus);

		if (iLocalStatus.Int() != KErrNone || !iResponse().IsValidBDAddr()) 
			User::Leave(KErrCouldNotConnect);

		TBTSockAddr address;
		address.SetBTAddr(iResponse().BDAddr());
		address.SetPort(1);

		iSocket.Connect(address, iLocalStatus);
		User::WaitForRequest(iLocalStatus);

		iDeviceSelector.CancelNotifier(KDeviceSelectionNotifierUid);
		iDeviceSelector.Close();

		isConnected = ETrue;
		iApplicationUi->SetConnected(ETrue);
		StartReceiving();
	}
	else
	{
		iLog->Write(_L("The device is already connected"));
	}
}

void CCodeListener::DisconnectFromServer()
{
	if(isConnected)
	{
		Cancel();
		
		TRequestStatus iLocalStatus;
		
		iSocket.Shutdown(RSocket::ENormal, iLocalStatus);
		User::WaitForRequest(iLocalStatus);
		iSocket.Close();
		iSocketServ.Close();
		
		isConnected = EFalse;
		iApplicationUi->SetConnected(EFalse);
	}
	else
	{
		iLog->Write(_L("The device is not connected"));
	}
}

TBool CCodeListener::GetConnected()
{
	return isConnected;
}