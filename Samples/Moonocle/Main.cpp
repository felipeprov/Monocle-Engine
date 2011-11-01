#include "Monocle.h"
#include "Pong.h"
#include "LuaBinder.h"
#include "MoonocleGameScene.h"



#include <iostream>
using namespace std;
using namespace Monocle;

int main(void)
{
	/* Declare a Lua State, open the Lua State and load the libraries (see above). */

	Game *game = new Game("Monocle with Lua",800,600);
	game->SetScene(new Moonocle::GameScene());
	game->Main();

	/* Remember to destroy the Lua State */
	delete game;

	return 0;
}
