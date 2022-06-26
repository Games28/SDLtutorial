
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "EntityManager.h"
#include "TextureManager.h"



class AssetManager
{
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureid, const char* filePath);
	SDL_Texture* GetTexture(std::string textureid);
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
};

#endif // !ASSETMANAGER_H
