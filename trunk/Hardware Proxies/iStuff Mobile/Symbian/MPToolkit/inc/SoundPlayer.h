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

	private:
		enum TState
		{
			ENotReady,
			EReady,
			EPlaying
		};
    
		TState iState;
		CMdaAudioPlayerUtility* iMdaPlayer;
};