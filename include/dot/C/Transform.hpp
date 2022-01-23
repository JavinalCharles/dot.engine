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
	sf::Vector2f getPosition() const;

	void setX(float x);
	void setY(float y);
	void addX(float x);
	void addY(float y);

	void setRotation(float angle);
	void rotate(float angle);
	float getRotation();

	void setOffset(const sf::Vector2f& offset);
	sf::Vector2f getOffset() const;

	void setStatic(bool isStatic);
	bool isStatic() const;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_offset;
	float m_rotation;



	bool m_isStaticTransform;
}; // class Transform

}; // namespace dot