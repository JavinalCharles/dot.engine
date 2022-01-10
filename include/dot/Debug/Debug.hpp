#pragma once

#include <array>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "dot/Window.hpp"
#include "dot/Events/KeyboardInput.hpp"

using dot::Window;
using dot::KeyboardInput;


class Debug
{
public:
	static void render(Window& window);
	static void renderRect(const sf::FloatRect& rect, sf::Color colour = sf::Color::White);
	static void renderLine(const sf::Vector2f& from, const sf::Vector2f& to, sf::Color colour = sf::Color::White);
	static void log(const std::string& msg);
	static void logWarning(const std::string& msg);
	static void logError(const std::string& msg);

	static void handleCameraZoom(Window& window, KeyboardInput& input);
private:
	static std::vector<std::array<sf::Vertex, 2>> lines;
	static std::vector<sf::RectangleShape> rects;
}; // class Debug
