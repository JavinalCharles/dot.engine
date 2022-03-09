#include "dot/Window.hpp"

using dot::Window;

Window::Window()
	: m_window(sf::VideoMode(1024, 960), "Game Window", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);
}

Window::Window(sf::VideoMode mode, const std::string& title, sf::Uint32 style)
	: m_window(mode, title, style)
{
	m_window.setVerticalSyncEnabled(true);
}

void Window::update()
{
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Window::clear(sf::Color color)
{
	m_window.clear(color);
}

void Window::render(const sf::Drawable& drawable, const sf::Transform& transform)
{
	m_window.draw(drawable, transform);
}

void Window::render(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type)
{
	m_window.draw(vertices, vertexCount, type);
}

void Window::render(const sf::Drawable& drawable)
{
	m_window.draw(drawable);
}

void Window::display()
{
	m_window.display();
}

bool Window::isOpen() const
{
	return m_window.isOpen();
}

void Window::close()
{
	m_window.close();
}

sf::FloatRect Window::getViewSpace() const
{
	const sf::View& view = m_window.getView();
	const sf::Vector2f& viewCenter = view.getCenter();
	const sf::Vector2f& viewSize = view.getSize();

	sf::Vector2f viewSizeHalf(viewSize.x * 0.5f, viewSize.y * 0.5f);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);

	return viewSpace;
}

sf::Vector2u Window::getCentre() const
{
	sf::Vector2u size = m_window.getSize();

	return sf::Vector2u(size.x/2, size.y/2);
}

const sf::View& Window::getView() const
{
	return m_window.getView();
}

void Window::setView(const sf::View& view)
{
	m_window.setView(view);
}

const sf::RenderWindow& Window::getWindow() const
{
	return m_window;
}
