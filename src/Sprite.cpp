#include "dot/C/Sprite.hpp"
#include "dot/E/Entity.hpp"

using dot::Drawable;
using dot::Sprite;
using dot::Entity;

Sprite::Sprite(Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: Drawable(owner, sortOrder, drawLayer),
	m_currentTextureID(0)
{
}

void Sprite::awake()
{
	m_sprite.setPosition(m_owner->getPosition());
	m_sprite.setRotation(m_owner->getRotation());
}

void Sprite::load(const std::string& filePath)
{
	unsigned textureID = m_owner->context->textures->add(filePath);
	if (textureID > 0)
	{
		m_currentTextureID = textureID;
		std::shared_ptr<sf::Texture> texture = m_owner->context->textures->get(textureID);
		m_sprite.setTexture(*texture);
	}
}

void Sprite::load(unsigned id)
{
	if (id > 0 && id != m_currentTextureID)
	{
		// std::cout << "Getting Textures from ID " << id << std::endl;
		if (m_owner->context->textures->has(id))
		{
			m_currentTextureID = id;
			std::shared_ptr<sf::Texture> texture = m_owner->context->textures->get(id);
			m_sprite.setTexture(*texture);
			// std::cout << "Texture set: " << id << std::endl;
		}
	}
}

void Sprite::setColor(sf::Color color)
{
	m_sprite.setColor(color);
}

void Sprite::setTextureRect(int x, int y, int width, int height)
{
	m_sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void Sprite::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
}

void Sprite::rotate(float angle)
{
	m_sprite.rotate(angle);
}

void Sprite::setRotation(float angle)
{
	m_sprite.setRotation(angle);
}

void Sprite::lateUpdate(float deltaTime)
{
	sf::Vector2f pos = m_owner->getPosition();
	float rotation = m_owner->getRotation();

	m_sprite.setPosition(pos);
	m_sprite.setRotation(rotation);
}

void Sprite::render(Window& window)
{
	window.render(m_sprite);
}

void Sprite::render(Window& window, const sf::Transform& transform)
{
	sf::Transform combinedTransform = transform * m_owner->getTransform();
	window.render(m_sprite, combinedTransform);
}

void Sprite::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

bool Sprite::continueToDraw() const
{
	return !m_owner->isQueuedForRemoval();
}

void Sprite::setOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);
}

void Sprite::setOrigin(const sf::Vector2f& factor)
{
	m_sprite.setOrigin(factor);
}

sf::Color Sprite::getColor() const
{
	return m_sprite.getColor();
}

sf::IntRect Sprite::getTextureRect() const
{
	return m_sprite.getTextureRect();
}

sf::FloatRect Sprite::getLocalBounds() const
{
	return m_sprite.getLocalBounds();
}

sf::FloatRect Sprite::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::FloatRect Sprite::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Sprite::getScale() const
{
	return m_sprite.getScale();
}
