#include "dot/E/Entity.hpp"

using dot::Entity;

Entity::Entity(dot::SharedContext* context)
	: context(context),
	m_queuedForRemoval(false)
{
	this->transform = this->addComponent<dot::Transform>();
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

bool Entity::isQueuedForRemoval()
{
	return m_queuedForRemoval;
}