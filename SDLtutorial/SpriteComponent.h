
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <sdl.h>
#include "AssetManager.h"
#include "TextureManager.h"
#include "Animation.h"



class SpriteComponent : public Component
{
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(std::string assetTextureId)
	{
		isAnimated = false;
		isFixed = false;
		SetTexture(assetTextureId);
	}

	SpriteComponent(std::string id, int numFrames, int animatonSpeed, bool hasDirections, bool isFixed)
	{
		this->isAnimated = true;
		this->numFrames = numFrames;
		this->animationSpeed = animatonSpeed;
		this->isFixed = isFixed;

		if (hasDirections)
		{
			Animation downAnimation = Animation(0, numFrames, animationSpeed);
			Animation rightAnimation = Animation(1, numFrames, animationSpeed);
			Animation leftAnimation = Animation(2, numFrames, animationSpeed);
			Animation upAnimation = Animation(3, numFrames, animationSpeed);

			animations.emplace("DownAnimation", downAnimation);
			animations.emplace("RightAnimation", rightAnimation);
			animations.emplace("leftAnimation", leftAnimation);
			animations.emplace("UpAnimation", upAnimation);

			this->animatonIndex = 0;
			this->currentAnimationName = "DownAnimation";
		}
		else
		{
			Animation SingleAnimation = Animation(0, numFrames, animationSpeed);
			animations.emplace("SingleAnimation", SingleAnimation);
			this->animatonIndex = 0;
			this->currentAnimationName = "SingleAnimation";
		}

		Play(this->currentAnimationName);
		SetTexture(id);

	}

	void Play(std::string animationName)
	{
		numFrames = animations[animationName].numFrames;
		animatonIndex = animations[animationName].index;
		animationSpeed = animations[animationName].animationSpeed;
		currentAnimationName = animationName;
	}

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
		if (isAnimated)
		{
			sourceRect.x = (sourceRect.w * (SDL_GetTicks() / animationSpeed) % numFrames);
			sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
		}
		sourceRect.y = animatonIndex * transform->height;
		destinationRect.x = static_cast<int>(transform->position.x);
		destinationRect.y = static_cast<int>(transform->position.y);
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
	bool isAnimated;
	int numFrames;
	int animationSpeed;
	bool isFixed;
	std::map<std::string, Animation> animations;
	std::string currentAnimationName;
	unsigned int animatonIndex = 0;

};
#endif // !SPRITECOMPONENT_H
