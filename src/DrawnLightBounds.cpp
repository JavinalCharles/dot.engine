#include "dot/C/DrawnLightBounds.hpp"
#include "dot/E/Entity.hpp"

using dot::DrawnLightBounds;

DrawnLightBounds::DrawnLightBounds(dot::Entity* owner)
	: dot::LightBounds(owner)
{

}

void DrawnLightBounds::awake()
{
	m_drawable = m_owner->getDrawable();
}

sf::FloatRect DrawnLightBounds::getBounds()
{
	return m_drawable->getGlobalBounds();
}