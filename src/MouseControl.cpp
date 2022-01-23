#include "dot/C/MouseControl.hpp"
#include "dot/E/Entity.hpp"
#include <SFML/Window.hpp>

using dot::MouseControl;
using dot::MouseInput;
using dot::Entity;
using dot::Component;

MouseControl::MouseControl(Entity* owner)
	: Component(owner)
{

}

void MouseControl::awake()
{

}

void MouseControl::update(float deltaTime)
{
	MouseInput* input = m_owner->context->mouseInput;

	for (auto& btnBind : m_btnPressedActions)
	{
		if (input->isCodeActive(btnBind.first))
		{
			for (auto& f : btnBind.second)
			{
				f();
			}
		}
	}

	for (auto& btnBind : m_btnUpActions)
	{
		if (input->isCodeUp(btnBind.first))
		{;
			for (auto& f : btnBind.second)
			{
				f();
			}
		}
	}

	for (auto& btnBind : m_btnDownActions)
	{
		if (input->isCodeDown(btnBind.first))
		{
			for (auto& f : btnBind.second)
			{
				f();
			}
		}
	}
}

void MouseControl::lateUpdate(float deltaTime)
{

}

void MouseControl::bindOnButtonPressed(unsigned code, MouseAction action)
{
	auto actionList = m_btnPressedActions.find(code);
	if (actionList == m_btnPressedActions.end())
	{
		m_btnPressedActions.insert(std::make_pair(code, std::vector<MouseAction>{action}));

	}
	else
	{
		actionList->second.emplace_back(action);
	}
}

void MouseControl::bindOnButtonUp(unsigned code, MouseAction action)
{
	auto actionList = m_btnUpActions.find(code);
	if (actionList == m_btnUpActions.end())
	{
		m_btnUpActions.insert(std::make_pair(code, std::vector<MouseAction>{action}));
	}
	else
	{
		actionList->second.emplace_back(action);
	}
}

void MouseControl::bindOnButtonDown(unsigned code, MouseAction action)
{
	auto actionList = m_btnDownActions.find(code);
	if (actionList == m_btnDownActions.end())
	{
		m_btnDownActions.insert(std::make_pair(code, std::vector<MouseAction>{action}));

	}
	else
	{
		actionList->second.emplace_back(action);
	}
}

sf::Vector2i MouseControl::getPosition() const
{
	return sf::Mouse::getPosition(m_owner->context->window->getWindow());
}