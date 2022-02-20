#pragma once

#include <cmath>
#include "dot/C/Component.hpp"
#include "dot/C/Drawable.hpp"
#include "dot/Utilities/Utils.hpp"

namespace dot
{
class RayCaster : public dot::Drawable
{
public:
	RayCaster(dot::Entity*, unsigned sortOrder = 0u, unsigned drawLayer = 0u);
	virtual ~RayCaster();

	virtual void lateUpdate(float deltaTime) override;

	virtual void render(dot::Window& window) override;

	void setMaxDistance(float maxDistance);
	void setTileSize(const sf::Vector2f& size);
	void setTileSize(float width, float height);
	void setAngleAdjustment(float adjustment);


	float getMaxDistance() const;
	const sf::Vector2f& getTileSize() const;

	virtual bool continueToDraw() const override;

	sf::FloatRect getGlobalBounds() const override;

private:
	float m_maxDistance;
	float m_angleAdjustment;

	sf::Vector2f m_tileSize;

	sf::Color m_rayColor;
	sf::Vertex m_ray[2];

	static constexpr float PI = 3.14159265f;
}; // class RayCaster


}; // namespace dot