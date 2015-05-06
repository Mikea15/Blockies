#ifndef _CREDITSTATE_H_
#define _CREDITSTATE_H_

#include "GameState.h"

class CreditState : public GameState
{
	public:
		CreditState();
		~CreditState();

		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void OnEvent(MainGame *Game, sf::Event Event);
		void OnUpdate(MainGame *Game);
		void Draw(sf::RenderWindow &Window);

		static CreditState *Instance();

    private:
        static CreditState	mCreditState;

	private:
		sf::Image			mBg;
		sf::Sprite			mSprite;

};


#endif

