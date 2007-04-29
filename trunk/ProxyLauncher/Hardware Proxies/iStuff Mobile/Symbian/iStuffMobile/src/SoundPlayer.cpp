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