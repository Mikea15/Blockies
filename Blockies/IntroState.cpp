#include "IntroState.h"

// Initialize mIntroState as Static Variable
IntroState IntroState::mIntroState;

IntroState::IntroState()
{
	i = 255;
}

IntroState::~IntroState()
{
}

void IntroState::Init()
{
	// load background Image
	if (!mBgImage.LoadFromFile("Data\\gfx\\introscreen.jpg"))
	{
		// Error...
		cout << "[!] Wasn't able to load the blueBlock.jpg File" << endl;
	}

	// link background image to sprite
	mBgSprite.SetImage(mBgImage);

	mClock.Reset();
}

void IntroState::Cleanup()
{
}

void IntroState::Pause()
{
}

void IntroState::Resume()
{
}

void IntroState::OnEvent(MainGame *Game, sf::Event Event)
{
	switch(Event.Type)
	{
		case sf::Event::Closed:
			Game->Quit();
		break;
		case sf::Event::KeyPressed:
			switch(Event.Key.Code)
			{
				case sf::Key::Escape:
					Game->Quit();
				break;
				case sf::Key::Return:
					Game->ChangeState( MenuState::Instance() );
				break;
				default: break;
			}
		break;
		default: break;
	}
}

void IntroState::OnUpdate(MainGame *Game)
{
	if( mClock.GetElapsedTime() > 5.0f )
		Game->ChangeState( MenuState::Instance() );
}

void IntroState::Draw(sf::RenderWindow &Window)
{
	Window.Clear();

	Window.Draw(mBgSprite);
	if( i < 20 )
		i = 0;
	else
		i -= 10;

	Window.Draw(sf::Shape::Rectangle(0, 0, WINWIDTH, WINHEIGHT, sf::Color(0,0,0,i)));

	Window.Display();
}


IntroState *IntroState::Instance()
{
    return &mIntroState;
}
