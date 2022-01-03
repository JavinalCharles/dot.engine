#pragma once

#include <vector>
#include <memory>
#include "Sigma/Window.hpp"
#include "Sigma/C/Component.hpp"
#include "Sigma/C/Transform.hpp"
#include "Sigma/C/InstanceID.hpp"
#include "Sigma/C/Drawable.hpp"
#include "Sigma/C/Collidable.hpp"
#include "Sigma/SharedContext.hpp"

namespace Sigma
{

using Sigma::Component;
using Sigma::SharedContext;

class Entity
{
public:
	Entity(SharedContext* context);

	/**
	 * Entity::awake()
	 * - use to ensure the required components are
	 * are present
	 * */
	void awake();

	/**
	 * Entity::start()
	 * - called after the awake() method. Use to 
	 * initialize member attributes.
	 * */
	void start();

	void update(float deltaTime);
	void lateUpdate(float deltaTime);
	void render(Window& window);

	/**
	 * Entity::addComponent<T>()
	 * - creates a Component and adds it to the
	 * Entity..
	 * */
	template <typename T>
	std::shared_ptr<T> addComponent();

	template <typename T>
	std::shared_ptr<T> getComponent();

	std::shared_ptr<Sigma::Drawable> getDrawable();

	bool isQueuedForRemoval();
	void queueForRemoval();
	

public: // Public Attributes

	std::shared_ptr<Sigma::Transform> transform;
	std::shared_ptr<Sigma::InstanceID> instanceID;

	Sigma::SharedContext* context;

private:
	std::vector<std::shared_ptr<Component>> m_components;

	bool m_queuedForRemoval;

	std::shared_ptr<Sigma::Drawable> m_drawable;
	std::vector<std::shared_ptr<Sigma::Collidable>> m_collidables;
}; // class Entity

/************************************
 * Implemnations of template methods:
 ************************************/
template<typename T>
std::shared_ptr<T> Entity::addComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "Error. T must be a derived type of Sigma::C::Component. Assertion returned false.");
	// Check that the Entity no longer have a
	// Component of T type. Prevent it if found.
	for(auto& existingComponent : m_components)
	{
		if (std::dynamic_pointer_cast<T>(existingComponent))
		{
			return std::dynamic_pointer_cast<T>(existingComponent);
		}
	}

	// The Entity does not have a Component of T
	// type so we create it, and add it to the list.
	std::shared_ptr<T> newComponent = std::make_shared<T>(this);
	m_components.push_back(newComponent);

	// Check if the component is a Drawable
	if (std::dynamic_pointer_cast<Sigma::Drawable>(newComponent))
	{
		m_drawable = std::dynamic_pointer_cast<Sigma::Drawable>(newComponent);
	}

	return newComponent;
}

template<typename T>
std::shared_ptr<T> Entity::getComponent()
{
	for (auto& existingComponent : m_components)
	{
		if (std::dynamic_pointer_cast<T>(existingComponent))
		{
			return std::dynamic_pointer_cast<T>(existingComponent);
		}
	}
}

}; // namespace Sigma