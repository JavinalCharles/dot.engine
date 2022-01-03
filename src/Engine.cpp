#include "Sigma/Engine.hpp"

using namespace Sigma;

Engine::Engine()
	: m_sceneManager(),
	m_window(sf::VideoMode(1024, 860), "Bowman"),
	m_clock(),
	m_deltaTime(m_clock.restart().asSeconds())
{

}

void Engine::run()
{
	while(m_window.isOpen())
	{
		this->handleInputs();
		this->update();
		this->lateUpdate();
		this->render();
		this->calculateDeltaTime();
	}
}

void Engine::handleInputs()
{

}

void Engine::update()
{
	m_window.update();
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