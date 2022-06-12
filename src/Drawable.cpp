#include "dot/C/Drawable.hpp"
#include "dot/Containers/Quadtree.hpp"

using dot::Component;
using dot::Drawable;
using dot::Entity;
using dot::Window;


Drawable::Drawable(Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: Component(owner),
	m_sortOrder(sortOrder), 
	m_layer(drawLayer),
	m_containingTree(nullptr)
{

}

Drawable::~Drawable()
{

}

void Drawable::setSortOrder(unsigned order)
{
	m_sortOrder = order;
}

unsigned Drawable::getSortOrder() const
{
	return m_sortOrder;
}

void Drawable::setDrawLayer(unsigned layer)
{
	m_layer = layer;
}

unsigned Drawable::getDrawLayer() const
{
	return m_layer;
}

void Drawable::updateTree()
{
	if (m_containingTree == nullptr)
		return;

	if (m_containingTree->getBounds().intersects(this->getBounds()))
	{
		m_containingTree->updatePosition(shared_from_this());
	}
}

void Drawable::setTree(Quadtree<dot::Drawable>* tree)
{
	m_containingTree = tree;
}