#pragma once

#include <memory>
#include <functional>
#include <map>
#include <vector>
#include "dot/C/Component.hpp"
#include "dot/Events/KeyboardInput.hpp"
#include "dot/C/Velocity.hpp"

namespace dot
{

using KeyAction = std::function<void(void)>;

class KeyboardControl : public dot::Component
{
public:
	KeyboardControl(dot::Entity* owner);
	void awake() override;

	void bindOnKeyPressed(unsigned keyCode, KeyAction keyaction);
	void bindOnKeyUp(unsigned keyCode, KeyAction keyAction);
	void bindOnKeyDown(unsigned keyCode, KeyAction keyAction);

	void update(float deltaTime) override;
	void lateUpdate(float deltaTime) override;

private:
	std::map<unsigned, std::vector<KeyAction>> m_keyPressedActions;
	std::map<unsigned, std::vector<KeyAction>> m_keyUpActions;
	std::map<unsigned, std::vector<KeyAction>> m_keyDownActions;
}; // class KeyboardControl

}; // namespace dot