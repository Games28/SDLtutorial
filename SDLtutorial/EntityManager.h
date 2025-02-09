
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Constants.h"

#include <vector>

//class Entity;


class EntityManager
{
public:
	void ClearData();
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName, LayerType layer);
	std::vector<Entity*> GetEntities() const;
	Entity* GetEntity(std::string name ,LayerType layer);
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
	unsigned int GetEntityCount();
	CollisionType CheckCollisions() const;
	void DestroyInactiveEntities();
private:
	std::vector<Entity*> entities;
	

};


#endif // !ENTITYMANAGER_H
