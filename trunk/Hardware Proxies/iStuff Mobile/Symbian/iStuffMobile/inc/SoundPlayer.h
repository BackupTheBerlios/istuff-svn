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

#include <MdaAudioSamplePlayer.h>

class CSoundPlayer: public CBase, public MMdaAudioPlayerCallback
{
	public:
		static CSoundPlayer* NewL(const TDesC& aFile);
		static CSoundPlayer* NewLC(const TDesC& aFile);
		~CSoundPlayer();

		void Play();
		void Stop();

    
		void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
		void MapcPlayComplete(TInt aError);


	private:
		CSoundPlayer();
		void ConstructL(const TDesC& aFile);

		enum TState
		{
			ENotReady,
			EReady,
			EPlaying
		};
    
		TState iState;
		CMdaAudioPlayerUtility* iMdaPlayer;
};