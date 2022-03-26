#include "dot/C/EntityComponent.hpp"
#include "dot/E/Entity.hpp"

using dot::EntityComponent;

EntityComponent::EntityComponent(dot::Entity* owner)
	: dot::Component(owner)
{
}

void EntityComponent::lateUpdate(float deltaTime)
{
	for (auto& c : m_children)
	{
		c->setPosition(m_owner->getPosition());
		c->setRotation(m_owner->getRotation());
	}
}

void EntityComponent::add(std::shared_ptr<dot::Entity> child)
{
	m_children.push_back(child);
}

std::vector<std::shared_ptr<dot::Entity>> EntityComponent::getEntities()
{
	return m_children;
}
