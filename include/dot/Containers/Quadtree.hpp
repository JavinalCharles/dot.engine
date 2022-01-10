#pragma once

#include <memory>
#include <vector>
#include "dot/C/BoxCollider.hpp"
#include "dot/E/Entity.hpp"

#include "dot/Debug/Debug.hpp"

using dot::BoxCollider;
using dot::Entity;


namespace dot
{
class Quadtree
{
public:
	Quadtree();
	Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent);

	void insert(std::shared_ptr<BoxCollider> object);
	void remove(std::shared_ptr<BoxCollider> object);

	void clear();

	std::vector<std::shared_ptr<BoxCollider>> search(const sf::FloatRect& area);
	const sf::FloatRect& getBounds() const;

	void drawDebug();

private:
	void search(const sf::FloatRect& area, std::vector<std::shared_ptr<BoxCollider>>& overlappingObjects);
	int getChildIndexForObject(const sf::FloatRect& objectBounds);

	void split();

	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int maxObjects;
	int maxLevels;

	Quadtree* parent;
	std::shared_ptr<Quadtree> children[4];

	std::vector<std::shared_ptr<BoxCollider>> objects;

	int level;

	sf::FloatRect bounds;

}; // class Quadtree

}; // namespace dot