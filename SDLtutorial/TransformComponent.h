
#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <SDL.h>
#include "EntityManager.h"
#include "Constants.h"
#include "Game.h"


class TransformComponent : public Component
{
public:
	vf2d position;
	vf2d velocity;
	int width;
	int height;
	int scale;
	
	TransformComponent(vi2d pos, vi2d vel, int w, int h, int s)
	{
		position = pos;
		velocity = vel;
		width = w;
		height = h;
		scale = s;
	}

	void Initialize() override
	{

	}

	void Update(float deltaTime) override
	{
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
	}

	void Render() override
	{
		
	}

};
#endif // !TRANSFROMCOMPONENT_H
