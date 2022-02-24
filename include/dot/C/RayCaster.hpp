#pragma once

#include <cmath>
#include "dot/C/Component.hpp"
#include "dot/C/Drawable.hpp"
#include "dot/Utilities/Utils.hpp"

namespace dot
{
class RayCaster : public dot::Component
{
public:
	RayCaster(dot::Entity* owner);
	virtual ~RayCaster();

	void setMaxDistance(float maxDistance);
	void setTileSize(const sf::Vector2f& size);
	void setTileSize(float width, float height);
	void setAngleAdjustment(float adjustment);
	void setTo(const sf::Vector2f& to);


	float getMaxDistance() const;
	const sf::Vector2f& getTileSize() const;
	const sf::Vector2f& getTo() const;

private:
	float m_maxDistance;
	float m_angleAdjustment;

	sf::Vector2f m_tileSize;

	sf::Color m_rayColor;

	sf::Vector2f m_to;
	static constexpr float PI = 3.14159265f;
}; // class RayCaster


}; // namespace dot