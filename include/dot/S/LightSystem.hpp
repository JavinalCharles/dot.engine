#pragma once
#include <memory>
#include <vector>
#include <cmath>
#include "dot/Containers/Quadtree.hpp"
#include "dot/C/LightBounds.hpp"
#include "dot/C/DrawnLightBounds.hpp"
#include "dot/C/RayCaster.hpp"
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

	void cast(const sf::Vector2f& from, const sf::Vector2f& to, int exclusionID = 0);
	std::vector<sf::Vector2f> buildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to);
	sf::FloatRect buildRayBounds(const sf::Vector2f& from, const sf::Vector2f& to);

private:
	LightBoundsTree m_boundsTree;

	std::vector<std::shared_ptr<dot::RayCaster>> m_rayCasters;
}; // LightSystem

}; // namespace dot