#include "MainGame.h"
#include "GameState.h"

MainGame::MainGame(string title)
{
	mWinName = title;
	mAppRunning = true;
	mAppFrameRateLimit = 12;
}
// Initializes the Window
bool MainGame::Init()
{
	
	mAppWindowSettings.DepthBits         = 0; // Request a 24 bits depth buffer
	mAppWindowSettings.StencilBits       = 0;  // Request a 8 bits stencil buffer
	mAppWindowSettings.AntialiasingLevel = 0;  // Request 2 levels of antialiasing

	mAppWindow.Create(sf::VideoMode(WINWIDTH, WINHEIGHT, BPP), mWinName, sf::Style::Close, mAppWindowSettings);
	mAppWindow.SetFramerateLimit(mAppFrameRateLimit);
	
	return true;
}

void MainGame::Cleanup()
{
	cout << "[ ] Entering Cleanup" << endl;
}

void MainGame::ChangeState(GameState *newState)
{ 
	// cleans current state first
	if( !mGameState.empty() )
	{
		mGameState.back()->Cleanup();
		mGameState.pop_back();
	}

	// then add out new state
	mGameState.push_back(newState);
	mGameState.back()->Init(); // and start it
}


void MainGame::PushState(GameState *newState)
{
	// if we want to pause a state
	// or if we want to kill the state.
	if( !mGameState.empty() )
	{
		mGameState.back()->Pause();
	}

	// add new state in back of the line
	// and start it.
	mGameState.push_back(newState);
	mGameState.back()->Init();
}

void MainGame::PopState()
{
	// clean the current state
	// and removes it.
	if( !mGameState.empty() )
	{
		mGameState.back()->Cleanup();
		mGameState.pop_back();
	}
	
	// after cleanup and deletion if there
	// are still other states then
	// resume it.
	if( !mGameState.empty() )
	{
		mGameState.back()->Resume();
	}
}

void MainGame::Quit()
{
	mAppRunning = false;
}


void MainGame::OnEvent()
{
	while( mAppWindow.GetEvent(mAppEvent) )
	{
		mGameState.back()->OnEvent(this, mAppEvent);
	}
}

void MainGame::OnUpdate()
{
	mGameState.back()->OnUpdate(this);
}

void MainGame::OnDraw()
{
	mGameState.back()->Draw(mAppWindow);
}

bool MainGame::isRunning()
{
	return mAppRunning;
}

