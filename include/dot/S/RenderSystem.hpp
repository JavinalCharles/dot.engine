#pragma once

#include <map>
#include "dot/C/Drawable.hpp"
#include "dot/E/Entity.hpp"
#include "dot/S/RenderModule.hpp"

using dot::Drawable;
using dot::Entity;
using dot::Window;

using drawLayer = unsigned;

namespace dot
{
class RenderSystem : public dot::RenderModule
{
public:
	virtual ~RenderSystem();

	virtual void add(std::vector<std::shared_ptr<Entity>>& entities) override;
	virtual void add(std::shared_ptr<Entity>& entity) override;
	virtual void processRemovals() override;

	virtual void update(float deltaTime) override;

	virtual void render(Window& window) override;
private:
	void sort();

	std::map<drawLayer, std::vector<std::shared_ptr<Drawable>>> m_drawables;

	static bool layerSort(std::shared_ptr<Drawable> a, std::shared_ptr<Drawable> b);
}; // class RenderSystem
}; // namespace dot