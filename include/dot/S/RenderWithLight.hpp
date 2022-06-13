#pragma once

#include <map>
#include "dot/C/Drawable.hpp"
#include "dot/C/LightBlend.hpp"
#include "dot/E/Entity.hpp"
#include "dot/S/RenderModule.hpp"
#include "dot/Containers/Quadtree.hpp"

using dot::Drawable;
using dot::Entity;
using dot::Window;

using drawLayer = unsigned;

namespace dot
{
class RenderWithLight : public dot::RenderModule
{
public:
	virtual ~RenderWithLight();

	virtual void add(std::vector<std::shared_ptr<Entity>>& entities) override;
	virtual void add(std::shared_ptr<Entity>& entity) override;
	virtual void processRemovals() override;

	virtual void render(Window& window) override;		
private:
	// void sort();

	std::map<drawLayer, dot::DrawableTree> m_drawables;
	
	std::vector<std::shared_ptr<dot::LightBlend>> m_lightSources;

	// static bool layerSort(std::shared_ptr<Drawable> a, std::shared_ptr<Drawable> b);
}; // class RenderWithLight


}; // namespace dot