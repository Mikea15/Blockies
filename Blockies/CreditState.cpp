#include "CreditState.h"

// Initialize mCreditState as Static Variable
CreditState CreditState::mCreditState;

CreditState::CreditState()
{
	
}

CreditState::~CreditState()
{
}

void CreditState::Init()
{
	if( !mBg.LoadFromFile("Data\\gfx\\aboutscreen.jpg"))
	{
		// error
	}

	mSprite.SetImage(mBg);
}

void CreditState::Cleanup()
{
	
}

void CreditState::Pause()
{
}

void CreditState::Resume()
{
}

void CreditState::OnEvent(MainGame *Game, sf::Event Event)
{
	switch(Event.Type)
	{
		case sf::Event::Closed:
			Game->PopState();
		break;
		case sf::Event::KeyPressed:
			switch(Event.Key.Code)
			{
				case sf::Key::Escape:
					Game->PopState(); // Soon to have Pause!
				break;
				default: break;
			}
		break;
		default: break;
	}
}	

void CreditState::OnUpdate(MainGame *Game)
{

}

void CreditState::Draw(sf::RenderWindow &Window)
{
	Window.Clear(sf::Color(250, 50, 150));

	Window.Draw(mSprite);

	Window.Display();
}


CreditState *CreditState::Instance()
{
    return &mCreditState;
}