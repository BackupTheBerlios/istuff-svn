#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <e32base.h>
#include <flogger.h>
#include <w32std.h>
#include <apgwgnam.h>

class CKeyListener : public CActive
{
	public:
		static CKeyListener* NewLC();
		static CKeyListener* NewL();
		CKeyListener();
		~CKeyListener();

		void StartL();
		void StopL();

		RFileLogger iLog;

	private:
		void StartListening();
		void ConstructL();
		void RunL();
		void DoCancel();

		RWsSession ws;
};

#endif