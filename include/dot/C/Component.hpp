#pragma once

#include "dot/Window.hpp"

namespace dot
{
class Entity;

class Component
{
public:
	Component(dot::Entity* owner);
	virtual ~Component();

	virtual void awake();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void lateUpdate(float deltaTime);

	dot::Entity* getOwner();

protected:
	dot::Entity* m_owner;
};// class Component
}; // namespace dot