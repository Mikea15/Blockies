#include "MainGame.h"
#include "IntroState.h"

int main(int argc, char *argv[])
{
	MainGame Game("Blockies");
	
	// initialize the engine
	if( Game.Init() == false )
	{
		cout << "[!] Window Created : " << WINWIDTH << "*" << WINHEIGHT << "@" << BPP << " - ERROR" << endl;
		return EXIT_FAILURE;
	}
	cout << "[ ] Window Created : " << WINWIDTH << "*" << WINHEIGHT << "@" << BPP << endl;

	// load the intro
	Game.ChangeState( IntroState::Instance() ); 

	// main loop
	while(Game.isRunning())
	{
		Game.OnEvent();

		Game.OnUpdate();

		Game.OnDraw();
	}
	
	// cleanup the engine
	Game.Cleanup();
	cout << "[ ] Cleanup Success" << endl;

	cout << "[ ] Exit Success" << endl;
	return EXIT_SUCCESS;
} 


