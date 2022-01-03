#pragma once

#include "Sigma/C/Component.hpp"

namespace Sigma
{

using Sigma::Component;

class Transform : public Component
{
public:
	Transform(Sigma::Entity* owner);

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

}; // namespace Sigma