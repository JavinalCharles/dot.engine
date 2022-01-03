#pragma once

#include "Sigma/C/Component.hpp"
#include "Sigma/C/Collider.hpp"

using Sigma::Collider;
using Sigma::Manifold;

namespace Sigma
{

enum class Origin {
	TopLeft,
	AbsCentre,
	MiBottom
}; // enum Origin

class BoxCollider : public Sigma::Collider
{
public:
	BoxCollider(Sigma::Entity* owner);
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

}; // namespace Sigma