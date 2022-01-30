#pragma once

#include "dot/C/Collider.hpp"
#include "dot/C/Drawable.hpp"

#include <cmath>

namespace dot
{
class SpriteBoxCollider : public dot::Collider
{
public:
	SpriteBoxCollider(dot::Entity* owner);

	virtual void awake() override;

	virtual Manifold intersects(std::shared_ptr<Collider> other) override;
	virtual void resolveOverlap(const Manifold& m) override;

	virtual void setCollidable(const sf::FloatRect& rect) override;
	virtual sf::FloatRect getCollidable() override;
	virtual sf::FloatRect getBounds() override;

private:
	std::shared_ptr<dot::Drawable> m_drawable;
}; // class SpriteBoxCollider

}; // namespace dot
