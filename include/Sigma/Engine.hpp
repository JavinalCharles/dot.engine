#pragma once

#include <SFML/System.hpp>

#include "Sigma/Window.hpp"
#include "Sigma/Utilities/WorkingDirectory.hpp"
#include "Sigma/ResourceAllocator.hpp"
#include "Sigma/SceneManager.hpp"


namespace Sigma
{

class Engine
{
public:
	Engine();

	void run();

protected:

	void handleInputs();
	void update();
	void render();
	void lateUpdate();

	bool isRunning() const;
	void calculateDeltaTime();

	

protected:
	Sigma::Window m_window;
	Sigma::WorkingDirectory m_wd;

	Sigma::SceneManager m_sceneManager;
	Sigma::TextureAllocator m_textureAllocator;

	sf::Clock m_clock;
	float m_deltaTime;
}; // class Engine

}; // namespace Sigma