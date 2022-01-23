#pragma once

#include <unordered_map>
#include <SFML/Window.hpp>
#include "dot/Utilities/Bitmask.hpp"

namespace dot
{
class MouseInput
{
public:
	MouseInput();

	void update();

	void bind(sf::Mouse::Button btn, unsigned code);

	void unbind(sf::Mouse::Button btn);
	
	bool isCodeActive(unsigned code);
	bool isCodeDown(unsigned code);
	bool isCodeUp(unsigned code);

	sf::Vector2i getPos(const sf::Window& window) const;

private:
	std::unordered_map<sf::Mouse::Button, unsigned> m_mouseBinds;

	Bitmask m_thisFrameBits;
	Bitmask m_lastFrameBits;

}; // class MouseInput
}; // namespace dot

