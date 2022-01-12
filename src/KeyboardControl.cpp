#include "dot/C/KeyboardControl.hpp"
#include "dot/E/Entity.hpp"
#include <iostream>

using dot::KeyboardInput;
using dot::KeyboardControl;
using dot::KeyAction;

KeyboardControl::KeyboardControl(dot::Entity* owner)
	: dot::Component(owner)
{

}

void KeyboardControl::awake()
{

}

void KeyboardControl::update(float deltaTime)
{
	KeyboardInput* input = m_owner->context->keyInput;

	for (auto& keyBind : m_keyPressedActions)
	{
		if (input->isCodeActive(keyBind.first))
		{
			// std::cout << "Found an active code: " <<keyBind.first << std::endl;
			for (auto& f : keyBind.second)
			{
				f();
			}
		}
	}
	for (auto& keyBind : m_keyDownActions)
	{
		if (input->isCodeDown(keyBind.first))
		{
			for (auto& f : keyBind.second)
			{
				f();
			}
		}
	}
	for (auto& keyBind : m_keyUpActions)
	{
		if (input->isCodeUp(keyBind.first))
		{
			for (auto& f : keyBind.second)
			{
				f();
			}
		}
	}
}

void KeyboardControl::lateUpdate(float deltaTime)
{

}

void KeyboardControl::bindOnKeyPressed(unsigned keyCode, KeyAction action)
{
	auto actionList = m_keyPressedActions.find(keyCode);
	if (actionList == m_keyPressedActions.end())
	{
		m_keyPressedActions.insert(std::make_pair(keyCode, std::vector<KeyAction>{action}));

	}
	else
	{
		actionList->second.emplace_back(action);
	}
	std::cout << "KeyboardControl::bindOnKeyPressed()" << keyCode << std::endl;
}

void KeyboardControl::bindOnKeyUp(unsigned keyCode, KeyAction action)
{
	auto actionList = m_keyUpActions.find(keyCode);
	if (actionList == m_keyUpActions.end())
	{
		m_keyUpActions.insert(std::make_pair(keyCode, std::vector<KeyAction>{action}));
	}
	else
	{
		actionList->second.emplace_back(action);
	}
}

void KeyboardControl::bindOnKeyDown(unsigned keyCode, KeyAction action)
{
	auto actionList = m_keyDownActions.find(keyCode);
	if (actionList == m_keyDownActions.end())
	{
		m_keyDownActions.insert(std::make_pair(keyCode, std::vector<KeyAction>{action}));
	}
	else
	{
		actionList->second.emplace_back(action);
	}
}