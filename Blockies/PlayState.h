#ifndef _PLAYSTATE_H_
#define _PLAYSTATE_H_

#include "GameState.h"

#include "HighScoreState.h"

class PlayState : public GameState
{
	public:
		PlayState();
		~PlayState();

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(sf::RenderWindow &Window);

		static PlayState *Instance();

		void createNewBlocks();
		void moveBlock( int x, int y );
		bool canMove();
		void copyPasteBlock();
		int  collisionDetection(int x, int y);
		void rotateBlock();
		void removeLine(int line);

		void updateScore();

		void saveToFile();
		void loadHighScores();

		void askNameInput(MainGame *Game);

    private:
        static PlayState	mPlayState;

	private:
		sf::Clock			mClock;

		int					mGrid[NBLOCKW][NBLOCKH];
		
		sf::Image			mBgImages[NBLOCKS];
		sf::Sprite			mBgSprites[NBLOCKS];

		Block				mCurrentBlock;
		Block				mNextBlock;

		bool				mNewGame;

		int					mInitPosX;
		int					mInitPosY;

		float				mLevelSpeed;

		sf::Font			mFontType;
		float				mFontSize;
		sf::Color			mFontColor;


		sf::Clock			mTimePlayed;
		std::string			mName;
		sf::String			mNameString;
		int					mScore;
		int					mScoreIncrement;
		int					mLines;
		int					mLevel;
		int					mLinesToLevelUp;
		float				mTimeToDecreaseLevelUp;
		float				mScorePosX;
		float				mScorePosY;
		std::stringstream	mTextScores;
		sf::String			mStringScores;
		sf::Color			mScoreColor;
		float				mFontSizeScore;

		sf::Image			mBg;
		sf::Sprite			mBgSprite;


		sf::SoundBuffer		mBufferRowDelete;
		sf::Sound			mSoundRowDelete;

		sf::SoundBuffer		mBufferLevelUp;
		sf::Sound			mSoundLevelUp;

		sf::SoundBuffer		mBufferHit;
		sf::Sound			mSoundHit;

		sf::Music			mMusic;

		bool				mSfxPause;
		bool				mMusicPause;

		bool				mEndGame;

		ifstream			mReadFile;
		ofstream			mWriteFile;

		std::vector<PlayerInfo>	mHighScores;

		sf::String			mEnterNameString;
		float				mEnterNamePosX;
		float				mEnterNamePosY;
		float				mEnterNameSize;

		sf::String			mPauseString;
		float				mPausePosX;
		float				mPausePosY;
		float				mPauseSize;

		bool				mPause;

};


#endif

