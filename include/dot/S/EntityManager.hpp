#pragma once

#include <memory>
#include <vector>
#include "dot/E/Entity.hpp"
#include "dot/S/SystemModule.hpp"
#include "dot/S/RenderModule.hpp"

#include "dot/S/RenderSystem.hpp"
#include "dot/S/CollisionSystem.hpp"
#include "dot/S/LightSystem.hpp"

using dot::Entity;

namespace dot
{
class EntityManager
{
public:

	~EntityManager();
	void add(std::vector<std::shared_ptr<Entity>>& otherEntities);
	void add(std::shared_ptr<Entity> entity);

	// void addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask);

	void update(float deltaTime);
	void lateUpdate(float deltaTime);
	
	void render(dot::Window& window);

	void processNewObjects();

	void processRemovals();

	template <typename T>
	std::shared_ptr<T> addModule();

	template <typename T>
	std::shared_ptr<T> getModule();

private:
	std::vector<std::shared_ptr<dot::SystemModule>> m_modules;

	std::shared_ptr<dot::RenderModule> m_renderer;

	std::vector<std::shared_ptr<dot::Entity>> m_entities;
	std::vector<std::shared_ptr<dot::Entity>> m_newEntities;

}; // class EntityManager

/**********************************************
 *  Implementation of template methods
 *********************************************/
template<typename T>
std::shared_ptr<T> EntityManager::addModule()
{
	static_assert(std::is_base_of<dot::SystemModule, T>::value, "Error. T must be a derived type of dot::SystemModule, defined in dot/S/SystemModule.hpp. Assertion returned false.");
	for (auto& existingModule : m_modules)
	{
		if (std::dynamic_pointer_cast<T>(existingModule))
		{
			return std::dynamic_pointer_cast<T>(existingModule);
		}
	}
	// The EntityManager does not have a module 
	// of type T. so we create and add it to the
	// m_modules list
	std::shared_ptr<T> newModule = std::make_shared<T>();
	m_modules.push_back(newModule);

	// Check if the new module is also a derived 
	// type of RenderModule.
	if (std::is_base_of<dot::RenderModule, T>::value)
	{
		m_renderer = std::dynamic_pointer_cast<dot::RenderModule>(newModule);
	}

	return newModule;
}

template<typename T>
std::shared_ptr<T> EntityManager::getModule()
{
	for (auto& module: m_modules)
	{
		if (std::dynamic_pointer_cast<T>(module))
		{
			return std::dynamic_pointer_cast<T>(module);
		}
	}

	return nullptr;
}


}; // namespace Sigma