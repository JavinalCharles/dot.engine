#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "dot/C/Component.hpp"

namespace dot
{
struct Manifold
{
	bool colliding = false;
	const sf::FloatRect* other;
}; // struct Manifold

class Collider : public Component
{
public:
	Collider(dot::Entity* owner);
	virtual ~Collider();

	virtual Manifold intersects(std::shared_ptr<Collider> other) = 0;
	virtual void resolveOverlap(const Manifold& m) = 0;

	unsigned getLayer() const;

	virtual void setLayer(unsigned layer);
private:
	unsigned m_layer;
};

}; // namespace dot