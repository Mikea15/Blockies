#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_

#include "GameState.h"
#include "Menu.h"

#include "PlayState.h"
#include "CreditState.h"
#include "HighScoreState.h"

class MenuState : public GameState
{
	public:
		MenuState();
		~MenuState();

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(sf::RenderWindow &Window);

		static MenuState *Instance();

    private:
        static MenuState	mMenuState;

	private:
		sf::Image			mBgImg;
		sf::Sprite			mBgSprite;

		Menu				mMenu;
		float				mMenuPosX;
		float				mMenuPosY;
		float				mMenuLineMargin;
		float				mMenuFontSize;
};


#endif

