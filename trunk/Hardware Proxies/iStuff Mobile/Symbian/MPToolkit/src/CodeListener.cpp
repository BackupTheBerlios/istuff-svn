
#include "CodeListener.h"

CCodeListener::CCodeListener(CMPToolkitAppUi* app) : CActive(0)
{
	iApplicationUi = app;
	isConnected = EFalse;
//iLog.Connect();
//iLog.CreateLog(_L("MPToolkit"),_L("MyLogFile1"),EFileLoggingModeOverwrite);
//iLog.Write(_L("created"));
}

CCodeListener::~CCodeListener()
{
	Cancel();

//	iLog.CloseLog();
//	iLog.Close();
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
	iKeyListener = CKeyListener::NewLC();
	iKeyListener->StartL();
}

void CCodeListener::StopKeyCapture()
{
	if(iKeyListener != NULL)
		iKeyListener->StopL();
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