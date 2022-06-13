#pragma once

#include <SFML/Graphics.hpp>
#include "dot/C/LightBlend.hpp"

namespace dot
{
class CircleLightBlend : public dot::LightBlend
{
public:
	CircleLightBlend(dot::Entity* owner);

	virtual void awake() override;

	virtual void lateUpdate(float deltaTime) override;

	virtual void render(dot::Window& window) override;

	virtual bool reaches(const sf::FloatRect& rect) const override;
private:
	sf::CircleShape m_circle;

}; // class CircleLightBlend


}; // namespace dot