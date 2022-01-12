#pragma once
#include <cmath>
#include "dot/C/Component.hpp"

namespace dot
{
class Velocity : public dot::Component
{
public:
	Velocity(dot::Entity* entity);

	void update(float deltaTime) override;
	void lateUpdate(float deltaTime) override;

	void set(const sf::Vector2f& vel);
	void set(float x, float y);
	void setX(float x);
	void setY(float y);
	const sf::Vector2f& get() const;
private:
	void clampVelocity();

	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
};
	
}; // namespace dot