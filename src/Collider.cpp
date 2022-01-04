#include "dot/C/Collider.hpp"

using dot::Collider;
using dot::Entity;

Collider::Collider(Entity* owner)
	: Component(owner),
	m_layer(0u)
{

}

Collider::~Collider()
{

}

unsigned Collider::getLayer() const
{
	return m_layer;
}

void Collider::setLayer(unsigned layer)
{
	m_layer = layer;
}