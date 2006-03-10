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
iLog.Connect();
iLog.CreateLog(_L("iStuffMobile"),_L("CodeListener"),EFileLoggingModeOverwrite);
iLog.Write(_L("created"));
}

CCodeListener::~CCodeListener()
{
	Cancel();

	iLog.CloseLog();
	iLog.Close();
}

void CCodeListener::ConstructL(CEikonEnv* aEikEnv)
{
       iEikEnv = aEikEnv; // remember our environment
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

iLog.WriteFormat(_L("code =%d"),value);

	switch(value)
	{
		case OPCODE_DISCONNECT:
			DisconnectFromServer();
			break;

		case OPCODE_BACKLIGHT_ON:
			User::ResetInactivityTime();
			break;
		
		case OPCODE_KEY_RECEIVED:
			SendKeyToPhone();
			break;

		case OPCODE_PLAYSOUND:
			PlaySoundFile();
			break;
		
		case OPCODE_STOPSOUND:
			StopSoundFile();
			break;

		case OPCODE_LAUNCHAPP:
			LaunchApp();
			break;

		case OPCODE_CLOSEAPP:
			CloseApp();
			break;

		case OPCODE_START_KEYCAPTURE:
			StartKeyCapture();
			break;

		case OPCODE_STOP_KEYCAPTURE:
			StopKeyCapture();
			break;

		default:
			break;
	}
}

void CCodeListener::StartKeyCapture()
{
	iKeyListener = CKeyListener::NewL();
	iKeyListener->StartL();
}

void CCodeListener::StopKeyCapture()
{
	if(iKeyListener != NULL)
	{
		iKeyListener->StopL();
	}
}

void CCodeListener::LaunchApp()
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

	TPtrC Ptr(path);

	CApaCommandLine * cmd=CApaCommandLine::NewL();
    cmd->SetLibraryNameL(Ptr);
    cmd->SetCommandL(EApaCommandRun);
    EikDll::StartAppL(*cmd);

	cmd=CApaCommandLine::NewL();
    cmd->SetLibraryNameL(Ptr);
    cmd->SetCommandL(EApaCommandRun);
    EikDll::StartAppL(*cmd);
}

void CCodeListener::CloseApp()
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

	TPtrC Ptr(path);
	
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
				}
            }
        }
    }
}

void CCodeListener::SendKeyToPhone()
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

	TKeyEvent event;
	event.iRepeats = repeat;
	event.iScanCode = scancode;
	event.iCode = code;

	TApaTask task( CCoeEnv::Static()->WsSession() );
	task.SetWgId( CCoeEnv::Static()->WsSession().GetFocusWindowGroup() );
	
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

	TPtrC Ptr(path);
	iSoundPlayer = CSoundPlayer::NewL(Ptr);
}

void CCodeListener::StopSoundFile()
{
	if(iSoundPlayer != NULL)
		iSoundPlayer->Stop();
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
		User::InfoPrint(_L("Device already connected"));
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
		User::InfoPrint(_L("Device not connected"));
}

TBool CCodeListener::GetConnected()
{
	return isConnected;
}