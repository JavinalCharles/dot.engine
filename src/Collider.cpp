#include "dot/C/Collider.hpp"
#include "dot/Containers/Quadtree.hpp"


using dot::Collider;
using dot::Entity;

Collider::Collider(Entity* owner)
	: Component(owner),
	m_layer(0u),
	m_containingTree(nullptr)
{

}

Collider::~Collider()
{

}

dot::Manifold Collider::intersects(std::shared_ptr<dot::Collider> other)
{
	Manifold m;
	m.colliding = false;

	sf::FloatRect rect1 = this->getCollidable();
	sf::FloatRect rect2 = other->getCollidable();

	if (rect1.intersects(rect2))
	{
		m.colliding = true;
		m.other = rect2;
	}

	return m;
}

unsigned Collider::getLayer() const
{
	return m_layer;
}

void Collider::setLayer(unsigned layer)
{
	m_layer = layer;
}

void Collider::setTree(dot::Quadtree<Collider>* tree)
{
	m_containingTree = tree;
}

void Collider::updateTree()
{
	if (m_containingTree != nullptr)
	{
		if (m_containingTree->getBounds().intersects(this->getBounds()))
		{
			m_containingTree->updatePosition(shared_from_this());
		}
	}
}