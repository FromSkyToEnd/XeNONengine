/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

  Debugging code provided by
		Darren Reid

	-----------------------

	GameEngine.h

\*******************************************************/

#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include "Game.h"

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif

int main()
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	Game MyGame;

	MyGame.gameLoop();

	return 1;
}

#endif
