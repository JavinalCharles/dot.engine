#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "dot/C/Component.hpp"

namespace dot
{
struct Manifold
{
	bool colliding = false;
	sf::FloatRect other;
}; // struct Manifold

class CollisionTree;

class Collider : public Component, public std::enable_shared_from_this<dot::Collider>
{
public:
	Collider(dot::Entity* owner);
	virtual ~Collider();

	virtual Manifold intersects(std::shared_ptr<dot::Collider> other);

	virtual void resolveOverlap(const Manifold& m) = 0;

	virtual void setCollidable(const sf::FloatRect& rect) = 0;
	virtual sf::FloatRect getCollidable() = 0;

	void setCollisionTree(CollisionTree* tree);

	unsigned getLayer() const;

	virtual void setLayer(unsigned layer);

	void updateTree();
private:
	unsigned m_layer;

	CollisionTree* m_containingTree;
};

}; // namespace dot