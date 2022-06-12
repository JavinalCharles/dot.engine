#include "dot/S/RenderWithLight.hpp"
#include "dot/Debug/Debug.hpp"

using dot::RenderWithLight;
using dot::Entity;
using dot::Drawable;
using dot::Window;

RenderWithLight::~RenderWithLight()
{
	m_drawables.clear();
	m_lightBlenders.clear();
}

void RenderWithLight::add(std::vector<std::shared_ptr<Entity>>& entities)
{
	for (auto& e : entities)
	{
		this->add(e);
	}
}

void RenderWithLight::add(std::shared_ptr<Entity>& entity)
{
	std::shared_ptr<Drawable> entityDrawable = entity->getDrawable();
	if (entityDrawable != nullptr)
	{
		unsigned layer = entityDrawable->getDrawLayer();
		auto itr = m_drawables.find(layer);

		if (itr != m_drawables.end())
		{
			m_drawables[layer].insert(entityDrawable);
		}
		else
		{
			m_drawables.emplace(layer, dot::DrawableTree());
		}
	}

	std::shared_ptr<dot::LightBlend> lightBlend = entity->getComponent<dot::LightBlend>();
	if (lightBlend != nullptr)
	{
		m_lightBlenders.push_back(lightBlend);
	}
}

void RenderWithLight::processRemovals()
{
	for (auto& layer : m_drawables)
	{
		layer.second.clearRemovedObjects();
	}
	auto iter = m_lightBlenders.begin();
	while(iter != m_lightBlenders.end())
	{
		auto obj = *iter;
		if(obj->getOwner()->isQueuedForRemoval())
		{
			iter = m_lightBlenders.erase(iter);
		}
		else {
			++iter;
		}
	}
}

void RenderWithLight::render(Window& window)
{
	sf::FloatRect rect = window.getViewSpace();

	for (auto& layer : m_drawables)
	{
		std::vector<std::shared_ptr<dot::Drawable>> drawables = layer.second.search(rect);
		for(auto& drawable : drawables)
		{
			if (rect.intersects(drawable->getGlobalBounds()))
			{
				drawable->render(window);
			}
		}
	}

	for (auto& lightBlend : m_lightBlenders)
	{
		lightBlend->render(window);
	}
}