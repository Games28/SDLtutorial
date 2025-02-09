#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "EntityManager.h"
#include "AssetManager.h"
#include "Game.h"

class TextLabelComponent : public Component
{
public:
	TextLabelComponent(int x, int y, std::string text, std::string fontfamily, const SDL_Color& color)
	{
		this->position.x = x;
		this->position.y = y;
		this->text = text;
		this->fontFamily = fontfamily;
		this->color = color;
		SetLabelText(text, fontfamily);

	}

	void SetLabelText(std::string text, std::string fontfamily)
	{
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontfamily),
			text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);

	}

	void Render() override
	{
		FontManager::Draw(texture, position);
	}

private:

	SDL_Rect position;
	std::string text;
	std::string fontFamily;
	SDL_Color color;
	SDL_Texture* texture;
};
#endif // !TEXTLABELCOMPONENT_H
