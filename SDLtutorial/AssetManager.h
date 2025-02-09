
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include <SDL_ttf.h>
#include "EntityManager.h"
#include "FontManager.h"
#include "TextureManager.h"



class AssetManager
{
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureid, const char* filePath);
	SDL_Texture* GetTexture(std::string textureid);
	
	void AddFont(std::string fontId, const char* filePath, int fontSize);
	TTF_Font* GetFont(std::string fontId);
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};

#endif // !ASSETMANAGER_H
