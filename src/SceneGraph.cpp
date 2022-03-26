#include "dot/C/SceneGraph.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"

using dot::SceneNode;
using dot::SceneGraph;

SceneNode::SceneNode(dot::Entity* entity, SceneNode* parent)
	: m_entity(entity),
	m_parent(parent)
{
}


SceneNode::~SceneNode()
{
	this->clear();
}

void SceneNode::render(Window& window, const sf::Transform& transform)
{
	// DO NOT RENDER ON ROOT BRANCH
	if(m_parent != nullptr)
	{
		sf::Transform combinedTransform = transform *
		m_entity->getTransform();
		auto drawable = m_entity->getDrawable();
		if(drawable != nullptr)
		{
			drawable->render(window, combinedTransform);
		}

		this->renderChildren(window, combinedTransform);
	}
	else
	{
		this->renderChildren(window, transform);
	}
}

void SceneNode::renderChildren(dot::Window& window, const sf::Transform& transform)
{
	for(auto& child: m_children)
	{
		child->render(window, transform);
	}
}

void SceneNode::addChild(std::shared_ptr<dot::Entity> child)
{
	m_children.push_back(std::make_shared<SceneNode>(child.get(), this));
}

sf::FloatRect SceneNode::getGlobalBounds(const sf::Vector2f& currentPos) const
{
	// TODO: Properly measure GlobalBounds


	sf::FloatRect rect(currentPos, sf::Vector2f(1.f, 1.f));
	// for (auto& child: m_children)
	// {
	// 	rect = child->getGlobalBounds(rect);
	// }
	return rect;
}



sf::FloatRect SceneNode::getGlobalBounds(const sf::FloatRect& currentRect) const
{
	// TODO: Properly measure GlobalBounds

	return currentRect;
}

void SceneNode::clear()
{
	clearChildren();
	m_entity = nullptr;
}

void SceneNode::clearChildren()
{
	for(auto& child: m_children)
	{
		child->clear();
	}
	m_children.clear();
}

/********************
* SceneGraph
*********************/
SceneGraph::SceneGraph(dot::Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: dot::Drawable(owner, sortOrder, drawLayer),
	m_node(owner, nullptr)
{

}

SceneGraph::~SceneGraph()
{
	m_node.clear();
}

void SceneGraph::render(Window& window)
{
	m_node.render(window, m_owner->getTransform());
}

void SceneGraph::render(Window& window, const sf::Transform& transform)
{
	m_node.render(window, transform);
}

void SceneGraph::lateUpdate(float deltaTime)
{
	if(!continueToDraw())
	{
		Debug::log("SceneGraph::lateUpdate() - object: " + std::to_string(m_owner->instanceID->get()) + " being cleared");
		m_node.clear();
	}
}
void SceneGraph::addChild(std::shared_ptr<dot::Entity> childEntity)
{
	m_node.addChild(childEntity);
}

sf::FloatRect SceneGraph::getGlobalBounds() const
{
	sf::FloatRect rect(m_owner->getPosition(), sf::Vector2f(1.f, 1.f));
	Debug::renderRect(rect);
	return rect;
}

bool SceneGraph::continueToDraw() const
{
	return !m_owner->isQueuedForRemoval();
}
