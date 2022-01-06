#include "dot/SceneManager.hpp"

using dot::SceneManager;

SceneManager::SceneManager()
	: m_scenes(0),
	m_currentScene(nullptr),
	m_insertedSceneID(0)
{

}

void SceneManager::handleInputs()
{
	if (m_currentScene)
	{
		m_currentScene->handleInputs();
	}
}

void SceneManager::update(float deltaTime)
{
	if (m_currentScene)
	{
		m_currentScene->update(deltaTime);
	}
}

void SceneManager::lateUpdate(float deltaTime)
{
	if (m_currentScene)
	{
		m_currentScene->lateUpdate(deltaTime);
	}
}

void SceneManager::render(Window& window)
{
	if (m_currentScene)
	{
		m_currentScene->render(window);
	}
}

unsigned int SceneManager::add(std::shared_ptr<Scene> scene)
{
	auto inserted = m_scenes.insert(std::make_pair(m_insertedSceneID++, scene));

	inserted.first->second->onCreate();

	return m_insertedSceneID-1;
}

void SceneManager::remove(unsigned int id)
{
	auto it = m_scenes.find(id);
	if (it != m_scenes.end())
	{
		if (m_currentScene == it->second)
		{
			m_currentScene = nullptr;
		}

		it->second->onDestroy();

		m_scenes.erase(it);
	}
}

void SceneManager::switchTo(unsigned int id)
{
	auto it = m_scenes.find(id);
	if (it != m_scenes.end())
	{
		if (m_currentScene)
		{
			// If we have a current scene, we call its onDeactivate method
			m_currentScene->onDeactivate();
		}
		// Setting the current scene ensures that it is updated and drawn
		m_currentScene = it->second;
		m_currentScene->onActivate();
	}
}