#include "dot/Events/KeyboardInput.hpp"

using dot::KeyboardInput;
using dot::Bitmask;

KeyboardInput::KeyboardInput()
	: m_keyBinds(),
	m_thisFrameKeys(),
	m_lastFrameKeys()
{

}

void KeyboardInput::update()
{
	m_lastFrameKeys.setMask(m_thisFrameKeys);
	m_thisFrameKeys.clear();

	for(const auto& keyBind: m_keyBinds)
	{
		if (sf::Keyboard::isKeyPressed(keyBind.first))
		{
			m_thisFrameKeys.setBit(keyBind.second);
		}
	}
}

void KeyboardInput::bind(sf::Keyboard::Key key, unsigned code)
{
	m_keyBinds.insert_or_assign(key, code);
}

void KeyboardInput::unbind(sf::Keyboard::Key key)
{
	m_keyBinds.erase(key);
}

bool KeyboardInput::isKeyPressed(unsigned keyCode)
{
	return m_thisFrameKeys.getBit(keyCode);
}

bool KeyboardInput::isKeyDown(unsigned keyCode)
{
	bool lastFrame = m_lastFrameKeys.getBit(keyCode);
	bool thisFrame = m_thisFrameKeys.getBit(keyCode);
	return thisFrame && !lastFrame;
}

bool KeyboardInput::isKeyUp(unsigned keyCode)
{
	bool lastFrame = m_lastFrameKeys.getBit(keyCode);
	bool thisFrame = m_thisFrameKeys.getBit(keyCode);
	return !thisFrame && lastFrame;
}