#pragma once

#include <unordered_map>
#include <functional>
#include "dot/C/Component.hpp"
#include "dot/Utilities/EnumClassHash.hpp"

namespace dot
{

// struct AIState
// {
// 	unsigned code; // State's unique code
// 	std::function<void(void)> do;
// };

class SimpleAI : public dot::Component
{
public:
	SimpleAI(dot::Entity* owner);

	virtual void update(float deltaTime) override;

	void addBehavior(unsigned code, std::function<void(float)> newBehavior);
	void setState(unsigned newState);

private:
	unsigned m_currentState;
	std::unordered_map<unsigned, std::function<void(float)>, EnumClassHash> m_behaviors;

}; // class SimpleAI

}; // namespace dot