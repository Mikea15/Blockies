#include "MenuState.h"

// Initialize mMenuState as Static Variable
MenuState MenuState::mMenuState;

MenuState::MenuState()
{
	
}

MenuState::~MenuState()
{
	
}

void MenuState::Init()
{
	mMenuPosX = WINWIDTH - 200;
	mMenuPosY = WINHEIGHT - 240;
	mMenuLineMargin = 40.0f;
	mMenuFontSize = 30.0f;

	mMenu.loadFont( "Data\\fonts\\HoboStd.otf" );
	mMenu.loadFontSize( mMenuFontSize );

	mMenu.setMenuColor( 250, 250, 250 );
	mMenu.setMenuColorSelected( 138, 196, 233 );

	mMenu.addString("Play");
	mMenu.addString("Hall of Fame");
	mMenu.addString("About");
	mMenu.addString("Quit");

	// set mMenu to position and push down next item, plus
	// a little random treat to make game more fun! xD
	for( int i = 0; i < mMenu.getMenuSize(); i++ )
	{
		mMenu.setPosition(i, mMenuPosX, mMenuPosY );
		mMenuPosY += mMenuLineMargin;
	}	

	if( !mBgImg.LoadFromFile("Data\\gfx\\menuscreen.jpg")) 
	{
		// error
	}

	mBgSprite.SetImage(mBgImg);
}

void MenuState::Cleanup()
{
	mMenu.cleanMenu();
	cout << "[ ] Menu Cleaned Up" << endl;
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::OnEvent(MainGame *Game, sf::Event Event)
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
					// Select Last
					mMenu.goLast();
				break;
				case sf::Key::Up:
					mMenu.goUp();
				break;
				case sf::Key::Down:
					mMenu.goDown();
				break;
				case sf::Key::Return:
					switch( mMenu.getSelectedItem() )
					{
						case 0:
							// playState
							Game->PushState( PlayState::Instance() );
						break;
						case 1:
							Game->PushState( HighScoreState::Instance() );
						break;
						case 2:
							// creditState
							Game->PushState( CreditState::Instance() );
						break;
						case 3:
							// quit
							Game->Quit();
						break;
						default: break;
					}
				break;
				default: break;
			}
		break;
		default: break;
	}
}	

void MenuState::OnUpdate(MainGame *Game)
{

}

void MenuState::Draw(sf::RenderWindow &Window)
{
	Window.Clear(sf::Color(50, 50, 150));

	Window.Draw(mBgSprite);

	// now, we draw our menu.
	for( int i = 0 ; i < mMenu.getMenuSize(); i++ )
	{
		if( i == mMenu.getSelectedItem() )
			mMenu.isSelected(i);
		else
			mMenu.isNotSelected(i);

		Window.Draw( mMenu.draw(i) );
	}

	Window.Display();
}


MenuState *MenuState::Instance()
{
    return &mMenuState;
}