/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	Game.cpp

\*******************************************************/

#include "Game.h"

/*******************************************************\

	Game::gameLoop()
		Main game loop where your input, update and draw methods get called
		additional stuff happens in order to facilitate things

	Arguments:
		void

	Return:
		void

\*******************************************************/
void Game::gameLoop()
{
	srand(time(NULL));
	QuitB=false;

	TexMan = new sfmlTextureManager("media/");

	Init();
	while(!QuitB)
	{
		sf::Event events;
		while(view.pollEvent(events))
		{
			Input(events);
		}
		ETime=FCLK.restart().asMilliseconds();//Time elasped
		Update(ETime);
		view.clear();
		Draw(view);
		view.display();
	}
	view.close();
	Uninit();

	delete TexMan;
}

/*******************************************************\

	Game::SetView()
		Initiates the view object of the game

	Arguments:
		std::string _Title
			Strings that holds the title of the window

		int Game_Width
		int Game_Height
			Size of the game view (This is NOT the window size,
			the game view will get resized to the window)
		
		int Window_Width
		int Window_Height
			Size of the window to create

		bool Fullscreen
			Triggers fullscreen

	Return:
		void

\*******************************************************/
void Game::SetView(std::string _Title,int Game_Width, int Game_Height, int Window_Width, int Window_Height, bool Fullscreen)
{
	GameSize=sf::Vector2i(Game_Width,Game_Height);
	Title=_Title;
	if(Fullscreen)
		view.create(sf::VideoMode(Window_Width,Window_Height),_Title,sf::Style::Fullscreen);
	else
		view.create(sf::VideoMode(Window_Width,Window_Height),_Title);
	view.setVerticalSyncEnabled(false);
	view.setKeyRepeatEnabled(false);
	ViewR.reset(sf::FloatRect(0,0,Game_Width,Game_Height));
	ViewR.setViewport(sf::FloatRect(0.f,0.f,1.f,1.f));
	view.setView(ViewR);
}

/*******************************************************\

	Game::SetView()
		resets the view and changes it's size or toggles fullscreen on or off

	Arguments:
		int Window_Width
		int Window_Height
			size of window to change to
		bool Fullscreen
			Triggers fullscreen

	Return:
		void

\*******************************************************/
void Game::SetView(int Window_Width,int Window_Height,bool Fullscreen)
{
	if(view.isOpen())
	{
		view.close();
	}
	if(Fullscreen)
		view.create(sf::VideoMode(Window_Width,Window_Height),Title,sf::Style::Fullscreen);
	else
		view.create(sf::VideoMode(Window_Width,Window_Height),Title);
	view.setVerticalSyncEnabled(true);
	view.setKeyRepeatEnabled(false);
	view.setView(ViewR);
}

/*******************************************************\

	Game::Quit()
		Enables you to quit the game gracefully

	Arguments:
		void

	Return:
		void

\*******************************************************/
void Game::Quit()
{
	QuitB=true;
}

/*******************************************************\

	Game::NewSprite()
		Creates a new sprite while using the sfmlTextureManager
		without hassle

	Arguments:
		std::string File
			File to load

		unsigned int left
		unsigned int top
			Top-left corner of the image to load from the file

		unsigned int width
		unsigned int height
			size of the image to load from the file

		bool anti_aliasing
			should anti_aliasing be applied to this sprite
			when transformation is applied

		bool origin_center
			should the origin of the sprite be centered?

		bool wrap
			should the texture be wrapped around incase
			you read outside of it

	Return:
		sSprite*
			Pointer to the newly created sprite for you
			to store

\*******************************************************/
sSprite* Game::NewSprite(std::string File,unsigned int left,unsigned int top,unsigned int width,unsigned int height,bool anti_aliasing,bool origin_center,bool wrap)
{
	sSprite* sprite = new sSprite(TexMan,File,sf::IntRect(left,top,width,height),anti_aliasing,origin_center,wrap);
	return sprite;
}

/*******************************************************\

	Game::NewSprite()
		Creates a new animated sprite while using the sfmlTextureManager
		without hassle

	Arguments:
		std::string File
			File to load

		unsigned int left
		unsigned int top
			Top-left corner of the image to load from the file

		unsigned int width
		unsigned int height
			size of the image to load from the file

		unsigned int frame_count_x
		unsigned int frame_count_y
			how many frames the animation will be

		unsigned int AnimationRate
			How fast should the animation go, in milliseconds

		bool anti_aliasing
			should anti_aliasing be applied to this sprite
			when transformation is applied

		bool origin_center
			should the origin of the sprite be centered?

		bool wrap
			should the texture be wrapped around incase
			you read outside of it

	Return:
		sSprite*
			Pointer to the newly created sprite for you
			to store

\*******************************************************/
aSprite* Game::NewSprite(std::string File, unsigned int left, unsigned int top, unsigned int width, unsigned int height, unsigned int frame_count_x, unsigned int frame_count_y, unsigned int AnimationRate, bool anti_aliasing, bool origin_center, bool wrap)
{
	aSprite* sprite = new aSprite(TexMan,File,sf::IntRect(left,top,width,height),frame_count_x,frame_count_y,AnimationRate,anti_aliasing,origin_center,wrap);
	return sprite;
}

/*******************************************************\

	Game::GetGameSize()
		Returns the size of the game view, not the window!

	Arguments:
		void

	Return:
		sf::Vectori
			size of game view

\*******************************************************/
sf::Vector2i Game::GetGameSize()
{
	return GameSize;
}

/*******************************************************\

	Game::GetWindowSize()
		Returns the size of the window

	Arguments:
		void

	Return:
		sf::Vector2u
			size of the view

\*******************************************************/
sf::Vector2u Game::GetWindowSize()
{
	return view.getSize();
}

/*******************************************************\

	Game::View()
		returns a pointer to the view object, should it
		ever be needed

	Arguments:
		void

	Return:
		sf::RenderWindow*
			pointer to the view object

\*******************************************************/
sf::RenderWindow* Game::View()
{
	return &view;
}
