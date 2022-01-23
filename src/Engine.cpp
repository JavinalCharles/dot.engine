#include "dot/Engine.hpp"

using dot::Engine;

Engine::Engine()
	: m_sceneManager(),
	m_window(sf::VideoMode(1024, 860), "Titlebar"),
	m_clock(),
	m_deltaTime(m_clock.restart().asSeconds())
{

}

Engine::Engine(sf::VideoMode mode, const std::string& title)
	: m_sceneManager(),
	m_window(mode, title),
	m_clock(),
	m_deltaTime(m_clock.restart().asSeconds())
{
	
}

void Engine::run()
{
	do
	{
		this->handleInputs();
		if (m_window.isOpen())
		{
			this->update();
			this->lateUpdate();
			this->render();
			this->calculateDeltaTime();
		}
	}
	while(m_window.isOpen());
}

void Engine::handleInputs()
{
	m_window.update();
	m_sceneManager.handleInputs();
}

void Engine::update()
{
	m_sceneManager.update(m_deltaTime);
}

void Engine::lateUpdate()
{
	m_sceneManager.lateUpdate(m_deltaTime);
}

void Engine::render()
{
	m_window.clear();
	m_sceneManager.render(m_window);
	m_window.display();
}

void Engine::calculateDeltaTime()
{
	m_deltaTime = m_clock.restart().asSeconds();
}