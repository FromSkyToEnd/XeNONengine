#include "GameEngine.h"
#include <iostream>

void Game::Init()
{
  this->SetView("Test",200,200,200,200,true);
	Grump = this->NewSprite("Grump.png",0,0,121,147);
	Grump->SetPosition(50,50);
}

void Game::Input(sf::Event e)
{
	if(e.type == sf::Event::Closed || (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape))
	{
		this->Quit();
	}
}

void Game::Update(unsigned int time)
{
	Grump->Update(time);
	std::cout << (1/(float)time)*1000 << "              \r";
}

void Game::Draw(sf::RenderTarget &view)
{
	Grump->Draw(view);
}

void Game::Uninit()
{
	delete Grump;
}
