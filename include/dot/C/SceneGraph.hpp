#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "dot/C/Drawable.hpp"
#include "dot/Window.hpp";

namespace dot
{

class SceneNode
{
public:
	SceneNode(dot::Entity* entity, SceneNode* parent = nullptr);

	~SceneNode();

	void render(Window& window, const sf::Transform& transform);

	void addChild(std::shared_ptr<dot::Entity> child);

	sf::FloatRect getGlobalBounds(const sf::Vector2f& currentPos) const;

	void clear();

private: // Helper Methods
	void clearChildren();

	void renderChildren(Window& window, const sf::Transform& transform);


	sf::FloatRect getGlobalBounds(const sf::FloatRect& currentRect) const;
private:
	dot::Entity* m_entity;
	SceneNode* m_parent;
	std::vector<std::shared_ptr<SceneNode>> m_children;
}; // class SceneNode

class SceneGraph : public dot::Drawable
{
public:
	SceneGraph(dot::Entity* owner, unsigned sortOrder = 0u, unsigned drawLayer = 0);

	virtual ~SceneGraph();

	void addChild(std::shared_ptr<dot::Entity> childEntity);

	virtual void lateUpdate(float deltaTime) override;

	virtual void render(dot::Window& window) override;
	virtual void render(dot::Window& window, const sf::Transform& transform) override;
	virtual sf::FloatRect getGlobalBounds() const;

	bool continueToDraw() const;
private:
	SceneNode m_node;
}; // class SceneGraph

}; // namespace dot
