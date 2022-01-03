#include "Sigma/C/Component.hpp"

using Sigma::Component;
using Sigma::Entity;

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