#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "dot/C/Component.hpp"
#include "dot/Window.hpp"

namespace dot
{

template<typename T>
class Quadtree;

class Drawable : public dot::Component, public std::enable_shared_from_this<dot::Drawable>
{
public:
	Drawable(dot::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);
	virtual ~Drawable();

	virtual void render(dot::Window& window) = 0;
	virtual void render(dot::Window& window, const sf::Transform& transform) = 0;

	void setSortOrder(unsigned order);
	unsigned getSortOrder() const;

	void setDrawLayer(unsigned drawLayer);
	unsigned getDrawLayer() const;

	virtual bool continueToDraw() const = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;
	virtual sf::FloatRect getBounds() const = 0;

	void updateTree();
	void setTree(Quadtree<dot::Drawable>* tree);
protected:
	unsigned m_sortOrder;

	unsigned m_layer;

	Quadtree<dot::Drawable>* m_containingTree;
}; // class Drawable

}; // namespace dot
