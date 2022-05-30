#include "dot/S/EntityManager.hpp"
#include "dot/Debug/Debug.hpp"

using dot::EntityManager;


EntityManager::~EntityManager()
{
	m_entities.clear();
	m_newEntities.clear();

}

void EntityManager::update(float deltaTime)
{
	for (auto& e : m_entities)
	{
		e->update(deltaTime);
	}
	for (auto& m : m_modules)
	{
		m->update(deltaTime);
	}
}

void EntityManager::lateUpdate(float deltaTime)
{
	for (auto& e : m_entities)
	{
		e->lateUpdate(deltaTime);
	}
	for(auto& m : m_modules)
	{
		m->lateUpdate(deltaTime);
	}
}

void EntityManager::render(dot::Window& window)
{
	m_renderer->render(window);
}

void EntityManager::add(std::shared_ptr<Entity> entity)
{
	m_newEntities.push_back(entity);
}

void EntityManager::add(std::vector<std::shared_ptr<Entity>>& otherEntities)
{
	m_newEntities.insert(m_newEntities.end(), otherEntities.begin(), otherEntities.end());
}

void EntityManager::processNewObjects()
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

		for (auto& m: m_modules)
		{
			m->add(m_newEntities);
		}

		m_newEntities.clear();
	}
}

void EntityManager::processRemovals()
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
		for (auto& m : m_modules)
		{
			m->processRemovals();
		}
		// TODO: Add removal for light system
	}
}
