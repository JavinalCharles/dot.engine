#pragma once

#include <memory>
#include <unordered_map>
#include "Sigma/Scene.hpp"
#include "Sigma/Window.hpp"

namespace Sigma
{

class SceneManager
{
public:
	SceneManager();

	void handleInputs();
	void update(float deltaTime);
	void lateUpdate(float deltaTime);
	void render(Window& window);

	/**
	 * SceneManager::add() 
	 * - adds a scene to the SceneManager and
	 * returns the id of that mscene
	 * */
	unsigned int add(std::shared_ptr<Scene> scene);

	/**
	 * SceneManager::switchTo()
	 * - Transitions to scene with specified id
	 * */
	void switchTo(unsigned int id);

	/**
	 * SceneManager::remove()
	 * - Removes scene from the SceneManager
	 * */
	void remove(unsigned int id);

private:
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> m_scenes;
	std::shared_ptr<Scene> m_currentScene;

	unsigned int insertedSceneID;
}; // class SceneManager
}; // namespace Sigma