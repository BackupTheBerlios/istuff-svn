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
#include "iStuffMobileAppUi.h"
#include "SoundPlayer.h"
#include "KeyListener.h"

class CiStuffMobileAppUi;

class CCodeListener : public CActive
{
	public:
		CCodeListener(CiStuffMobileAppUi* app);
		~CCodeListener();

		void ConstructL(CEikonEnv* aEikEnv);
		void ConnectToServer();
		void DisconnectFromServer();
		void SendKeyToProxy(TUint16 code,TUint16 aType);
		TBool GetConnected();

		RFileLogger iLog;
	
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

		CiStuffMobileAppUi* iApplicationUi;
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