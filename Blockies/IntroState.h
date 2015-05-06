#ifndef _INTROSTATE_H_
#define _INTROSTATE_H_

#include "GameState.h"
#include "MenuState.h"

class IntroState : public GameState
{
	public:
		IntroState();
		~IntroState();

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(sf::RenderWindow &Window);

		static IntroState *Instance();

    private:
        static IntroState	mIntroState;

		sf::Image			mBgImage;
		sf::Sprite			mBgSprite;

		sf::Clock			mClock;

		int					i;
};


#endif
