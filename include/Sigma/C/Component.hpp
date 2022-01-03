#pragma once

#include "Sigma/Window.hpp"

namespace Sigma
{
class Entity;

class Component
{
public:
	Component(Sigma::Entity* owner);
	virtual ~Component();

	virtual void awake();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void lateUpdate(float deltaTime);

	Sigma::Entity* getOwner();

protected:
	Sigma::Entity* m_owner;
};// class Component
}; // namespace Sigma