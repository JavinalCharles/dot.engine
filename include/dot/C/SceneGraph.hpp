#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "dot/C/Drawable.hpp"
#include "dot/Window.hpp"

class dot::Entity;

namespace dot
{

class SceneNode
{
public:
	SceneNode(std::shared_ptr<dot::Entity> entity, SceneNode* parent = nullptr);

	void render(Window& window);
	void render(Window& window, const sf::Transform& transform);

	void addChild(std::shared_ptr<dot::Entity> childEntity);

	sf::FloatRect getGlobalBounds() const;

private: // Helper Methods
	void renderChildren(Window& window, const sf::Transform& transform);
	sf::FloatRect getGlobalBounds(const sf::FloatRect& currentRect) const;
private:
	std::shared_ptr<dot::Entity> m_entity;
	SceneNode* m_parent;
	std::vector<std::shared_ptr<SceneNode>> m_children;
};

class SceneGraph : public dot::Drawable
{
public:
	SceneGraph(dot::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0u);

	void addChild(std::shared_ptr<dot::Entity> childEntity);

	virtual void render(dot::Window& window) override;
	virtual void render(dot::Window& window, const sf::Transform& transform) override;
	virtual sf::FloatRect getGlobalBounds() const;
private:
	SceneNode m_node;
}; // class SceneGraph

}; // namespace dot
