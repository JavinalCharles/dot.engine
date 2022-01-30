#include "dot/C/BoxCollider.hpp"
#include "dot/E/Entity.hpp"
#include <cmath>

#include "dot/Debug/Debug.hpp"

using std::fabs;
using dot::BoxCollider;
using dot::Collider;
using dot::Entity;
using dot::Origin;

BoxCollider::BoxCollider(Entity* owner)
	: Collider(owner),
	m_origin(Origin::AbsCentre),
	m_offset(sf::Vector2f(0.f, 0.f))
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::setCollidable(const sf::FloatRect& rect)
{
	m_AABB = rect;
	setPosition();
}

sf::FloatRect BoxCollider::getCollidable()
{
	// Debug::log("getting collidable.");
	setPosition();
	return m_AABB;
}

sf::FloatRect BoxCollider::getBounds()
{
	setPosition();
	return m_AABB;
}

void BoxCollider::setOrigin(const Origin& origin)
{
	this->m_origin = origin;
}

void BoxCollider::setPosition()
{
	// Debug::log("BoxCollider::setPosition() - getting pos of : " + std::to_string(m_owner->instanceID->get()));
	sf::Vector2f pos = m_owner->transform->getPosition();

	switch(m_origin)
	{
		case(Origin::TopLeft) :
			m_AABB.left = pos.x + m_offset.x;
			m_AABB.top = pos.y + m_offset.y;
			break;
		case(Origin::AbsCentre) :
			m_AABB.left = pos.x - (m_AABB.width / 2) + m_offset.x;
			m_AABB.top = pos.y - (m_AABB.height / 2) + m_offset.y;
			break;
		case(Origin::MiBottom) :
			m_AABB.left = pos.x - (m_AABB.width / 2) + m_offset.x;
			m_AABB.top = pos.y - m_AABB.height + m_offset.y;
			break;
	}
}

// Manifold BoxCollider::intersects(std::shared_ptr<Collider> other)
// {
// 	Manifold m;
// 	m.colliding = false;

// 	std::shared_ptr<BoxCollider> boxCollider = std::dynamic_pointer_cast<BoxCollider>(other);
// 	if (boxCollider)
// 	{
// 		const sf::FloatRect& rect1 = getCollidable();
// 		const sf::FloatRect& rect2 = boxCollider->getCollidable();

// 		if (rect1.intersects(rect2))
// 		{
// 			m.colliding = true;
// 			m.other = rect2;
// 		}
// 	}
// 	return m;
// }

void BoxCollider::resolveOverlap(const Manifold& m)
{
	auto transform = m_owner->transform;
	if (transform->isStatic())
	{
		return;
	}

	const sf::FloatRect& rect1 = getCollidable();
	const sf::FloatRect rect2 = m.other;

	if (!rect1.intersects(rect2))
	{
		return;
	}

	float resolve = 0;
	float xDiff = (rect1.left + (rect1.width * 0.5f)) - (rect2.left + (rect2.width * 0.5f));
	float yDiff = (rect1.top + (rect1.height * 0.5f)) - (rect2.top + (rect2.height * 0.5f));

	if (fabs(xDiff) > fabs(yDiff))
	{
		if (xDiff > 0)
		{
			resolve = (rect2.left + rect2.width) - rect1.left;
		}
		else
		{
			resolve = -((rect1.left + rect1.width) - rect2.left);
		}
		transform->addPosition(resolve, 0);
	}
	else
	{
		if (yDiff > 0) // Colliding above
		{
			resolve = (rect2.top + rect2.height) - rect1.top;
		}
		else
		{
			resolve = -((rect1.top + rect1.height) - rect2.top);
		}
		transform->addPosition(0, resolve);
	}
}

void BoxCollider::setOffset(const sf::Vector2f& offset)
{
	m_offset = offset;
}

void BoxCollider::setOffset(float x, float y)
{
	m_offset.x = x;
	m_offset.y = y;
}

void BoxCollider::setSize(const sf::Vector2f& size)
{
	m_AABB.width = size.x;
	m_AABB.height = size.y;
}

void BoxCollider::setSize(float width, float height)
{
	m_AABB.width = width;
	m_AABB.height = height;
}