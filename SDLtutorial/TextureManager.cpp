#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* AltSurface = NULL;
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(fileName);
	if (surface == NULL)
	{
		AltSurface = SDL_ConvertSurface(surface, Game::screenSurface->format, 0);
		texture = SDL_CreateTextureFromSurface(Game::renderer, AltSurface);
	}
	else {
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	}

	SDL_FreeSurface(surface);
	SDL_FreeSurface(AltSurface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect DestinationRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &sourceRect, &DestinationRect, 0.0, NULL, flip);
}

