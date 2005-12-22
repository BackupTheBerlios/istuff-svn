#include "SoundPlayer.h"


CSoundPlayer* CSoundPlayer::NewL(const TDesC& aFile)
{
    CSoundPlayer* self = NewLC(aFile);
    CleanupStack::Pop(self);
    return self;
}

CSoundPlayer* CSoundPlayer::NewLC(const TDesC& aFile)
{
    CSoundPlayer* self = new (ELeave) CSoundPlayer();
    CleanupStack::PushL(self);
    self->ConstructL(aFile);
    return self;
}

CSoundPlayer::CSoundPlayer()
{

}

CSoundPlayer::~CSoundPlayer()
{
    delete iMdaPlayer;    
    iMdaPlayer = NULL;
}


void CSoundPlayer::ConstructL(const TDesC& aFile)
{
   iMdaPlayer = CMdaAudioPlayerUtility::NewFilePlayerL(aFile,*this);
}



void CSoundPlayer::Play()
{
   iState=EPlaying;
   iMdaPlayer->Play();
}


void CSoundPlayer::Stop()
{
   iMdaPlayer->Stop();
   iState = EReady;
}


void CSoundPlayer::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
{
   if(aError == KErrNone)
	   Play();
   else
	   Stop();
}


void CSoundPlayer::MapcPlayComplete(TInt aError)
{
    if(aError == KErrNone)
		iState = EReady;
	else
		iState = ENotReady;
}