#pragma once

#include <functional>
#include <memory>
#include <map>
#include <vector>
#include "dot/C/Component.hpp"
#include "dot/Events/MouseInput.hpp"

namespace dot
{

using MouseAction = std::function<void(void)>;

class MouseControl : public dot::Component
{
public:
	MouseControl(dot::Entity* owner);
	void awake() override;

	void bindOnButtonPressed(unsigned keyCode, MouseAction action);
	void bindOnButtonUp(unsigned keyCode, MouseAction action);
	void bindOnButtonDown(unsigned keyCode, MouseAction action);

	void update(float deltaTime) override;
	void lateUpdate(float deltaTime) override;

	sf::Vector2i getPosition() const;

private:
	std::map<unsigned, std::vector<MouseAction>> m_btnPressedActions;
	std::map<unsigned, std::vector<MouseAction>> m_btnUpActions;
	std::map<unsigned, std::vector<MouseAction>> m_btnDownActions;
}; // class MouseControl


}; // namespace dot