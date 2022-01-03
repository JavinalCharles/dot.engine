#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Sigma
{

class Window
{
public:
	Window();
	Window(sf::VideoMode mode, const std::string& title = "Game Window", sf::Uint32 style = sf::Style::Default );

	void update();

	void clear(sf::Color color = sf::Color::Black);
	void render(const sf::Drawable& drawable);
	void render(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type);
	void display();

	bool isOpen() const;

	sf::Vector2u getCentre() const;

	sf::FloatRect getViewSpace() const;

	const sf::View& getView() const;
	void setView(const sf::View& view);

private:
	sf::RenderWindow m_window;

}; // class Window

}; // class Sigma