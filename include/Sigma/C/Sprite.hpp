#pragma once

#include "Sigma/C/Drawable.hpp"
#include "Sigma/C/Transform.hpp"
#include "Sigma/ResourceAllocator.hpp"

namespace Sigma
{
class Sprite : public Sigma::Drawable
{
	Sprite(Sigma::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);

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


	virtual void lateUpdate(float deltaTime) override;

	virtual void render(Window& window) override;

	void setTextureRect(int x, int y, int width, int height);
	void setTextureRect(const sf::IntRect& rect);
	void setScale(float x, float y);

	virtual bool continueToDraw() const override;
private:
	sf::Sprite m_sprite;

	unsigned m_currentTextureID;
};

}; // namespace Sigma