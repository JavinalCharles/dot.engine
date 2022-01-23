#include "dot/Events/MouseInput.hpp"

using dot::MouseInput;

MouseInput::MouseInput()
	: m_mouseBinds(),
	m_thisFrameBits(),
	m_lastFrameBits()
{

}

void MouseInput::update()
{
	m_lastFrameBits.setMask(m_thisFrameBits);
	m_thisFrameBits.clear();

	for(const auto& mouseBind: m_mouseBinds)
	{
		if (sf::Mouse::isButtonPressed(mouseBind.first))
		{
			m_thisFrameBits.setBit(mouseBind.second);
		}
	}

}

void MouseInput::bind(sf::Mouse::Button btn, unsigned code)
{
	m_mouseBinds.insert_or_assign(btn, code);
}

void MouseInput::unbind(sf::Mouse::Button btn)
{
	m_mouseBinds.erase(btn);
}

bool MouseInput::isCodeActive(unsigned code)
{
	return m_thisFrameBits.getBit(code);
}

bool MouseInput::isCodeDown(unsigned code)
{
	bool lastFrame = m_lastFrameBits.getBit(code);
	bool thisFrame = m_thisFrameBits.getBit(code);
	return thisFrame && !lastFrame;
}

bool MouseInput::isCodeUp(unsigned code)
{
	bool lastFrame = m_lastFrameBits.getBit(code);
	bool thisFrame = m_thisFrameBits.getBit(code);
	return !thisFrame && lastFrame;
}

sf::Vector2i MouseInput::getPos(const sf::Window& window) const
{
	return sf::Mouse::getPosition(window);
}