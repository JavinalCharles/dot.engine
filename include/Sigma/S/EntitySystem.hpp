#pragma once

#include <memory>
#include <vector>
#include "Sigma/E/Entity.hpp"

using Sigma::Entity;

namespace Sigma
{
class EntitySystem
{
public:
	void add(std::shared_ptr<Entity> entity);
	void add(std::vector<std::shared_ptr<Entity>>& otherEntities);

	void update(float deltaTime);
	void lateUpdate(float deltaTime);
	void render(Sigma::Window& window);

	void processNewObjects();

	void processRemovals();

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Entity>> m_newEntities;
	/**
	 * Add the rendering system and collision system
	 * */

};

}; // namespace Sigma