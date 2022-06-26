
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <sdl.h>
#include "AssetManager.h"
#include "TextureManager.h"



class SpriteComponent : public Component
{
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* filePath)
	{
		SetTexture(filePath);
	}

	void SetTexture(std::string assetTextureId)
	{
		texture = Game::assetManager->GetTexture(assetTextureId);
	}
	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = transform->width;
		sourceRect.h = transform->height;
	}

	void Update(float deltaTime) override
	{
		destinationRect.x = (int)transform->position.x;
		destinationRect.y = (int)transform->position.y;
		destinationRect.w = transform->width * transform->scale;
		destinationRect.h = transform->height * transform->scale;

	}

	void Render() override
	{
		TextureManager::Draw(texture, sourceRect, destinationRect, spriteFlip);
	}

private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

};
#endif // !SPRITECOMPONENT_H
