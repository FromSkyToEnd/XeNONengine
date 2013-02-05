/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	SpriteWrapper.cpp

\*******************************************************/

#include "SpriteWrapper.h"

sSprite::sSprite(sfmlTextureManager *TM, std::string File, sf::IntRect SubRect, bool anti_aliasing, bool origin_center, bool wrap)
{
	Sprt.setTexture(*(TM->Load(File,wrap,anti_aliasing)));
	Sprt.setTextureRect(SubRect);
	if(origin_center)
		Sprt.setOrigin(SubRect.width*0.5,SubRect.height*0.5);
	file=File;
	TexMan=TM;
}

sSprite::~sSprite()
{
	TexMan->Unload(file);
}

std::string sSprite::GetFile()
{
	return file;
}

sfmlTextureManager* sSprite::GetTexMan()
{
	return TexMan;
}

void sSprite::SetPosition(float x, float y)
{
	Sprt.setPosition(x,y);
}

void sSprite::SetPosition(sf::Vector2f pos)
{
	Sprt.setPosition(pos);
}

sf::Vector2f sSprite::GetPosition()
{
	return Sprt.getPosition();
}

void sSprite::Move(float x, float y)
{
	Sprt.move(x,y);
}

void sSprite::Move(sf::Vector2f pos)
{
	Sprt.move(pos);
}

void sSprite::SetVelocity(float x, float y)
{
	velocity.x=x;
	velocity.y=y;
}

void sSprite::SetVelocity(sf::Vector2f vel)
{
	velocity=vel;
}

sf::Vector2f sSprite::GetVelocity()
{
	return velocity;
}

void sSprite::Accelerate(float x,float y)
{
	velocity.x+=x;
	velocity.y+=y;
}

void sSprite::Accelerate(sf::Vector2f vel)
{
	velocity.x+=vel.x;
	velocity.y+=vel.y;
}

void sSprite::SetColor(char r, char g, char b, char a)
{
	Sprt.setColor(sf::Color(r,g,b,a));
}

void sSprite::SetColor(sf::Color color)
{
	Sprt.setColor(color);
}

sf::Color sSprite::GetColor()
{
	return Sprt.getColor();
}

void sSprite::SetScale(float x, float y)
{
	Sprt.setScale(x,y);
}

void sSprite::SetScale(sf::Vector2f scale)
{
	Sprt.setScale(scale);
}

sf::Vector2f sSprite::GetScale()
{
	return Sprt.getScale();
}

void sSprite::SetRotation(float angle)
{
	Sprt.setRotation(angle);
}

void sSprite::Rotate(float angle)
{
	Sprt.rotate(angle);
}

float sSprite::GetRotation()
{
	return Sprt.getRotation();
}

void sSprite::SetRect(sf::IntRect rect)
{
	Sprt.setTextureRect(rect);
}

sf::IntRect sSprite::GetRect()
{
	return Sprt.getTextureRect();
}

sf::FloatRect sSprite::GetBounds()
{
	return Sprt.getGlobalBounds();
}

void sSprite::SetCenter(float x,float y)
{
	Sprt.setOrigin(x,y);
}

void sSprite::SetCenter(sf::Vector2f pos)
{
	Sprt.setOrigin(pos);
}

sf::Vector2f sSprite::GetCenter()
{
	return Sprt.getOrigin();
}

sf::Sprite* sSprite::GetSprite()
{
	return &Sprt;
}

void sSprite::Draw(sf::RenderTarget &view)
{
	view.draw(Sprt);
}

void sSprite::Draw(sf::RenderTarget &view, sf::RenderStates &Rend)
{
	view.draw(Sprt,Rend);
}

void sSprite::Update(unsigned int time)
{
	Move(velocity.x * time,velocity.y * time);
}

bool sSprite::Collide(sSprite *that)
{
	return Sprt.getGlobalBounds().intersects(that->GetBounds());
}

aSprite::aSprite(sfmlTextureManager *TM, std::string File, sf::IntRect SubRect, unsigned int frame_count_x, unsigned int frame_count_y, unsigned int AnimationRate, bool anti_aliasing, bool origin_center, bool wrap):
sSprite(TM,File,SubRect,anti_aliasing,origin_center,wrap)
{
	CurFrame=0;
	NumFrameX=frame_count_x;
	NumFrameY=frame_count_y;
	AnimRate=AnimationRate;
	StartX=SubRect.left;
	StartY=SubRect.top;
	FrameWidth=SubRect.width;
	FrameHeight=SubRect.height;
	Frame=SubRect;
}

aSprite::~aSprite()
{
	GetTexMan()->Unload(GetFile());
}

void aSprite::Update(unsigned int time)
{
	ElasTime += time;
	if(ElasTime >= AnimRate)
	{
		ElasTime -= AnimRate;
		CurFrame=(CurFrame+1)%(NumFrameX*NumFrameY);

		Frame.left	= (CurFrame%NumFrameX) * FrameWidth;
		Frame.top	= (CurFrame/NumFrameX) * FrameHeight;
		
		SetRect(Frame);
	}
	Move(GetVelocity().x * time,GetVelocity().y * time);
}

void aSprite::SetFrame(unsigned int frame)
{
	CurFrame=frame%(NumFrameX*NumFrameY);
}

unsigned int aSprite::GetFrame()
{
	return CurFrame;
}

void aSprite::SetRate(unsigned int rate)
{
	AnimRate=rate;
}

float aSprite::GetRate()
{
	return AnimRate;
}

sText::sText(std::string Fontfile, unsigned int size, const char *fmt, ...)
{
	char text[1024];
	va_list ap;

	if(fmt == NULL) return;

	va_start(ap, fmt);
	vsnprintf_s(text,1024,1024, fmt, ap);
	va_end(ap);

	FontObject.loadFromFile(std::string("Media/").append(Fontfile));
	
	textObject.setFont(FontObject);
	
	textObject.setCharacterSize(size);

	textObject.setString(text);
}

void sText::SetText(const char *fmt, ...)
{
	char text[1024];
	va_list ap;

	if(fmt == NULL) return;

	va_start(ap, fmt);
	vsnprintf_s(text,1024,1024, fmt, ap);
	va_end(ap);

	textObject.setString(text);
}

std::string sText::GetText()
{
	return textObject.getString();
}

void sText::SetFont(std::string Fontfile)
{
	FontObject.loadFromFile(Fontfile);
}

sf::Font sText::GetFont()
{
	return textObject.getFont();
}

void sText::SetSize(unsigned int size)
{
	textObject.setCharacterSize(size);
}

unsigned int sText::GetSize()
{
	return textObject.getCharacterSize();
}

void sText::SetStyle(bool Bold, bool Italic, bool Underlined)
{
	sf::Uint32 style = 0x00000000;
	style = style | (Bold?sf::Text::Bold:0);
	style = style | (Italic?sf::Text::Italic:0);
	style = style | (Underlined?sf::Text::Underlined:0);

	textObject.setStyle(style);
}

void sText::GetStyle(bool &Bold, bool &Italic, bool &Underlined)
{
	sf::Uint32 style = textObject.getStyle();
	Bold = style & sf::Text::Bold;
	Italic = style & sf::Text::Italic;
	Underlined = style & sf::Text::Underlined;
}

void sText::SetColor(char r, char g, char b, char a)
{
	textObject.setColor(sf::Color(r,g,b,a));
}

void sText::SetColor(sf::Color color)
{
	textObject.setColor(color);
}

sf::Color sText::GetColor()
{
	return textObject.getColor();
}

void sText::SetScale(float x, float y)
{
	textObject.setScale(x,y);
}

void sText::SetScale(sf::Vector2f scale)
{
	textObject.setScale(scale);
}

sf::Vector2f sText::GetScale()
{
	return textObject.getScale();
}

void sText::SetRotation(float angle)
{
	textObject.setRotation(angle);
}

float sText::GetRotation()
{
	return textObject.getRotation();
}
