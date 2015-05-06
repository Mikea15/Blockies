#include "PlayState.h"

// Initialize mPlayState as Static Variable
PlayState PlayState::mPlayState;

PlayState::PlayState()
{
	
}

PlayState::~PlayState()
{
}

void PlayState::Init()
{
	// Init all Vars
	mLevelSpeed = 1.0f;
	mInitPosX = 6;
	mInitPosY = -2;

	mFontColor = sf::Color(0, 0, 0);
	mFontSize = 30.0f;
	mFontSizeScore = 20.0f;

	mName = "Player";
	mScorePosX = 550;
	mScorePosY = 270;
	mScore = 0;
	mScoreIncrement = 100;
	mLines = 0;
	mLevel = 0;
	mLinesToLevelUp = 10;
	mTimeToDecreaseLevelUp = 0.075f;

	mScoreColor = sf::Color(255, 255, 255);

	mEnterNamePosX = 215.0f;
	mEnterNamePosY = 215.0f;
	mEnterNameSize = 15.0f;

	mPausePosX = 5.0f;
	mPausePosY = 215.0f;
	mPauseSize = 35.0f;


	mPause = false;
	mMusicPause = false;
	mSfxPause = false;
	mNewGame = false;
	mEndGame = false;


	// fill board of emptiness.
	for( int i = 0; i < NBLOCKW; i++ )
		for( int j = 0; j < NBLOCKH; j++ )
			mGrid[i][j] = NONE;

	// --------------------------------------------------------------------
	// Loading Images, setting them as NOT smooth, and bind them to sprites
	// --------------------------------------------------------------------
	if( !mBgImages[NONE].LoadFromFile("Data\\gfx\\blackblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[NONE].SetSmooth(false);
	mBgSprites[NONE].SetImage(mBgImages[NONE]);
	mBgSprites[NONE].SetBlendMode(sf::Blend::Multiply);

	if( !mBgImages[YELLOW].LoadFromFile("Data\\gfx\\yellowblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[YELLOW].SetSmooth(false);
	mBgSprites[YELLOW].SetImage(mBgImages[YELLOW]);


	if( !mBgImages[BLUE].LoadFromFile("Data\\gfx\\blueblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[BLUE].SetSmooth(false);
	mBgSprites[BLUE].SetImage(mBgImages[BLUE]);


	if( !mBgImages[CYAN].LoadFromFile("Data\\gfx\\cyanblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[CYAN].SetSmooth(false);
	mBgSprites[CYAN].SetImage(mBgImages[CYAN]);


	if( !mBgImages[PINK].LoadFromFile("Data\\gfx\\pinkblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[PINK].SetSmooth(false);
	mBgSprites[PINK].SetImage(mBgImages[PINK]);


	if( !mBgImages[RED].LoadFromFile("Data\\gfx\\redblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[RED].SetSmooth(false);
	mBgSprites[RED].SetImage(mBgImages[RED]);


	if( !mBgImages[ORANGE].LoadFromFile("Data\\gfx\\orangeblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[ORANGE].SetSmooth(false);
	mBgSprites[ORANGE].SetImage(mBgImages[ORANGE]);


	if( !mBgImages[GREEN].LoadFromFile("Data\\gfx\\greenblock.jpg") )
	{
		// error
		std::cout << "[ ]";
	}
	mBgImages[GREEN].SetSmooth(false);
	mBgSprites[GREEN].SetImage(mBgImages[GREEN]);

	// --------------------------------------------------------------------
	// Loading Font AnimeAce2_Regular, set font, size, pos, color and text
	// --------------------------------------------------------------------

	if( !mFontType.LoadFromFile("Data\\fonts\\HoboStd.otf") )
	{
		//error
		std::cout << "[ ]";
	}	

	mStringScores.SetFont(mFontType);
	mStringScores.SetSize(mFontSizeScore);
	mStringScores.SetColor(mScoreColor);
	mStringScores.SetPosition(mScorePosX, mScorePosY);

	mEnterNameString.SetText("                  Game Over\n\nEnter Your Name, then Press Enter");
	mEnterNameString.SetFont(mFontType);
	mEnterNameString.SetPosition(mEnterNamePosX, mEnterNamePosY);
	mEnterNameString.SetColor(mFontColor);
	mEnterNameString.SetSize(mEnterNameSize);

	mPauseString.SetText("               Game Paused \n\n          Press 'P' to Resume");
	mPauseString.SetFont(mFontType);
	mPauseString.SetPosition(mPausePosX, mPausePosY);
	mPauseString.SetColor(mScoreColor);
	mPauseString.SetSize(mPauseSize);
	
	// --------------------------------------------------------------------
	// Loading SoundFx, and Sound Buffers
	// --------------------------------------------------------------------
	if( !mBufferRowDelete.LoadFromFile("Data\\sfx\\explosion1.wav"))
	{
		// error
		std::cout << "[ ]";
	}
	mSoundRowDelete.SetBuffer(mBufferRowDelete);


	if( !mBufferLevelUp.LoadFromFile("Data\\sfx\\pickup1.wav"))
	{
		// error
		std::cout << "[ ]";
	}
	mSoundLevelUp.SetBuffer(mBufferLevelUp);


	if( !mBufferHit.LoadFromFile("Data\\sfx\\hit2.wav"))
	{
		// error
		std::cout << "[ ]";
	}
	mSoundHit.SetBuffer(mBufferHit);


	// --------------------------------------------------------------------
	// Loading Music for game, loop on, and play
	// --------------------------------------------------------------------
	if( !mMusic.OpenFromFile("Data\\sfx\\tetristheme.wav") )
	{
		// error
		std::cout << "[ ]";
	}
	mMusic.SetLoop(true);
	mMusic.Play();


	// --------------------------------------------------------------------
	// Loading Image to make some gradient effect.
	// --------------------------------------------------------------------
	if( !mBg.LoadFromFile("Data\\gfx\\playscreen.jpg"))
	{
		// error
		std::cout << "[ ]";
	}
	mBgSprite.SetImage(mBg);

	// set timer to zero.
	mTimePlayed.Reset();

	// create new blocks and start playing.
	createNewBlocks();

	// loads scores to highscores vector.
	loadHighScores();
}

void PlayState::Cleanup()
{
	// we quit so we stop playing the music
	mMusic.Stop();
	mHighScores.clear();
}

void PlayState::Pause()
{
	mPause = true;
	if( !mMusicPause )
		mMusic.Pause();
}

void PlayState::Resume()
{
	mPause = false;
	if( !mMusicPause )
		mMusic.Play();
}

void PlayState::OnEvent(MainGame *Game, sf::Event Event)
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
					Game->PopState();
				break;

				/*
				case sf::Key::Left:
					if( !mPause )
						moveBlock(-1, 0);
				break;
				case sf::Key::Right:
					if( !mPause )
						moveBlock(1, 0);
				break;
				case sf::Key::Down:
					if( !mPause )
						moveBlock(0, 1);
				break;
				*/

				case sf::Key::Up:
					if( !mPause )
						rotateBlock();
				break;
				case sf::Key::O:
					if( !mPause )
					{
						if( mMusic.GetStatus() == sf::Sound::Status::Paused )
						{
							mMusic.Play();
							mMusicPause = false;
						}
						else
						{
							mMusic.Pause();
							mMusicPause = true;
						}
					}
				break;
				case sf::Key::I:
					if( !mPause )
					{
						if( mSfxPause == true )
							mSfxPause = false;
						else
							mSfxPause = true;
					}
				break;
				case sf::Key::P:
					if( mPause )
						Resume();
					else
						Pause();
				break;
				
				default: break;
			}
		break;
		default:break;
	}
}	

void PlayState::OnUpdate(MainGame *Game)
{
	if( !mPause )
	{
		if( mEndGame )
		{
			askNameInput(Game);
			saveToFile();
			Game->PopState();
			Game->PushState( HighScoreState::Instance() );
		}

		if( mClock.GetElapsedTime() >= mLevelSpeed )
		{
			moveBlock(0, 1);
			mClock.Reset();
		}

		// update time and score
		mTextScores.str("");
		mTextScores << mLevel << "\n\n\n\n" << mScore << "\n\n\n\n\n" << mLines << "\n\n\n\n\n" << (int) ( mTimePlayed.GetElapsedTime() ); 
		mStringScores.SetText(mTextScores.str());

		
		
		if( Game->mAppWindow.GetInput().IsKeyDown(sf::Key::Left) )
			moveBlock(-1, 0);
		if( Game->mAppWindow.GetInput().IsKeyDown(sf::Key::Right) )
			moveBlock(1, 0);
		if( Game->mAppWindow.GetInput().IsKeyDown(sf::Key::Down) )
			moveBlock(0, 1);
		


	}
}

void PlayState::Draw(sf::RenderWindow &Window)
{
	// cleans screen with one color.
	Window.Clear(sf::Color(23, 150, 198));

	Window.Draw(mBgSprite);

	// draw the map
	for( int i = 0; i < NBLOCKW; i++ )
	{
		for( int j = 0; j < NBLOCKH; j++ )
		{
			switch( mGrid[i][j] )
			{
				case NONE:		
					mBgSprites[NONE].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[NONE]); 
				break;
				case YELLOW:	
					mBgSprites[YELLOW].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[YELLOW]); 
				break;
				case BLUE:		
					mBgSprites[BLUE].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[BLUE]); 
				break;
				case CYAN:		
					mBgSprites[CYAN].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[CYAN]); 
				break;
				case PINK:
					mBgSprites[PINK].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[PINK]); 
				break;
				case RED:		
					mBgSprites[RED].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[RED]);
				break;
				case ORANGE:	
					mBgSprites[ORANGE].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[ORANGE]); 
				break;
				case GREEN:		
					mBgSprites[GREEN].SetPosition( (float) BLOCKSIZE * i, (float) BLOCKSIZE * j);
					Window.Draw(mBgSprites[GREEN]); 
				break;
				default: break;
			}
		}
	}

	// draw the next piece
	for( int i = 0; i < BGSIZE; i++ )
	{
		for( int j = 0; j < BGSIZE; j++ )
		{
			switch( mNextBlock.grid[i][j] )
			{
				case YELLOW:	
					mBgSprites[YELLOW].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[YELLOW]); 
				break;
				case BLUE:		
					mBgSprites[BLUE].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[BLUE]); 
				break;
				case CYAN:		
					mBgSprites[CYAN].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[CYAN]); 
				break;
				case PINK:
					mBgSprites[PINK].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[PINK]); 
				break;
				case RED:		
					mBgSprites[RED].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[RED]);
				break;
				case ORANGE:	
					mBgSprites[ORANGE].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[ORANGE]); 
				break;
				case GREEN:		
					mBgSprites[GREEN].SetPosition( (float) ( ( BLOCKSIZE * i ) + ( (WINWIDTH / 2) + 150 ) ), (float) ( ( BLOCKSIZE * j ) + 50 ) );
					Window.Draw(mBgSprites[GREEN]); 
				break;
				default: break;
			}
		}
	}
	
	// draw the pieces
	for( int i = 0; i < BGSIZE; i++ )
	{
		for( int j = 0; j < BGSIZE; j++ )
		{
			switch( mCurrentBlock.grid[i][j] )
			{
				case YELLOW:	
					mBgSprites[YELLOW].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[YELLOW]); 
				break;
				case BLUE:		
					mBgSprites[BLUE].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[BLUE]); 
				break;
				case CYAN:		
					mBgSprites[CYAN].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[CYAN]); 
				break;
				case PINK:
					mBgSprites[PINK].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[PINK]); 
				break;
				case RED:		
					mBgSprites[RED].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[RED]);
				break;
				case ORANGE:	
					mBgSprites[ORANGE].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[ORANGE]); 
				break;
				case GREEN:		
					mBgSprites[GREEN].SetPosition( (float) ( BLOCKSIZE * (i+mCurrentBlock.x) ), (float) ( BLOCKSIZE * (j+mCurrentBlock.y) ));
					Window.Draw(mBgSprites[GREEN]); 
				break;
				default: break;
			}
		}
	}

	// draw text
	Window.Draw(mStringScores);

	if( mPause ) 
	{
		Window.Draw(sf::Shape::Rectangle(0, 0, WINWIDTH, WINHEIGHT, sf::Color(250, 250, 250, 150)));
		Window.Draw(mPauseString);
	}

	Window.Display();
}




PlayState *PlayState::Instance()
{
    return &mPlayState;
}


void PlayState::createNewBlocks()
{
	// set current block to good position.
	mCurrentBlock.x = mInitPosX;
	mCurrentBlock.y = mInitPosY;

	if( !mNewGame ) // means new game.
	{
		mNewGame = true;
		std::cout << "[ ] New Game" << std::endl;

		// reset grid
		for( int i = 0; i < BGSIZE; i++ )
			for( int j = 0; j < BGSIZE; j++ )
				mCurrentBlock.grid[i][j] = NONE;

		switch( sf::Randomizer::Random(0, 6) )
		{
			case SQ:
				mCurrentBlock.grid[1][1] = YELLOW;
				mCurrentBlock.grid[2][1] = YELLOW;
				mCurrentBlock.grid[1][2] = YELLOW;
				mCurrentBlock.grid[2][2] = YELLOW;
			break;
			case I:
				mCurrentBlock.grid[1][0] = BLUE;
				mCurrentBlock.grid[1][1] = BLUE;
				mCurrentBlock.grid[1][2] = BLUE;
				mCurrentBlock.grid[1][3] = BLUE;
			break;
			case L:
				mCurrentBlock.grid[1][0] = CYAN;
				mCurrentBlock.grid[1][1] = CYAN;
				mCurrentBlock.grid[1][2] = CYAN;
				mCurrentBlock.grid[2][2] = CYAN;
			break;
			case LI:
				mCurrentBlock.grid[2][0] = PINK;
				mCurrentBlock.grid[2][1] = PINK;
				mCurrentBlock.grid[2][2] = PINK;
				mCurrentBlock.grid[1][2] = PINK;
			break;
			case N:
				mCurrentBlock.grid[1][0] = RED;
				mCurrentBlock.grid[1][1] = RED;
				mCurrentBlock.grid[2][1] = RED;
				mCurrentBlock.grid[2][2] = RED;
			break;
			case NI:
				mCurrentBlock.grid[2][0] = ORANGE;
				mCurrentBlock.grid[2][1] = ORANGE;
				mCurrentBlock.grid[1][1] = ORANGE;
				mCurrentBlock.grid[1][2] = ORANGE;
			break;
			case T:
				mCurrentBlock.grid[1][1] = GREEN;
				mCurrentBlock.grid[0][2] = GREEN;
				mCurrentBlock.grid[1][2] = GREEN;
				mCurrentBlock.grid[2][2] = GREEN;
			break;
			default: break;
		}
	}
	else
	{
		// reset grid
		for( int i = 0; i < BGSIZE; i++ )
			for( int j = 0; j < BGSIZE; j++ )
				mCurrentBlock.grid[i][j] = NONE;
		
		// create only block for the new one, and copy the old one.
		for( int i = 0; i < BGSIZE; i++ )
			for( int j = 0; j < BGSIZE; j++ )
				mCurrentBlock.grid[i][j] = mNextBlock.grid[i][j];
	}

	// reset grid
	for( int i = 0; i < BGSIZE; i++ )
		for( int j = 0; j < BGSIZE; j++ )
			mNextBlock.grid[i][j] = NONE;
	
	// randomly create new block.
	switch( sf::Randomizer::Random(0, 6) )
	{
		case SQ:
			mNextBlock.grid[1][1] = YELLOW;
			mNextBlock.grid[2][1] = YELLOW;
			mNextBlock.grid[1][2] = YELLOW;
			mNextBlock.grid[2][2] = YELLOW;
		break;
		case I:
			mNextBlock.grid[1][0] = BLUE;
			mNextBlock.grid[1][1] = BLUE;
			mNextBlock.grid[1][2] = BLUE;
			mNextBlock.grid[1][3] = BLUE;
		break;
		case L:
			mNextBlock.grid[1][0] = CYAN;
			mNextBlock.grid[1][1] = CYAN;
			mNextBlock.grid[1][2] = CYAN;
			mNextBlock.grid[2][2] = CYAN;
		break;
		case LI:
			mNextBlock.grid[2][0] = PINK;
			mNextBlock.grid[2][1] = PINK;
			mNextBlock.grid[2][2] = PINK;
			mNextBlock.grid[1][2] = PINK;
		break;
		case N:
			mNextBlock.grid[1][0] = RED;
			mNextBlock.grid[1][1] = RED;
			mNextBlock.grid[2][1] = RED;
			mNextBlock.grid[2][2] = RED;
		break;
		case NI:
			mNextBlock.grid[2][0] = ORANGE;
			mNextBlock.grid[2][1] = ORANGE;
			mNextBlock.grid[1][1] = ORANGE;
			mNextBlock.grid[1][2] = ORANGE;
		break;
		case T:
			mNextBlock.grid[1][1] = GREEN;
			mNextBlock.grid[0][2] = GREEN;
			mNextBlock.grid[1][2] = GREEN;
			mNextBlock.grid[2][2] = GREEN;
		break;
		default: break;
	}
}


void PlayState::moveBlock(int x, int y)
{
	if( collisionDetection(x, y) )
	{
		if( y == 1 )
		{
			if( mCurrentBlock.y < 1 )
			{
				// you lose, highScores Screen
				mEndGame = true;
				return;
			}
			else
			{
				copyPasteBlock();

				bool killblock = false;

				// check for filled row
				for( int j = 0; j < NBLOCKH; j++ ) 
				{
					bool filled = true;
					for( int i = 0; i < NBLOCKW; i++ )
						if( mGrid[i][j] == NONE )
							filled = false;

					if( filled ) {
						removeLine(j);
						killblock = true;
					}
				}

				if( killblock ) {
					for( int i = 0; i < BGSIZE; i++)
						for( int j = 0; j < BGSIZE; j++ )
							mCurrentBlock.grid[i][j] = NONE;
				}

				// the block has been put
				if( !mSfxPause )
					mSoundHit.Play();

				createNewBlocks();
				
			}
		}
	}
	else
	{
		// everything ok, update position.
		mCurrentBlock.x += x;
		mCurrentBlock.y += y;
	}
}

int PlayState::collisionDetection(int x, int y)
{
	int newX = mCurrentBlock.x + x;
	int newY = mCurrentBlock.y + y;

	// collision detection here
	for ( int i = 0; i < BGSIZE; i++ )
		for( int j = 0; j < BGSIZE; j++ )
			if( mCurrentBlock.grid[i][j] != NONE )
			{
				if( (newX+i) < 0 || (newX+i) > (NBLOCKW-1) )
					return 1;
				if( (newY+j) > (NBLOCKH-1) )
					return 1;
			}

	// collision detection with MAP
	for( int i = 0; i < NBLOCKW; i++ )
		for( int j = 0; j < NBLOCKH; j++ )
			if( ( i >= newX ) && ( i < ( newX + BGSIZE ) ) )
				if( ( j >= newY ) && ( j < ( newY + BGSIZE ) ) )
					if( mGrid[i][j] != NONE )
						if( mCurrentBlock.grid[i-newX][j-newY] != NONE )
							return 1;
	
	return 0;
}

void PlayState::copyPasteBlock()
{
	// we copy current block into the map and then create a new one! :D
	for ( int i = 0; i < BGSIZE; i++ )
	{
		for( int j = 0; j < BGSIZE; j++ )
		{
			if( mCurrentBlock.grid[i][j] != NONE )
			{
				mGrid[mCurrentBlock.x+i][mCurrentBlock.y+j] = mCurrentBlock.grid[i][j];
			}
		}
	}
}

void PlayState::rotateBlock()
{
	int temp[BGSIZE][BGSIZE];

	for( int i = 0; i < BGSIZE; i++ )
		for( int j = 0; j < BGSIZE; j++ )
			temp[(BGSIZE-1)-j][i]= mCurrentBlock.grid[i][j];

	int newX = mCurrentBlock.x;
	int newY = mCurrentBlock.y;

	// collision detection here
	for ( int i = 0; i < BGSIZE; i++ )
		for( int j = 0; j < BGSIZE; j++ )
			if( temp[i][j] != NONE )
			{
				if( (newX+i) < 0 || (newX+i) > (NBLOCKW-1) )
					return;
				if( (newY+j) > (NBLOCKH-1) || (newY+j) < 0 )
					return;
			}

	// collision detection with MAP
	for( int i = 0; i < NBLOCKW; i++ )
		for( int j = 0; j < NBLOCKH; j++ )
			if( ( i >= newX ) && ( i < ( newX + BGSIZE ) ) )
				if( ( j >= newY ) && ( j < ( newY + BGSIZE ) ) )
					if( mGrid[i][j] != NONE )
						if( temp[i-newX][j-newY] != NONE )
							return;

	for( int i = 0; i < BGSIZE; i++ )
		for( int j = 0; j < BGSIZE; j++ )
			mCurrentBlock.grid[i][j] = temp[i][j];
}

void PlayState::removeLine(int line)
{
	for( int i = 0; i < NBLOCKW; i++ )
		for( int j = line; j > 0; j-- )
			mGrid[i][j] = mGrid[i][j-1];
	
	// play sound for row destruction
	if( !mSfxPause )
		mSoundRowDelete.Play();

	updateScore();
}

void PlayState::updateScore()
{
	mLines++;
	mScore += mLines * mScoreIncrement / (mLevel+1);
	
	if( mLinesToLevelUp < 1 )
	{
		mLevel++;

		// play sound for level up! xD
		if( !mSfxPause )
			mSoundLevelUp.Play();

		mLinesToLevelUp = 10;
		
		if( mLevelSpeed < 0.10f )
			mLevelSpeed = 0.10f;
		else
			mLevelSpeed -= mTimeToDecreaseLevelUp;

	}
	else
	{
		mLinesToLevelUp--;
	}

}

void PlayState::saveToFile()
{
	// gather player info.
	PlayerInfo toWrite;
		toWrite.name  = mName;
		toWrite.level = mLevel;
		toWrite.lines = mLines;
		toWrite.score = mScore;
		toWrite.time  = (int) mTimePlayed.GetElapsedTime();

	mHighScores.push_back(toWrite); // put it on the vector at last pos. now has 11.

	// quicksort.
	for(unsigned int j = 0; j < (mHighScores.size()-1); j++ )
	{
		for(unsigned int i = 0; i < (mHighScores.size()-1); i++ )
		{
			PlayerInfo temp;

			if( mHighScores.at(i).score < mHighScores.at(i+1).score )
			{
				temp.name = mHighScores.at(i).name;
				temp.level = mHighScores.at(i).level;
				temp.lines = mHighScores.at(i).lines;
				temp.score = mHighScores.at(i).score;
				temp.time = mHighScores.at(i).time;

				mHighScores.at(i).name = mHighScores.at(i+1).name;
				mHighScores.at(i).level = mHighScores.at(i+1).level;
				mHighScores.at(i).lines = mHighScores.at(i+1).lines;
				mHighScores.at(i).score = mHighScores.at(i+1).score;
				mHighScores.at(i).time = mHighScores.at(i+1).time;

				mHighScores.at(i+1).name = temp.name;
				mHighScores.at(i+1).level = temp.level;
				mHighScores.at(i+1).lines = temp.lines;
				mHighScores.at(i+1).score = temp.score;
				mHighScores.at(i+1).time = temp.time;
			}
		}
	}

	// After sorting. we pop the last one.
	mHighScores.pop_back(); // remove the last position

	mWriteFile.open("Data\\hs.bks", fstream::out | fstream::trunc);
	//mWriteFile.seekp(0);

	if( mWriteFile )
	{
		std::cout << "[ Write ] Highscore file open." << std::endl;
		for(unsigned int i = 0; i < mHighScores.size(); i++ ) 
		{
			mWriteFile << mHighScores.at(i).name << " " 
					   << mHighScores.at(i).score << " "
					   << mHighScores.at(i).level << " " 
					   << mHighScores.at(i).lines << " " 
					   << mHighScores.at(i).time << "\n";
		}
		mWriteFile.close();
		std::cout << "[ Write ] Highscore file now closed." << std::endl;
	}
	else
		std::cerr << "[ Write ] Can't Open file" << std::endl;


	std::cout << "[ ] Everything Done, thanks!" << std::endl;
}

void PlayState::askNameInput(MainGame *Game)
{
	bool loopit = true;
	std::string temp;

	mNameString.SetPosition( 260, 260);
	
	while(loopit == true)
	{
		sf::Event Event;
		while (Game->mAppWindow.GetEvent(Event))
		{
			switch( Event.Type )
			{
				case sf::Event::TextEntered:
					if( Event.Text.Unicode == 8 )
					{
						if( temp.size() > 0 )
						{
							temp.erase( temp.size()-1, 1 );
							mNameString.SetText(temp);
							mName = temp;
						}
					}
					if( Event.Text.Unicode == 13 || Event.Text.Unicode == 27 )
					{
						loopit = false;
					}
					if( Event.Text.Unicode < 128 && Event.Text.Unicode != 8 )
					{
						temp += static_cast<char>(Event.Text.Unicode);
						mNameString.SetText(temp);
						mName = temp;
					}
				break;
				default: break;
			}
		}
		Game->mAppWindow.Draw(sf::Shape::Rectangle(200, 200, WINWIDTH-200, WINHEIGHT-200, sf::Color(20, 150, 250, 10), 5));

		Game->mAppWindow.Draw(mEnterNameString);

		Game->mAppWindow.Draw(mNameString);
		
		Game->mAppWindow.Display();
	}
	// testing
	mNameString.SetText("");
}

void PlayState::loadHighScores()
{
	// loads scores to highscores vector.
	mReadFile.open("Data\\hs.bks", ifstream::in);
	mReadFile.seekg(0);

	if( mReadFile )
	{
		std::cout << "[ Read ] Highscore file open." << std::endl;
		for(unsigned int i = 0; i < 10; i++ ) 
		{
			PlayerInfo temp;
			mReadFile >> temp.name >> temp.score >> temp.level >> temp.lines >> temp.time;
			mHighScores.push_back(temp);
		}		
		mReadFile.close();
		std::cout << "[ Read ] Highscore file now closed." << std::endl;
	}
	else
		std::cerr << "[ Read ] Can't Open file" << std::endl;
}