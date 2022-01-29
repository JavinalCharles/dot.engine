#pragma once

#include <memory>
#include <vector>
#include "dot/C/Collider.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"

namespace dot
{

class CollisionTree
{
public:
	CollisionTree();
	CollisionTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, CollisionTree* parent);

	void drawDebug();

	void insert(std::shared_ptr<dot::Collider> object);
	void remove(std::shared_ptr<dot::Collider> object);

	void clear();
	void clearRemovedObjects();

	void updatePosition(std::shared_ptr<dot::Collider> object, bool originalTree = true);

	std::vector<std::shared_ptr<dot::Collider>> search(const sf::FloatRect& area);

	const sf::FloatRect& getBounds() const;

private:
	void search(const sf::FloatRect& area, std::vector<std::shared_ptr<dot::Collider>>& overlappingObjects);
	void removeID(unsigned long long id);

	int getChildIndexForObject(const sf::FloatRect& objectBounds);

	void split();

	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int m_maxObjects;
	int m_maxLevels;

	CollisionTree* m_parent;

	std::shared_ptr<CollisionTree> m_children[4];

	std::vector<std::shared_ptr<dot::Collider>> m_objects;

	int m_level;

	sf::FloatRect m_bounds;

}; // class CollisionTree

}; // namespace dot