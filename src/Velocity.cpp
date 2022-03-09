#include "dot/C/Velocity.hpp"
#include "dot/E/Entity.hpp"

using dot::Velocity;

Velocity::Velocity(dot::Entity* owner)
	: dot::Component(owner),
	m_maxVelocity(500.f, 500.f)
{

}

void Velocity::update(float deltaTime)
{
	m_owner->move(m_velocity * deltaTime);
}

void Velocity::lateUpdate(float deltaTime)
{
	// m_velocity.x = 0.f;
	// m_velocity.y = 0.f;
}

void Velocity::set(const sf::Vector2f& vel)
{
	m_velocity = vel;
	clampVelocity();
}

void Velocity::set(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
	clampVelocity();
}

void Velocity::setX(float x)
{
	m_velocity.x = x;
	clampVelocity();
}

void Velocity::setY(float y)
{
	m_velocity.y = y;
	clampVelocity();
}

const sf::Vector2f& Velocity::get() const
{
	return m_velocity;
}

void Velocity::clampVelocity()
{
	if (fabs(m_velocity.x) > m_maxVelocity.x)
	{
		if(m_velocity.x > 0)
		{
			m_velocity.x = m_maxVelocity.x;
		}
		else
		{
			m_velocity.x = -m_maxVelocity.x;
		}
	}

	if (fabs(m_velocity.y) > m_maxVelocity.y)
	{
		if (m_velocity.y > 0.f)
		{
			m_velocity.y = m_maxVelocity.y;
		}
		else
		{
			m_velocity.y = - m_maxVelocity.y;
		}
	}
}
