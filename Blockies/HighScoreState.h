#ifndef _HSCORE_H_
#define _HSCORE_H_

#include "GameState.h"

class HighScoreState : public GameState
{
	public:
		HighScoreState();
		~HighScoreState();

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(sf::RenderWindow &Window);

		static HighScoreState *Instance();


		void loadFile();

    private:
        static HighScoreState	mHighScoreState;

	private:
		sf::Image						mBg;
		sf::Sprite						mBgSprite;

		bool							mLoaded;

		sf::Font						mFontType;

		float							mFontSize;
		sf::Color						mFontColor;
		float							mTextPosX;
		float							mTextPosY;

		float							mLineSpacing;

		ifstream						mReadFile;

		std::vector<sf::String>			mStrings;

};


#endif

