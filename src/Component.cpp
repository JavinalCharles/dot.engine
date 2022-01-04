#include "dot/C/Component.hpp"

using dot::Component;
using dot::Entity;

Component::Component(Entity* owner)
	: m_owner(owner)
{

}

Component::~Component()
{
	
}

void Component::awake()
{

}

void Component::start()
{

}

void Component::update(float deltaTime)
{

}

void Component::lateUpdate(float deltaTime)
{

}

Entity* Component::getOwner()
{
	return m_owner;
}