#pragma once

#include "dot/C/Component.hpp"
#include "dot/C/Collider.hpp"

using dot::Collider;
using dot::Manifold;

namespace dot
{

enum class Origin {
	TopLeft,
	AbsCentre,
	MiBottom
}; // enum Origin

class BoxCollider : public dot::Collider
{
public:
	BoxCollider(dot::Entity* owner);
	virtual ~BoxCollider();

	virtual Manifold intersects(std::shared_ptr<Collider> other) override;
	virtual void resolveOverlap(const Manifold& m) override;

	void setCollidable(const sf::FloatRect& rect);
	const sf::FloatRect& getCollidable();

	void setOrigin(const Origin& origin);

	void setOffset(const sf::Vector2f& offset);
	void setOffset(float x, float y);
	void setSize(const sf::Vector2f& size);
	void setSize(float width, float height);

private:
	void setPosition();

	sf::FloatRect m_AABB;
	Origin m_origin;
	sf::Vector2f m_offset;
};

}; // namespace dot