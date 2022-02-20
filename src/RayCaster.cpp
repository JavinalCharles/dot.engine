#include "dot/C/RayCaster.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"



using dot::RayCaster;

RayCaster::RayCaster(dot::Entity* owner, unsigned sortOrder, unsigned drawLayer)
	: dot::Drawable(owner, sortOrder, drawLayer),
	m_maxDistance(300.f),
	m_tileSize(64.f, 64.f),
	m_rayColor(sf::Color::Cyan)
{
	m_ray[0].color = m_rayColor;
	m_ray[1].color = m_rayColor;
}

RayCaster::~RayCaster()
{

}

void RayCaster::lateUpdate(float deltaTime)
{
	// Debug::log("RayCaster::lateUpdate()");
	// float angle = ((m_owner->transform->getRotation() + m_angleAdjustment) * PI / 180); // angle in radians
	// sf::Vector2f sPos = m_owner->transform->getPosition(); // startingPosition
	// sf::Vector2f ePos(sPos.x + (m_maxDistance*(cos(angle))), sPos.y + (m_maxDistance*(sin(angle)))); // ending position

	// float dx = ePos.x - sPos.x;
	// float dy = ePos.y - sPos.y;

	// Debug::log("sPos: (" + std::to_string(sPos.x) + ", " + std::to_string(sPos.y) + ")");
	// Debug::log("ePos: (" + std::to_string(ePos.x) + ", " + std::to_string(ePos.y) + ")");

	// Debug::log("delta: (" + std::to_string(dx) + ", " + std::to_string(dy) + ")");


	// sf::FloatRect currentCellBounds(static_cast<int>(sPos.x/m_tileSize.x)*m_tileSize.x, static_cast<int>(sPos.y/m_tileSize.y)*m_tileSize.y, m_tileSize.x, m_tileSize.y);

	// m_ray[0].position = sPos;
	// m_ray[1].position = ePos;


	// sf::Vector2i startingCell(sPos.x/m_tileSize.x, sPos.y/m_tileSize.y);
	// Debug::log("cell: (" + std::to_string(startingCell.x) + ", " + std::to_string(startingCell.y) + ")");

	// sf::Vector2i mapCheck(startingCell);

	// sf::Vector2f stepSize(sqrt(1 + (dy*dy)/(dx*dx)), sqrt(1 + ((dx*dx)/(dy*dy))));
	// Debug::log("stepSize: (" + std::to_string(stepSize.x) + ", " + std::to_string(stepSize.y) + ")");

	// sf::Vector2i step;
	
	// sf::Vector2f rayLength1D;

	// if (dx < 0)
	// {
	// 	step.x = -1;
	// 	rayLength1D.x = (sPos.x - static_cast<float>(mapCheck.x)) * stepSize.x;
	// }
	// else
	// {
	// 	step.x = 1;
	// 	rayLength1D.x = (static_cast<float>(mapCheck.x + 1) - sPos.x) * stepSize.x;
	// }

	// if (dy < 0)
	// {
	// 	step.y = -1;
	// 	rayLength1D.y = (sPos.y - static_cast<float>(mapCheck.y)) * stepSize.y;
	// }
	// else
	// {
	// 	step.y = 1;
	// 	rayLength1D.y = (static_cast<float>(mapCheck.y + 1) - sPos.y) * stepSize.y;
	// }

	// Debug::log("step: (" + std::to_string(step.x) + ", " + std::to_string(step.y) + ")");
	// Debug::log("rayLength1D: (" + std::to_string(rayLength1D.x) + ", " + std::to_string(rayLength1D.y) + ")");

	// Debug::renderRect(currentCellBounds);

	// bool endTileFound = false;
	// float fDistance = 0.0f;
	// while(!endTileFound && fDistance < m_maxDistance)
	// {
	// 	if(rayLength1D.x < rayLength1D.y)
	// 	{
	// 		mapCheck.x += step.x;
	// 		fDistance = rayLength1D.x;
	// 		rayLength1D.x += stepSize.x;
	// 	}
	// 	else
	// 	{
	// 		mapCheck.y += step.y;
	// 		fDistance = rayLength1D.y;
	// 		rayLength1D.y += stepSize.y;
	// 	}

	// 	currentCellBounds.left = mapCheck.x *m_tileSize.x;
	// 	currentCellBounds.top = mapCheck.y *m_tileSize.y;

	// 	Debug::renderRect(currentCellBounds, sf::Color::Yellow);
	// }

	// Debug::log("EXITING RayCaster::lateUpdate()");
}

void RayCaster::render(dot::Window& window)
{
	// window.render(m_ray, 2, sf::Lines);
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

bool RayCaster::continueToDraw() const
{
	return !m_owner->isQueuedForRemoval();
}

sf::FloatRect RayCaster::getGlobalBounds() const
{
	float left = m_ray[0].position.x < m_ray[1].position.x ? m_ray[0].position.x : m_ray[1].position.x;
	float top = m_ray[0].position.y < m_ray[1].position.y ? m_ray[0].position.y : m_ray[1].position.y;
	float width = abs(m_ray[0].position.x - m_ray[1].position.x);
	float height = abs(m_ray[0].position.y - m_ray[1].position.y);

	return sf::FloatRect(left, top, width, height);
}