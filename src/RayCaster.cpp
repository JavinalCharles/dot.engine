#include "dot/C/RayCaster.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"



using dot::RayCaster;

RayCaster::RayCaster(dot::Entity* owner)
	: dot::Component(owner),
	m_maxDistance(300.f),
	m_tileSize(64.f, 64.f),
	m_rayColor(sf::Color::Cyan)
{
}

RayCaster::~RayCaster()
{

}


void RayCaster::setMaxDistance(float maxDistance)
{
	m_maxDistance = maxDistance;
}

void RayCaster::setTileSize(const sf::Vector2f& size)
{
	m_tileSize = size;
}

void RayCaster::setTileSize(float width, float height)
{
	m_tileSize.x = width;
	m_tileSize.y = height;
}

void RayCaster::setAngleAdjustment(float adjustment)
{
	m_angleAdjustment = adjustment;
}

float RayCaster::getMaxDistance() const
{
	return m_maxDistance;
}

const sf::Vector2f& RayCaster::getTileSize() const
{
	return m_tileSize;
}

void RayCaster::setTo(const sf::Vector2f& to)
{
	m_to = to;
}

const sf::Vector2f& RayCaster::getTo() const
{
	return m_to;
}