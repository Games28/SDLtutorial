#include <iostream>
#include "EntityManager.h"
#include "Collsion.h"
#include "ColliderComponent.h"
//#include "Entity.h"

void EntityManager::ClearData()
{
	for (auto& entity : entities)
	{
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
	DestroyInactiveEntities();
}

void EntityManager::Render()
{
	for (int layernumber = 0; layernumber < NUM_LAYERS; layernumber++)
	{
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layernumber)))
		{
			entity->Render();
		}
	}
	
}

bool EntityManager::HasNoEntities()
{
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer)
{
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{

	return entities;
}

Entity* EntityManager::GetEntity(std::string name, LayerType layer)
{
	for (auto& entity : entities)
	{
		if (entity->layer == layer)
		{
			
				return entity;
			
		}
	}
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
	std::vector<Entity*> selectedEntities;

	for (auto& entity : entities)
	{
		if (entity->layer == layer)
		{
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
}

unsigned int EntityManager::GetEntityCount()
{
	return entities.size();
}

CollisionType EntityManager::CheckCollisions() const
{
	for (auto& thisEntity : entities)
	{
		if (thisEntity->HasComponent<ColliderComponent>())
		{
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (auto& thatEntity : entities)
			{
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>())
				{
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider))
					{
						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("enemy") == 0)
						{
							return PLAYER_ENEMY_COLLISION;
						}

						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("projectile") == 0)
						{
							return PLAYER_PROJECTILE_COLLISION;
						}

						if (
							thisCollider->colliderTag.compare("enemy") == 0 &&
							thatCollider->colliderTag.compare("friendly_projectile") == 0)
						{
							return ENEMY_PROJECTILE_COLLISION;
						}

						if (
							thisCollider->colliderTag.compare("player") == 0 &&
							thatCollider->colliderTag.compare("level_complete") == 0)
						{
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}

						
					}

				}
			}
		}
	}

	return NO_COLLISION;

}

void EntityManager::DestroyInactiveEntities()
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsActive())
		{
			entities.erase(entities.begin() + i);
		}
	}
}



