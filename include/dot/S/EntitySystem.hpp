#pragma once

#include <memory>
#include <vector>
#include "dot/E/Entity.hpp"
#include "dot/S/RenderSystem.hpp"
#include "dot/S/CollisionSystem.hpp"
#include "dot/S/LightSystem.hpp"

using dot::Entity;

namespace dot
{
class EntitySystem
{
public:

	~EntitySystem();
	void add(std::vector<std::shared_ptr<Entity>>& otherEntities);
	void add(std::shared_ptr<Entity> entity);

	void addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask);

	void update(float deltaTime);
	void lateUpdate(float deltaTime);
	void render(dot::Window& window);

	void processNewObjects();

	void processRemovals();

private:

	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Entity>> m_newEntities;
	
	dot::RenderSystem m_renderer;
	dot::CollisionSystem m_collider;
	dot::LightSystem m_lighter;

}; // class EntitySystem

}; // namespace Sigma