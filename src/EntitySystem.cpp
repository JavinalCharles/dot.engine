#include "dot/S/EntitySystem.hpp"

using dot::EntitySystem;

void EntitySystem::update(float deltaTime)
{
	for (auto& e : m_entities)
	{
		e->update(deltaTime);
	}
}

void EntitySystem::lateUpdate(float deltaTime)
{
	for (auto& e : m_entities)
	{
		e->lateUpdate(deltaTime);
	}
}

void EntitySystem::render(dot::Window& window)
{
	// TODO
}

void EntitySystem::add(std::shared_ptr<Entity> entity)
{
	m_newEntities.push_back(entity);
}

void EntitySystem::add(std::vector<std::shared_ptr<Entity>>& otherEntities)
{
	m_newEntities.insert(m_newEntities.end(), otherEntities.begin(), otherEntities.end());
}

void EntitySystem::processNewObjects()
{
	if (m_newEntities.size() > 0)
	{
		for (const auto& e : m_newEntities)
		{
			e->awake();
		}
		for (const auto& e : m_newEntities)
		{
			e->start();
		}

		m_entities.insert(m_entities.end(), m_newEntities.begin(), m_newEntities.end());

		m_newEntities.clear();
	}
}

void EntitySystem::processRemovals()
{
	bool removed = false;
	auto iter = m_entities.begin();

	while(iter != m_entities.end())
	{
		auto entity = *iter;
		if(entity->isQueuedForRemoval())
		{
			iter = m_entities.erase(iter);
			removed = true;
		}
		else
		{
			++iter;
		}
	}

	if (removed)
	{
		// TODO
	}
}