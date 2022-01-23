#pragma once

#include <map>
#include "dot/C/Drawable.hpp"
#include "dot/E/Entity.hpp"

using dot::Drawable;
using dot::Entity;
using dot::Window;

using drawLayer = unsigned;

namespace dot
{
class RenderSystem
{
public:
	~RenderSystem();

	void add(std::vector<std::shared_ptr<Entity>>& entities);
	void add(std::shared_ptr<Entity> entity);
	void processRemovals();

	void update(float deltaTime);

	void render(Window& window);
private:
	void sort();

	std::map<drawLayer, std::vector<std::shared_ptr<Drawable>>> m_drawables;

	static bool layerSort(std::shared_ptr<Drawable> a, std::shared_ptr<Drawable> b);
}; // class RenderSystem
}; // namespace dot