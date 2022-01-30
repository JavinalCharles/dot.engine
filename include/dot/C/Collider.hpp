#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "dot/C/Component.hpp"
// #include "dot/Containers/Quadtree.hpp"

namespace dot
{

template <typename T>
class Quadtree;

struct Manifold
{
	bool colliding = false;
	sf::FloatRect other;
}; // struct Manifold

class Collider : public Component, public std::enable_shared_from_this<dot::Collider>
{
public:
	Collider(dot::Entity* owner);
	virtual ~Collider();

	virtual Manifold intersects(std::shared_ptr<dot::Collider> other);

	virtual void resolveOverlap(const Manifold& m) = 0;

	virtual void setCollidable(const sf::FloatRect& rect) = 0;
	virtual sf::FloatRect getCollidable() = 0;

	virtual sf::FloatRect getBounds() = 0;
	
	void setTree(Quadtree<Collider>* tree);

	unsigned getLayer() const;

	virtual void setLayer(unsigned layer);

	void updateTree();
private:
	unsigned m_layer;

	Quadtree<Collider>* m_containingTree;
};

}; // namespace dot