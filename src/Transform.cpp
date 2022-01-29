#include "dot/C/Transform.hpp"

using dot::Transform;
using dot::Entity;

Transform::Transform(Entity* owner)
	: Component(owner),
	m_position(0.f, 0.f),
	m_offset(0.f, 0.f),
	m_rotation(0.f),
	m_isStaticTransform(false)
{

}

void Transform::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Transform::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
}

void Transform::addPosition(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
}

void Transform::addPosition(sf::Vector2f pos)
{
	m_position += pos;
}

void Transform::setX(float x)
{
	m_position.x = x;
}

void Transform::setY(float y)
{
	m_position.y = y;
}

void Transform::addX(float x)
{
	m_position.x += x;
}

void Transform::addY(float y)
{
	m_position.y += y;
}

void Transform::setRotation(float angle)
{
	m_rotation = angle;
}

void Transform::rotate(float angle)
{
	m_rotation += angle;
}

float Transform::getRotation()
{
	return m_rotation;
}

void Transform::setOffset(const sf::Vector2f& offset)
{
	m_offset = offset;
}

sf::Vector2f Transform::getOffset() const
{
	return m_offset;
}

void Transform::setStatic(bool isStatic)
{
	m_isStaticTransform = isStatic;
}

bool Transform::isStatic() const
{
	return m_isStaticTransform;
}

const sf::Vector2f& Transform::getPosition() const
{
	return m_position;
}
