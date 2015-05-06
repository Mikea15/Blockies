#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "MainGame.h"

class GameState
{
	public:
		virtual void Init();
		virtual void Cleanup();

		virtual void Pause();
		virtual void Resume();

		virtual void OnEvent(MainGame *Game, sf::Event Event);
		virtual void OnUpdate(MainGame *Game);
		virtual void Draw(sf::RenderWindow &Window);

		void ChangeState(MainGame Game, GameState *newState);

	protected: // only child/parent can use.
		GameState();
};


#endif
