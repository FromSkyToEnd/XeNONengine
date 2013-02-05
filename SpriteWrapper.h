/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	SpriteWrapper.h

\*******************************************************/

#ifndef __SFML_SPRITE_WRAPPER_CLASS_H__
#define __SFML_SPRITE_WRAPPER_CLASS_H__

#include "sfmlTextureManager.h"
#include <sstream>
#include <stdio.h>
#include <stdarg.h>

class sSprite
{
private:
	sf::Sprite Sprt;
	sf::Vector2f velocity;
	sfmlTextureManager *TexMan;
	std::string file;
public:
	sSprite(	sfmlTextureManager *TM,
				std::string File,
				sf::IntRect SubRect,
				bool anti_aliasing=true,
				bool origin_center=true,
				bool wrap=true);
	~sSprite();

	virtual void Draw(sf::RenderTarget &view);
	virtual void Draw(sf::RenderTarget &view,sf::RenderStates &Rend);
	virtual void Update(unsigned int time);

	std::string GetFile();
	sfmlTextureManager* GetTexMan();

	void SetPosition(float x,float y);
	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	void Move(float x,float y);
	void Move(sf::Vector2f pos);

	void SetVelocity(float x,float y);
	void SetVelocity(sf::Vector2f vel);
	sf::Vector2f GetVelocity();
	void Accelerate(float x,float y);
	void Accelerate(sf::Vector2f vel);

	void SetColor(char r,char b,char g,char a=255);
	void SetColor(sf::Color color);
	sf::Color GetColor();

	void SetScale(float x,float y);
	void SetScale(sf::Vector2f scale);
	sf::Vector2f GetScale();

	void SetRotation(float angle);
	void Rotate(float angle);
	float GetRotation();

	void SetRect(sf::IntRect rect);
	sf::IntRect GetRect();

	sf::FloatRect GetBounds();

	void SetCenter(float x,float y);
	void SetCenter(sf::Vector2f pos);
	sf::Vector2f GetCenter();

	sf::Sprite* GetSprite();

	bool Collide(sSprite *that);
};

class aSprite:public sSprite
{
private:
	unsigned int CurFrame;
	unsigned int NumFrameX;
	unsigned int NumFrameY;
	unsigned int AnimRate;
	unsigned int ElasTime;
	unsigned int StartX;
	unsigned int StartY;
	unsigned int FrameWidth;
	unsigned int FrameHeight;
	sf::IntRect Frame;
public:
	aSprite(	sfmlTextureManager *TM,
				std::string,
				sf::IntRect SubRect,
				unsigned int frame_count_x,
				unsigned int frame_count_y,
				unsigned int AnimationRate,
				bool anti_aliasing=true,
				bool origin_center=true,
				bool wrap=true);
	~aSprite();

	void Update(unsigned int time);
	void SetFrame(unsigned int frame);
	unsigned int GetFrame();
	void SetRate(unsigned int rate);
	float GetRate();
};

class sText
{
private:
	sf::Text textObject;
	sf::Font FontObject;

public:
	sText(std::string Fontfile,unsigned int size,const char *fmt, ...);
	
	void SetText(const char *fmt, ...);
	std::string GetText();

	void SetFont(std::string Fontfile);
	sf::Font GetFont();

	void SetSize(unsigned int size);
	unsigned int GetSize();

	void SetStyle(bool Bold,bool Italic,bool Underlined);
	void GetStyle(bool &Bold,bool &Italic,bool &Underlined);

	void SetColor(char r,char g,char b,char a=255);
	void SetColor(sf::Color color);
	sf::Color GetColor();

	void SetScale(float x,float y);
	void SetScale(sf::Vector2f scale);
	sf::Vector2f GetScale();

	void SetRotation(float angle);
	float GetRotation();
};

#endif
