#include "dot/C/SpriteBoxCollider.hpp"
#include "dot/E/Entity.hpp"

#include "dot/Debug/Debug.hpp"

using dot::SpriteBoxCollider;

SpriteBoxCollider::SpriteBoxCollider(dot::Entity* owner)
	: dot::Collider(owner)
{

}

void SpriteBoxCollider::awake()
{
	m_drawable = m_owner->getDrawable();
}

Manifold SpriteBoxCollider::intersects(std::shared_ptr<dot::Collider> other)
{
	Manifold m;;
	m.other = other->getCollidable();
	m.colliding = this->getCollidable().intersects(m.other);

	return m;
}

void SpriteBoxCollider::resolveOverlap(const Manifold& m)
{
	auto transform = m_owner->transform;
	if (transform->isStatic()) return;

	const sf::FloatRect& rect1 = this->getCollidable();
	const sf::FloatRect& rect2 = m.other;

	if (!rect1.intersects(rect2)) return;

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

void SpriteBoxCollider::setCollidable(const sf::FloatRect& rect) 
{
	// do nothing
}

sf::FloatRect SpriteBoxCollider::getCollidable()
{
	// Debug::log("SpriteBoxCollider::getCollidable()");
	return m_drawable->getGlobalBounds();
}