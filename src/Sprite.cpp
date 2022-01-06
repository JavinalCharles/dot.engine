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

void Sprite::setTextureRect(int x, int y, int width, int height)
{
	m_sprite.setTextureRect(sf::IntRect(x, y, width, height));
}

void Sprite::setTextureRect(const sf::IntRect& rect)
{
	m_sprite.setTextureRect(rect);
}

void Sprite::lateUpdate(float deltaTime)
{
	sf::Vector2f pos = m_owner->transform->getPosition();
	const sf::IntRect& spriteBounds = m_sprite.getTextureRect();
	const sf::Vector2f& spriteScale = m_sprite.getScale();

	m_sprite.setPosition(pos.x - ((abs(spriteBounds.width) * 0.5f) * spriteScale.x), pos.y - ((abs(spriteBounds.height) * 0.5f) * spriteScale.y));
}

void Sprite::render(Window& window)
{
	window.render(m_sprite);
}

void Sprite::setScale(float x, float y)
{
	m_sprite.setScale(x, y);
}

bool Sprite::continueToDraw() const
{
	return !m_owner->isQueuedForRemoval();
}