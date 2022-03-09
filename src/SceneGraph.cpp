#include "dot/C/SceneGraph.hpp"
#include "dot/E/Entity.hpp"

using dot::SceneNode;
using dot::SceneGraph;

SceneNode::SceneNode(std::shared_ptr<dot::Entity> entity, SceneNode* parent)
	: m_entity(entity),
	m_parent(parent)
{
}

void SceneNode::render(Window& window)
{
	sf::Transform transform = m_entity->getTransform();
	auto drawable = m_entity->getDrawable();
	if (drawable != nullptr)
		drawable->render(window, transform);

	this->renderChildren(window, transform);
}

void SceneNode::render(Window& window, const sf::Transform& transform)
{
	sf::Transform combinedTransform = transform * m_entity->getTransform();
	auto drawable = m_entity->getDrawable();
	if(drawable != nullptr)
		drawable->render(window, combinedTransform);

	this->renderChildren(window, combinedTransform);
}

void SceneNode::addChild(std::shared_ptr<dot::Entity> childEntity)
{
	m_children.push_back(std::make_shared<SceneNode>(childEntity, this));
}

sf::FloatRect SceneNode::getGlobalBounds() const
{
	sf::FloatRect rect(m_entity->getPosition(), sf::Vector2f(1.f,1.f));
	for (auto& child: m_children)
	{
		rect = child->getGlobalBounds(rect);
	}
	return rect;
}

void SceneNode::renderChildren(dot::Window& window, const sf::Transform& transform)
{
	for(auto& child: m_children)
	{
		child->render(window, transform);
	}
}

sf::FloatRect SceneNode::getGlobalBounds(const sf::FloatRect& currentRect) const
{
	sf::FloatRect resRect(currentRect);
	auto drawable = m_entity->getDrawable();
	if (drawable != nullptr)
	{
		sf::FloatRect rect2(drawable->getGlobalBounds());
		float left = (currentRect.left < rect2.left) ? currentRect.left : rect2.left;
		float top = (currentRect.top < rect2.top) ? currentRect.top : rect2.top;
		sf::Vector2f p1(currentRect.left+currentRect.width, currentRect.top+currentRect.width);
		sf::Vector2f p2(rect2.left+rect2.width, rect2.top+rect2.width);
		float width = left - (p1.x > p2.x ? p1.x : p2.x );
		float height = top - (p1.y > p2.y ? p1.y : p2.y );

		resRect.left = left;
		resRect.top = top;
		resRect.width = width;
		resRect.height = height;
	}

	for (auto& child: m_children)
	{
		resRect = child->getGlobalBounds(resRect);
	}

	return resRect;
}

/********************
* SceneGraph
*********************/
SceneGraph::SceneGraph(dot::Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: dot::Drawable(owner, sortOrder, drawLayer),
	m_node(std::shared_ptr<dot::Entity>(owner))
{

}

void SceneGraph::render(Window& window)
{
	m_node.render(window);
}

void SceneGraph::render(Window& window, const sf::Transform& transform)
{
	m_node.render(window, transform);
}

void SceneGraph::addChild(std::shared_ptr<dot::Entity> childEntity)
{
	m_node.addChild(childEntity);
}

sf::FloatRect SceneGraph::getGlobalBounds() const
{
	return m_node.getGlobalBounds();
}
