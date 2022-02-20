#include "dot/S/LightSystem.hpp"

using dot::LightSystem;

LightSystem::LightSystem()
	: m_boundsTree(10, 10, 0, {0, 0, 4200, 4200}, nullptr)
{

}

LightSystem::~LightSystem()
{
	m_boundsTree.clear();
}

void LightSystem::add(std::vector<std::shared_ptr<dot::Entity>>& entities)
{
	for (auto& e : entities)
	{
		auto bound = e->getComponent<dot::LightBounds>();
		if (bound != nullptr)
		{
			m_boundsTree.insert(bound);
		}
	}
}

void LightSystem::processRemovals()
{
	m_boundsTree.clearRemovedObjects();
}

void LightSystem::update()
{
	
}