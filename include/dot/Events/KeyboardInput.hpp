#pragma once

#include <unordered_map>
#include <SFML/Window.hpp>
#include "dot/Utilities/Bitmask.hpp"

namespace dot
{

class KeyboardInput
{
public:
	KeyboardInput();

	void update();

	void bind(sf::Keyboard::Key key, unsigned code);

	void unbind(sf::Keyboard::Key key);
	
	bool isKeyPressed(unsigned keyCode);
	bool isKeyDown(unsigned keyCode);
	bool isKeyUp(unsigned keyCode);
private:
	std::unordered_map<sf::Keyboard::Key, unsigned> m_keyBinds;

	Bitmask m_thisFrameKeys;
	Bitmask m_lastFrameKeys;
}; // class KeyboardInput
}; // namespace dot
