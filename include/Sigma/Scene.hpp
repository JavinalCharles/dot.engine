#pragma once
#include "Window.hpp"

namespace Sigma
{

class Scene
{

public:
	/**
	 * Scene::onCreate()
	 * - Called when scene initially created.
	 * Called once.
	 * */
	virtual void onCreate() = 0;

	/**
	 * Scene::onDestroy()
	 * - Called when scene is destroyed. Called
	 * at most, once. If a scene was never removed
	 * from the game, this will never be called.
	 * */
	virtual void onDestroy() = 0;

	/**
	 * Scene::onActivate()
	 * - Called whenever a transition into a scene
	 * occurs. Can be called many times.
	 * */
	virtual void onActivate();
	
	/**
	 * Scene::onDeactivate()
	 * - Called whenever a transition out of a
	 * scene occurs. Can be called many times.
	 * */
	virtual void onDeactivate();

	virtual void handleInputs();
	virtual void update(float deltaTime);
	virtual void lateUpdate(float deltaTime);
	virtual void render(Window& window) = 0;
}; // class Scene

}; // namespace Sigma