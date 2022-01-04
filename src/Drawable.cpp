#include "dot/C/Drawable.hpp"

using dot::Component;
using dot::Drawable;
using dot::Entity;
using dot::Window;


Drawable::Drawable(Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: Component(owner),
	m_sortOrder(sortOrder), 
	m_layer(drawLayer)
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