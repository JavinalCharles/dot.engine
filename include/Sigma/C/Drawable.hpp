#pragma once

#include <SFML/Graphics.hpp>
#include "Sigma/C/Component.hpp"
#include "Sigma/Window.hpp"

namespace Sigma
{

class Drawable : public Sigma::Component
{
public:
	Drawable(Sigma::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);
	virtual ~Drawable();
	
	virtual void render(Sigma::Window& window) = 0;

	void setSortOrder(unsigned order);
	unsigned getSortOrder() const;

	void setDrawLayer(unsigned drawLayer);
	unsigned getDrawLayer() const;

	virtual bool continueToDraw() const = 0;
protected:
	unsigned m_sortOrder;

	unsigned m_layer;
}; // class Drawable

}; // namespace Sigma