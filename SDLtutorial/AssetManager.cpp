#include "AssetManager.h"
#include "TransformComponent.h"


AssetManager::AssetManager(EntityManager* manager) : manager(manager)
{
}



void AssetManager::ClearData()
{
	textures.clear();
}

void AssetManager::AddTexture(std::string textureid, const char* filePath)
{
	textures.emplace(textureid, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureid)
{
	return textures[textureid];
}
