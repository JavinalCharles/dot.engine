#include "dot/E/Entity.hpp"

#include "dot/Debug/Debug.hpp"

using dot::Entity;

Entity::Entity(dot::SharedContext* context)
	: context(context),
	m_queuedForRemoval(false)
{
	this->instanceID = this->addComponent<dot::InstanceID>();
}

void Entity::awake()
{
	for (const auto& component : m_components)
	{
		component->awake();
	}
}

void Entity::start()
{
	for (const auto& component : m_components)
	{
		component->start();
	}
}

void Entity::update(float deltaTime)
{
	for (const auto& component : m_components)
	{
		component->update(deltaTime);
	}
}

void Entity::lateUpdate(float deltaTime)
{
	for (const auto& component : m_components)
	{
		component->lateUpdate(deltaTime);
	}
}

void Entity::render(Window& window)
{
	m_drawable->render(window);
}

std::shared_ptr<dot::Drawable> Entity::getDrawable()
{
	return m_drawable;
}

void Entity::queueForRemoval()
{
	this->m_queuedForRemoval = true;
}

bool Entity::isQueuedForRemoval() const
{
	return m_queuedForRemoval;
}

void Entity::setStatic(bool isStatic)
{
	m_isStatic = isStatic;
}

bool Entity::isStatic() const
{
	return m_isStatic;
}

void Entity::onCollisionEnter(std::shared_ptr<dot::Collider>& other)
{
	sf::FloatRect rect = other->getCollidable();

	for (const auto& component : m_collidables)
	{
		component->onCollisionEnter(other);
	}
}

void Entity::onCollisionStay(std::shared_ptr<dot::Collider>& other)
{
	for (const auto& component : m_collidables)
	{
		component->onCollisionStay(other);
	}
}

void Entity::onCollisionExit(std::shared_ptr<dot::Collider>& other)
{
	for (const auto& component : m_collidables)
	{
		component->onCollisionExit(other);
	}
}
