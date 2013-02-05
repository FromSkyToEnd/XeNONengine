/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	Code greatly inspired by
		Darren Reid

	-----------------------

	sfmlTextureManager.h

\*******************************************************/

#ifndef __SFML_TEXTURE_MANAGER_CLASS_H__
#define __SFML_TEXTURE_MANAGER_CLASS_H__

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <algorithm>

struct tex
{
	sf::Texture img;
	unsigned int refcount;
	bool unload;
};

struct ltstr
{
	bool operator()(std::string s1, std::string s2) const
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
};

class sfmlTextureManager
{
private:
	std::map <std::string, tex *, ltstr> textures;
	std::map <std::string, tex *, ltstr>::iterator itor;
	std::string texturePath;

public:
	sfmlTextureManager(std::string Mediapath);
	~sfmlTextureManager();

	sf::Texture* Load(std::string file, bool wrap=false, bool anti_aliasing=true);
	void Unload(std::string file);
};

#endif
