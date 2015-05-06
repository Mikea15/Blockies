#ifndef _MAINGAME_H_
#define _MAINGAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class GameState;

using namespace std;

class MainGame
{
	public:
		MainGame(string title);
		
		bool Init();
        void Cleanup();
		void Quit();

        void ChangeState(GameState *newState);
        void PushState(GameState *newState);
        void PopState();

		int  OnExecute();
        void OnEvent();
        void OnUpdate();
        void OnDraw();

		bool isRunning();

	// need to be used on gamestate event, update and draw functions.
	public:
		sf::WindowSettings	mAppWindowSettings;
		sf::RenderWindow	mAppWindow;
		sf::Event			mAppEvent;
		sf::Clock			mAppClock;

	private:
		vector<GameState*>	mGameState;

		string				mWinName;

		bool				mAppRunning;
		int					mAppFrameRateLimit;
};


#endif
