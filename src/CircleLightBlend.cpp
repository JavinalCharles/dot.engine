#include "dot/C/CircleLightBlend.hpp"
#include "dot/E/Entity.hpp"
#include "gmath/gmath.hpp"

using dot::CircleLightBlend;

CircleLightBlend::CircleLightBlend(dot::Entity* owner)
	: dot::LightBlend(owner),
	m_circle(456.f, 360)
{

}

void CircleLightBlend::awake()
{
	sf::Image image;
	image.create(912.f, 912.f, sf::Color::White);
	sf::Vector2f origin(456.f, 456.f);
	float magnitude = gmath::hypot(sf::Vector2f(0, 0), origin);
	for(int x = 0; x < 912; ++x) {
		for (int y = 0; y < 912; ++y) {
			float dist = gmath::hypot(sf::Vector2f(x, y), origin);
			uint8_t alpha = (1 - (dist / magnitude)) * 255;
			image.setPixel(x, y, sf::Color(255, 255, 255, alpha));
		}
	}

	sf::Texture circleTexture;
	circleTexture.loadFromImage(image);

	unsigned textureId = getOwner()->context->textures->add(circleTexture);

	m_circle.setTexture(getOwner()->context->textures->get(textureId).get());
	m_circle.setOrigin(origin);
	m_circle.setPosition(m_owner->getPosition());
}

void CircleLightBlend::lateUpdate(float deltaTime)
{
	m_circle.setPosition(m_owner->getPosition());
}

void CircleLightBlend::render(dot::Window& window)
{
	window.render(m_circle, sf::BlendAdd);
}