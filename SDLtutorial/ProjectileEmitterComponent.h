#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "Constants.h"
#include "EntityManager.h"
#include "TransformComponent.h"

class ProjectileEmitterComponent : public Component
{
public:
	ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldloop)
	{
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldloop;
		this->angleRad = deg2rad(angleDeg);
	}

	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		origin = { transform->position.x, transform->position.y };
		transform->velocity = { cos(angleRad) * speed, sin(angleRad) * speed };
	}

	void Update(float deltaTime) override
	{
		float distX = transform->position.x - origin.x;
		float distY = transform->position.y - origin.y;
		float distance = sqrtf(distX * distX + distY * distY);

		if (distance > range)
		{
			if (shouldLoop)
			{
				transform->position.x = origin.x;
				transform->position.y = origin.y;
			}
			else
			{
				owner->Destroy();
			}
		}
	}

	float deg2rad(float fAngleDeg) { return fAngleDeg * 3.14159f / 180.0f; }
	float rad2deg(float fAngleRad) { return fAngleRad / 3.14159f * 180.0f; }

private:
	TransformComponent* transform;
	vf2d origin;
	int speed;
	int range;
	float angleRad;
	bool shouldLoop;



};

#endif // !PROJECTILEEMITTERCOMPONENT_H

