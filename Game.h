/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	Game.h

\*******************************************************/

#ifndef __SFML_GAME_CLASS_H__
#define __SFML_GAME_CLASS_H__

#include "SpriteWrapper.h"
#include <string>

class Game
{
private:
	sf::VideoMode windSet;
	sf::RenderWindow view;
	sf::View ViewR;
	sf::Clock FCLK;
	sf::Vector2i GameSize;
	std::string Title;

	///Enables us to quit from the game loop
	bool QuitB;
	///Stores elasped time between frames
	unsigned int ETime;
	///Texture manager that takes care of storing textures and preventing redundancy
	sfmlTextureManager *TexMan;

	//*** Game components ***\\
	Put the variables your game will use here					\
	We'll put them here instead of making variables global		

	sSprite *Grump;

	//\\*******************//\\

public:
	//Functions//
	///Initiates the window
	void SetView(std::string Title,int Game_Width, int Game_Height, int Window_Width, int Window_Height, bool Fullscreen);
	///Resizes the view by code
	void SetView(int Window_Width,int Window_Height,bool Fullscreen);
	///Quit and close the game
	void Quit();
	///Get game size (Not window size)
	sf::Vector2i GetGameSize();
	///Get window size
	sf::Vector2u GetWindowSize();
	///Get view pointer
	///Used for drawing
	sf::RenderWindow* View();
	///Create a new standard sprite
	sSprite* NewSprite(	std::string File,
						unsigned int left,
						unsigned int top,
						unsigned int width,
						unsigned int height,
						bool anti_aliasing=true,
						bool origin_center=true,
						bool wrap=true);
	///Create a new animated sprite
	aSprite* NewSprite(	std::string File,
						unsigned int left,
						unsigned int top,
						unsigned int width,
						unsigned int height,
						unsigned int frame_count_x,
						unsigned int frame_count_y,
						unsigned int AnimationRate,
						bool anti_aliasing=true,
						bool origin_center=true,
						bool wrap=true);


	//Game loop functions//
	///Call this to initiate the game
	void gameLoop();

	///Initiate variables
	void Init();
	///clear up memory
	void Uninit();
	///Take care of event-based input
	void Input(sf::Event e);
	///Take care of updates
	void Update(unsigned int time);
	///Take care of drawing objects
	void Draw(sf::RenderTarget& view);
};

#endif		
