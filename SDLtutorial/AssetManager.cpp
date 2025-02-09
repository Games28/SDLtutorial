#include "AssetManager.h"
#include "TransformComponent.h"

AssetManager::AssetManager(EntityManager* manager)
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::ClearData()
{
	textures.clear();
	fonts.clear();
}

void AssetManager::AddTexture(std::string textureid, const char* filePath)
{
	textures.emplace(textureid, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureid)
{
	return textures[textureid];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize)
{
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId)
{
	return fonts[fontId];
}
