#pragma once

#include "dot/S/SystemModule.hpp"
#include "dot/C/Drawable.hpp"
#include "dot/E/Entity.hpp"

namespace dot
{
class RenderModule : public dot::SystemModule
{
public:
	RenderModule() : dot::SystemModule() {}

	virtual ~RenderModule() {}

	virtual void add(std::vector<std::shared_ptr<dot::Entity>>& entities) = 0;
	virtual void add(std::shared_ptr<dot::Entity>& entity) = 0;

	virtual void update(float deltaTime) {};
	virtual void lateUpdate(float deltaTime) {};

	virtual void render(dot::Window& window) = 0;
	virtual void processRemovals() = 0;
private:

};
};