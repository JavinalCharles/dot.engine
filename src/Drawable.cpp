#include "Sigma/C/Drawable.hpp"

using Sigma::Component;
using Sigma::Drawable;
using Sigma::Entity;
using Sigma::Window;


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