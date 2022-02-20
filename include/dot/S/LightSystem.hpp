#pragma once
#include <memory>
#include <vector>
#include "dot/Containers/Quadtree.hpp"
#include "dot/C/LightBounds.hpp"
#include "dot/C/DrawnLightBounds.hpp"
#include "dot/Utilities/EnumClassHash.hpp"

namespace dot
{
class LightSystem
{
public:
	LightSystem();

	~LightSystem();

	void add(std::vector<std::shared_ptr<dot::Entity>>& entities);

	void processRemovals();

	void update();

private:
	LightBoundsTree m_boundsTree;
}; // LightSystem

}; // namespace dot