#ifndef CODELISTENER_H
#define CODELISTENER_H

#include <es_sock.h>
#include <in_sock.h>
#include <BTExtNotifiers.h>
#include <bt_sock.h>
#include <flogger.h>
#include <apacmdln.h>
#include <EikDll.h>
#include <apgcli.h>

#include "Global.h"
#include "MPToolkitAppUi.h"
#include "SoundPlayer.h"
#include "KeyListener.h"

class CMPToolkitAppUi;

class CCodeListener : public CActive
{
	public:
		CCodeListener(CMPToolkitAppUi* app);
		~CCodeListener();

		void ConstructL(CEikonEnv* aEikEnv);
		void ConnectToServer();
		void DisconnectFromServer();
		void SendKeyToProxy(TUint16 code,TUint16 aType);
		TBool GetConnected();

	//	RFileLogger iLog;
	
	private:
		void StartReceiving();
		void DecodeOpcode();

		virtual void DoCancel(); // how to cancel me
		virtual void RunL();

		void SendKeyToPhone();
		void PlaySoundFile();
		void StopSoundFile();
		void LaunchApp();
		void CloseApp();
		void StartKeyCapture();
		void StopKeyCapture();

		CMPToolkitAppUi* iApplicationUi;
		CEikonEnv* iEikEnv;

		TBuf8<1> data;
		RSocketServ iSocketServ;
		RSocket iSocket;

		RNotifier iDeviceSelector;
		TBTDeviceResponseParamsPckg iResponse;
		TBool isConnected;

		CSoundPlayer* iSoundPlayer;
		CKeyListener* iKeyListener;
		CDesCArrayFlat*	iAppList;
};

#endif