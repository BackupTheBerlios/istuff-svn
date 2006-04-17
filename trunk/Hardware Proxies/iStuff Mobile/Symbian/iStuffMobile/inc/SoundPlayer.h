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

//!  CSoundPlayer class handles playback and stopping of a sound file.
/*!  CSoundPlayer class object is constructed when the opcode 
		 OPCODE_PLAYSOUND is received from the proxy. This class is
		 responsible for playback and stopping of a sound file.
*/
class CSoundPlayer: public CBase, public MMdaAudioPlayerCallback
{
	public:
		
		/** @name CSoundPlayer class first level constructors
		*   These methods create an object of CSoundPlayer class.
		
				\param aFile as TDesC type object. Represing the path
							 of the file to be played.

				\return CSoundPlayer object pointer.
		*/
		//@{
		static CSoundPlayer* NewL(const TDesC& aFile);
		static CSoundPlayer* NewLC(const TDesC& aFile);
		//@}
		
		~CSoundPlayer();

		//!  Starts playing the file
		/*!  This method sets the current state to EPlaying and 
				 starts the playback of the sound file.
		*/
		void Play();
		
		//!  Stops playing the file
		/*!  This method stops playing the sound file and sets 
				 the current state to EReady.
		*/
		void Stop();

    //!  Callback from the MMdaAudioPlayerCallback
		/*!  This method is invoked when the initialization of 
				 the sound player is completed.
				 
				 \param aError as TInt. Represents the status of
				 				completion.
				 \param aDuration as TTimeIntervalMicroSeconds object. Never used.
		*/
		void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
		
		//!  Callback from the MMdaAudioPlayerCallback
		/*!  This method is invoked when the playback of 
				 the sound file is completed.
				 
				 \param aError as TInt. Represents the status of
				 				completion. Can represent an Error if the
				 				playback was not successful.
		*/
		void MapcPlayComplete(TInt aError);


	private:
		CSoundPlayer();
		
		//!  CSoundPlayer class second level constructor
		/*!  This methods initializes iMdaPlayer class member.
		
				 \param aFile as TDesC type object. Represing the path
							 of the file to be played.
		*/
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