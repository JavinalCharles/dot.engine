#pragma once

#include "dot/C/Component.hpp"

namespace dot
{

using dot::Component;

class Transform : public Component
{
public:
	Transform(dot::Entity* owner);

	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f& pos);
	void addPosition(float x, float y);
	void addPosition(sf::Vector2f pos);

	void setX(float x);
	void setY(float y);
	void addX(float x);
	void addY(float y);

	void setStatic(bool isStatic);
	bool isStatic() const;

	const sf::Vector2f& getPosition() const;
private:
	sf::Vector2f m_position;

	bool m_isStaticTransform;
}; // class Transform

}; // namespace dot