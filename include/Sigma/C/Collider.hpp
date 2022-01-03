#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Sigma/C/Component.hpp"

namespace Sigma
{
struct Manifold
{
	bool colliding = false;
	const sf::FloatRect* other;
}; // struct Manifold

class Collider : public Component
{
public:
	Collider(Sigma::Entity* owner);
	virtual ~Collider();

	virtual Manifold intersects(std::shared_ptr<Collider> other) = 0;
	virtual void resolveOverlap(const Manifold& m) = 0;

	unsigned getLayer() const;

	virtual void setLayer(unsigned layer);
private:
	unsigned m_layer;
};

}; // namespace Sigma