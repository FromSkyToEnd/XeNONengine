/*******************************************************\

  Author: Frederic Duguay
	Date: 1st February 2013

	-----------------------

	Code greatly inspired by
		Darren Reid

	-----------------------

	sfmlTextureManager.cpp

\*******************************************************/

#include "sfmlTextureManager.h"

sfmlTextureManager::sfmlTextureManager(std::string Mediapath)
{
	texturePath = Mediapath;
}

sfmlTextureManager::~sfmlTextureManager()
{
	for(itor = textures.begin(); itor != textures.end(); itor++)
	{
		delete (itor)->second;
	}

	textures.clear();
}

sf::Texture* sfmlTextureManager::Load(std::string file, bool wrap, bool anti_aliasing)
{
	itor = textures.find(file);

	if(itor == textures.end())
	{
		tex *newtex = new tex;

		newtex->refcount = 1;
		newtex->unload = 1;

		std::string fullpath;
		fullpath = texturePath;
		fullpath.append(file);

		newtex->img.loadFromFile(fullpath);
		newtex->img.setRepeated(wrap);
		newtex->img.setSmooth(anti_aliasing);

		textures[file] = newtex;

		return &(newtex->img);
	}

	(*itor->second).refcount++;
	return &((*itor->second).img);
}

void sfmlTextureManager::Unload(std::string file)
{
	itor = textures.find(file);

	if(itor!=textures.end())
	{
		(*itor->second).refcount--;
		if((*itor->second).refcount <= 0 && (*itor->second).unload)
		{
			delete itor->second;
			textures.erase(itor);
		}
	}
}
