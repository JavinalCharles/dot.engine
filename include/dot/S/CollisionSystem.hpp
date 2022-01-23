#pragma once

#include <vector>
#include <memory>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstdarg>

#include "dot/E/Entity.hpp"
#include "dot/C/BoxCollider.hpp"
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

	void addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask);

	void processRemovals();
	void update();

private:
	void resolve();
	void processCollidingEntities();

	std::unordered_map<unsigned, dot::Bitmask, dot::EnumClassHash> m_collisionLayers;
	
	std::unordered_map<unsigned, std::vector<std::shared_ptr<dot::BoxCollider>>, EnumClassHash> m_collidables;

	std::unordered_set<std::pair<std::shared_ptr<dot::BoxCollider>, std::shared_ptr<dot::BoxCollider>>, dot::ComponentPairHash> m_objectsColliding;

	dot::Quadtree m_collisionTree;

}; // class CollisionSystem
}; // namespace dot