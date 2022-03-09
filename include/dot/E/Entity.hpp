#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "dot/Window.hpp"
#include "dot/C/Component.hpp"
#include "dot/C/BoxCollider.hpp"
#include "dot/C/InstanceID.hpp"
#include "dot/C/Drawable.hpp"
#include "dot/C/Collidable.hpp"
#include "dot/SharedContext.hpp"

namespace dot
{

using dot::Component;
using dot::SharedContext;

class Entity : public sf::Transformable
{
public:
	Entity(SharedContext* context);

	/**
	 * Entity::awake()
	 * - use to ensure the required components are
	 * are present
	 * */
	virtual void awake();

	/**
	 * Entity::start()
	 * - called after the awake() method. Use to
	 * initialize member attributes.
	 * */
	virtual void start();

	virtual void update(float deltaTime);
	virtual void lateUpdate(float deltaTime);
	virtual void render(Window& window);

	/**
	 * Entity::addComponent<T>()
	 * - creates a Component and adds it to the
	 * Entity..
	 * */
	template <typename T>
	std::shared_ptr<T> addComponent();

	template <typename T>
	std::shared_ptr<T> getComponent();

	std::shared_ptr<dot::Drawable> getDrawable();

	bool isQueuedForRemoval() const;
	void queueForRemoval();

	void setStatic(bool isStatic);
	bool isStatic() const;

	void onCollisionEnter(std::shared_ptr<dot::Collider>& other);
	void onCollisionStay(std::shared_ptr<dot::Collider>& other);
	void onCollisionExit(std::shared_ptr<dot::Collider>& other);

	void addChild(std::shared_ptr<Entity> child);

private: // Helper Methods



public: // Public Attributes

	std::shared_ptr<dot::InstanceID> instanceID;

	dot::SharedContext* context;

private:
	std::vector<std::shared_ptr<Component>> m_components;

	bool m_queuedForRemoval;
	bool m_isStatic;

	std::shared_ptr<dot::Drawable> m_drawable;

	std::vector<std::shared_ptr<dot::Collidable>> m_collidables;
}; // class Entity

/************************************
 * Implemnations of template methods:
 ************************************/
template<typename T>
std::shared_ptr<T> Entity::addComponent()
{
	static_assert(std::is_base_of<Component, T>::value, "Error. T must be a derived type of dot::C::Component. Assertion returned false.");
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
	if (std::dynamic_pointer_cast<dot::Drawable>(newComponent))
	{
		m_drawable = std::dynamic_pointer_cast<dot::Drawable>(newComponent);
	}

	if (std::dynamic_pointer_cast<dot::Collidable>(newComponent))
	{
		m_collidables.push_back(std::dynamic_pointer_cast<dot::Collidable>(newComponent));
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

	return nullptr;
}

}; // namespace dot
