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

class CMPToolkitAppUi;

class CCodeListener : public CActive
{
	public:
		CCodeListener(CMPToolkitAppUi* app);
		~CCodeListener();

		void ConstructL(CEikonEnv* aEikEnv);
		void ConnectToServer();
		void DisconnectFromServer();
		void SendKeyToProxy(TUint code);
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

		CMPToolkitAppUi* iApplicationUi;
		CEikonEnv* iEikEnv;

		TBuf8<1> data;
		RSocketServ iSocketServ;
		RSocket iSocket;

		RNotifier iDeviceSelector;
		TBTDeviceResponseParamsPckg iResponse;
		TBool isConnected;

		CSoundPlayer* iSoundPlayer;
		CDesCArrayFlat*	iAppList;
};

#endif