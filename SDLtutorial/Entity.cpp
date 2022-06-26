#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager& manager) : Manager(manager)
{
	this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : Manager(manager), name(name)
{
	this->isActive = true;
}

void Entity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : components)
	{
		component->Render();
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::IsActive() const
{
	return this->isActive;
}

void Entity::ListAllComponents() const
{
}
