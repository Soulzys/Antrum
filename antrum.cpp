#include "antrum.h"

/*
	Parameters
		@ GameMemory*		memory
		@ GameState*		gameState
		@ PlatformStorage*	platformStorage

*/
extern "C" GAME_UPDATE(Game_Update)
{
	if (!gameState->initialized)
	{


		gameState->initialized = true;
	}


	if (gameState->quit)
	{
		int a = 2;
	}
}