#pragma once

#include "dot/C/Drawable.hpp"
#include "dot/ResourceAllocator.hpp"
#include "dot/C/BoxCollider.hpp"

namespace dot
{
class Sprite : public dot::Drawable
{
public:
	Sprite(dot::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);

	/**
	 * Sprite::load(filePath)
	 * - loads a texture from file
	 * */
	void load(const std::string& filePath);

	/**
	 * Sprite::load(id)
	 * - loads a texture from the id
	 * */
	void load(unsigned id);

	virtual void awake() override;

	virtual void lateUpdate(float deltaTime) override;

	virtual void render(Window& window) override;

	virtual void render(Window& window, const sf::Transform& transform) override;

	void setTextureRect(int x, int y, int width, int height);
	void setTextureRect(const sf::IntRect& rect);
	void setScale(float x, float y);

	void rotate(float angle);
	void setRotation(float angle);

	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f& factors);

	sf::IntRect getTextureRect() const;
	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const override;
	sf::Vector2f getScale() const;

	virtual bool continueToDraw() const override;
private:
	sf::Sprite m_sprite;

	unsigned m_currentTextureID;
};

}; // namespace dot
