#include "HighScoreState.h"

// Initialize mHighScoreState as Static Variable
HighScoreState HighScoreState::mHighScoreState;

HighScoreState::HighScoreState()
{
	
}

HighScoreState::~HighScoreState()
{
}

void HighScoreState::Init()
{
	mFontSize = 15.0f;
	mFontColor = sf::Color(50, 100, 250);
	mTextPosX = 50.0f;
	mTextPosY = 100.0f;

	mLineSpacing = 40.0f;

	if( !mFontType.LoadFromFile("Data\\fonts\\animeace2_reg.ttf") )
	{
		// error
	}

	loadFile();

	for(unsigned int i = 0; i < mStrings.size(); i++ )
	{
		mStrings.at(i).SetFont(mFontType);
		mStrings.at(i).SetColor(mFontColor);
		mStrings.at(i).SetSize(mFontSize);
		mStrings.at(i).SetPosition(mTextPosX, mTextPosY);

		// update pos for next text
		mTextPosY += mLineSpacing;
	}

	if( !mBg.LoadFromFile("Data\\gfx\\halloffame.jpg"))
	{
		// error
	}
	mBgSprite.SetImage(mBg);

}

void HighScoreState::Cleanup()
{
	mStrings.clear();
}

void HighScoreState::Pause()
{
}

void HighScoreState::Resume()
{
}

void HighScoreState::OnEvent(MainGame *Game, sf::Event Event)
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

void HighScoreState::OnUpdate(MainGame *Game)
{

}

void HighScoreState::Draw(sf::RenderWindow &Window)
{
	Window.Clear(sf::Color(250, 250, 250));

	Window.Draw(mBgSprite);

	for(unsigned int i = 0; i < mStrings.size(); i++ )
	{
		Window.Draw( mStrings.at(i) );
	}

	Window.Display();
}


HighScoreState *HighScoreState::Instance()
{
    return &mHighScoreState;
}

void HighScoreState::loadFile()
{
	mReadFile.open("Data\\hs.bks", ios::in);
	mReadFile.seekg(0);
	

	if( mReadFile )
	{
		std::cout << "[ Read ] Highscore file open." << std::endl;
		for(unsigned int i = 0; i < 10; i++ ) 
		{
			PlayerInfo temp;
			mReadFile >> temp.name >> temp.score >> temp.level >> temp.lines >> temp.time;

			std::stringstream tempStream;
			tempStream << "Playername: " << temp.name 
					   << "   Score: " << temp.score
					   << "   Lines: " << temp.lines
					   << "   Level: " << temp.level
					   << "   Time: " << temp.time;

			sf::String tempString(tempStream.str());
			mStrings.push_back(tempString);
		}		
		mReadFile.close();
		std::cout << "[ Read ] Highscore file now closed." << std::endl;
	}
	else
		std::cerr << "[ Read ] Can't Open file" << std::endl;
}

