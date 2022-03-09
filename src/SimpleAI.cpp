#include "dot/C/SimpleAI.hpp"
#include "dot/E/Entity.hpp"

using dot::SimpleAI;

SimpleAI::SimpleAI(dot::Entity* owner)
	: dot::Component(owner),
	m_currentState(0u)
{

}

void SimpleAI::update(float deltaTime)
{
	// If currentState is 0, return.
	if(!m_currentState)
		return;

	m_behaviors.at(m_currentState)(deltaTime);
}

void SimpleAI::addBehavior(unsigned state, std::function<void(float)> newBehavior)
{
	m_behaviors.insert_or_assign(state, newBehavior);
	if(!m_currentState)
		m_currentState = state;
}

void SimpleAI::setState(unsigned state)
{
	m_currentState = state;
}