#pragma once

#include <SFML/System.hpp>

#include "dot/Window.hpp"
#include "dot/Utilities/WorkingDirectory.hpp"
#include "dot/ResourceAllocator.hpp"
#include "dot/SceneManager.hpp"


namespace dot
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
	dot::Window m_window;
	dot::WorkingDirectory m_wd;

	dot::SceneManager m_sceneManager;
	dot::TextureAllocator m_textureAllocator;

	sf::Clock m_clock;
	float m_deltaTime;
}; // class Engine

}; // namespace dot