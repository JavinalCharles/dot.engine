#pragma once

#include <SFML/Graphics.hpp>
#include "dot/C/Component.hpp"
#include "dot/Window.hpp"

namespace dot
{

class Drawable : public dot::Component
{
public:
	Drawable(dot::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);
	virtual ~Drawable();
	
	virtual void render(dot::Window& window) = 0;

	void setSortOrder(unsigned order);
	unsigned getSortOrder() const;

	void setDrawLayer(unsigned drawLayer);
	unsigned getDrawLayer() const;

	virtual bool continueToDraw() const = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;
protected:
	unsigned m_sortOrder;

	unsigned m_layer;
}; // class Drawable

}; // namespace dot