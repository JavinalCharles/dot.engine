#pragma once

#include <vector>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstdarg>

#include "dot/E/Entity.hpp"
#include "dot/C/Collider.hpp"
#include "dot/Containers/Quadtree.hpp"
#include "dot/Utilities/Bitmask.hpp"
#include "dot/Utilities/EnumClassHash.hpp"
#include "dot/Utilities/ComponentPairHash.hpp"

namespace dot
{
class CollisionSystem
{
public:
	CollisionSystem();

	~CollisionSystem();

	void add(std::vector<std::shared_ptr<dot::Entity>>& entities);
	void processRemovals();

	void addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask);

	void updatePositions();


	void resolve();
	void update();

private:
	void processCollidingEntities();

	std::unordered_map<unsigned, dot::Bitmask, dot::EnumClassHash> m_collisionLayers;

	std::vector<std::shared_ptr<dot::Collider>> m_nonStatics;

	std::unordered_set<std::pair<std::shared_ptr<dot::Collider>, std::shared_ptr<dot::Collider>>, dot::ComponentPairHash> m_objectsColliding;

	dot::CollisionTree m_collisionTree;

}; // class CollisionSystem
}; // namespace dot