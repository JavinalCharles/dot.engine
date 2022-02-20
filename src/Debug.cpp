#include "dot/Debug/Debug.hpp"

std::vector<sf::RectangleShape> Debug::rects = {};
std::vector<std::array<sf::Vertex, 2>> Debug::lines = {};
std::vector<sf::Vertex> Debug::points = {};

void Debug::render(Window& window)
{
	for (auto& r : rects)
	{
		window.render(r);
	}
	rects.clear();
	for (auto& l : lines)
	{
		sf::Vertex line[2] = {l.at(0), l.at(1)};
		window.render(line, 2, sf::Lines);
	}
	lines.clear();

	if (points.size() > 0)
	{
		sf::Vertex allPoints[points.size()];
		for (int i = 0; i < points.size(); ++i)
		{
			allPoints[i] = points[i];
		}
		window.render(allPoints, points.size(), sf::Points);
	}
	points.clear();

}


void Debug::renderRect(const sf::FloatRect& rect, sf::Color colour)
{
	sf::Vector2f size(rect.width, rect.height);
	sf::Vector2f pos(rect.left, rect.top);
	sf::RectangleShape shape(size);
	shape.setPosition(pos);
	shape.setOutlineColor(colour);
	shape.setOutlineThickness(3.f);
	shape.setFillColor(sf::Color::Transparent);
	rects.push_back(shape);
}

void Debug::renderLine(const sf::Vector2f& from, const sf::Vector2f& to, sf::Color colour)
{
	lines.push_back({sf::Vertex(from, colour), sf::Vertex(to, colour)});
}

void Debug::renderPoint(const sf::Vector2f& point, sf::Color colour)
{
	points.push_back(sf::Vertex(point, colour));
}

void Debug::log(const std::string& msg)
{
	std::cout << msg << std::endl;
}

void Debug::logWarning(const std::string& msg)
{
	std::cout << "WARNING: " << msg << std::endl;
}

void Debug::logError(const std::string& msg)
{
	std::cout << "ERROR: " << msg << std::endl;
}

void Debug::handleCameraZoom(Window& window, KeyboardInput& input)
{
	// if (input.isKeyUp(Input::Key::LBRACKET))
	// {
	// 	sf::View view = window.getView();
	// 	view.zoom(1.1f);
	// 	window.setView(view);
	// }
	// else if (input.isKeyUp(Input::Key::RBRACKET))
	// {
	// 	sf::View view = window.getView();
	// 	view.zoom(0.9f);
	// 	window.setView(view);
	// }
}