#include "dot/S/EntitySystem.hpp"
#include "dot/Debug/Debug.hpp"

using dot::EntitySystem;


EntitySystem::~EntitySystem()
{
	Debug::log("EntitySystem::~EntitySystem() entered");
	m_entities.clear();
	m_newEntities.clear();
	Debug::log("EntitySystem::~EntitySystem() exiting");
}

void EntitySystem::update(float deltaTime)
{
	for (auto& e : m_entities)
	{
		e->update(deltaTime);
	}
	m_collider.update();
	m_renderer.update(deltaTime);
	m_lighter.update();
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
	m_renderer.render(window);
}

void EntitySystem::add(std::shared_ptr<Entity> entity)
{
	m_newEntities.push_back(entity);
}

void EntitySystem::add(std::vector<std::shared_ptr<Entity>>& otherEntities)
{
	m_newEntities.insert(m_newEntities.end(), otherEntities.begin(), otherEntities.end());
}

void EntitySystem::addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask)
{
	m_collider.addCollisionLayers(collisionLayer, collisionBitmask);
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

		m_renderer.add(m_newEntities);
		m_collider.add(m_newEntities);
		m_lighter.add(m_newEntities);

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
		m_renderer.processRemovals();
		m_collider.processRemovals();
		// TODO: Add removal for light system
	}
}