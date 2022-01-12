#include "dot/C/Direction.hpp"
#include "dot/E/Entity.hpp"

using dot::Direction;
using dot::CardinalDirection;

Direction::Direction(dot::Entity* owner)
	: dot::Component(owner),
	m_currentDir(CardinalDirection::SOUTH)
{

}

void Direction::awake()
{
	m_velocity = m_owner->getComponent<dot::Velocity>();
}

CardinalDirection Direction::get()
{
	const sf::Vector2f& currentVel = m_velocity->get();

	if(currentVel.x != 0.f || currentVel.y != 0.f)
	{
		float velXAbs = fabs(currentVel.x);
		float velYAbs = fabs(currentVel.y);
		if (velXAbs > velYAbs)
		{
			m_currentDir = (currentVel.x < 0) ? CardinalDirection::WEST : CardinalDirection::EAST;
		}
		else
		{
			m_currentDir = (currentVel.y < 0) ? CardinalDirection::NORTH : CardinalDirection::SOUTH;
		}
	}
	
	return m_currentDir;
}