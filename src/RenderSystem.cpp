#include "dot/S/RenderSystem.hpp"
#include <iostream>
#include "dot/Debug/Debug.hpp"


#include "dot/Debug/Debug.hpp"

using dot::RenderSystem;
using dot::Entity;
using dot::Drawable;
using dot::Window;

RenderSystem::~RenderSystem()
{
	Debug::log("RenderSystem::~RenderSystem() entered");
	m_drawables.clear();
	Debug::log("RenderSystem::~RenderSystem() exiting");
}

void RenderSystem::add(std::vector<std::shared_ptr<Entity>>& entities)
{
	for (auto& e : entities)
	{
		this->add(e);
	}
}

void RenderSystem::add(std::shared_ptr<Entity>& entity)
{
	std::shared_ptr<Drawable> entityDrawable = entity->getDrawable();
	
	if (!entityDrawable) 
		return;


	unsigned layer = entityDrawable->getDrawLayer();
	auto itr = m_drawables.find(layer);

	if (itr != m_drawables.end())
	{
		m_drawables[layer].push_back(entityDrawable);
		// std::cout << "Adding Entity with Drawable. InstanceID:" << entity->instanceID->get() << std::endl;
	}
	else
	{
		std::vector<std::shared_ptr<Drawable>> newLayer;
		newLayer.push_back(entityDrawable);
		m_drawables.insert(std::make_pair(layer, newLayer));
		// std::cout << "Adding Entity with Drawable. InstanceID:" << entity->instanceID->get() << std::endl;
	}
}

void RenderSystem::sort()
{
	for (auto& layer : m_drawables)
	{
		if (!std::is_sorted(layer.second.begin(), layer.second.end(), layerSort))
		{
			std::sort(layer.second.begin(), layer.second.end(), layerSort);
		}
	}
}

void RenderSystem::update(float deltaTime)
{
	this->sort();
}

void RenderSystem::render(Window& window)
{
	sf::FloatRect rect = window.getViewSpace();
	Debug::renderRect(rect, sf::Color::Yellow);

	for(auto& layer : m_drawables)
	{
		// std::cout << "Rendering " << layer.second.size() << " entities" << std::endl;
		for (auto& drawable : layer.second)
		{
			if (rect.intersects(drawable->getGlobalBounds()))
			{
				drawable->render(window);
			}
		}
	}
}

void RenderSystem::processRemovals()
{
	for (auto& layer : m_drawables)
	{
		auto iter = layer.second.begin();

		while(iter != layer.second.end())
		{
			auto drawable = *iter;
			if(!drawable->continueToDraw())
			{
				iter = layer.second.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}

bool RenderSystem::layerSort(std::shared_ptr<Drawable> a, std::shared_ptr<Drawable> b)
{
	return a->getSortOrder() < b->getSortOrder();
}