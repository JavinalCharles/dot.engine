// #include "dot/S/LightSystem.hpp"

// using dot::LightSystem;

// LightSystem::LightSystem()
// 	: m_boundsTree(10, 10, 0, {0, 0, 4200, 4200}, nullptr)
// {

// }

// LightSystem::~LightSystem()
// {
// 	m_boundsTree.clear();
// }

// void LightSystem::add(std::vector<std::shared_ptr<dot::Entity>>& entities)
// {
// 	for (auto& e : entities)
// 	{
// 		auto bound = e->getComponent<dot::LightBounds>();
// 		if (bound != nullptr)
// 		{
// 			m_boundsTree.insert(bound);
// 		}
// 		else
// 		{
// 			auto rayCaster = e->getComponent<dot::RayCaster>();
// 			if(rayCaster != nullptr)
// 			{
// 				m_rayCasters.push_back(rayCaster);
// 			}
// 		}
// 	}
// }

// void LightSystem::processRemovals()
// {
// 	m_boundsTree.clearRemovedObjects();
// }

// void LightSystem::update()
// {
// 	for(auto& rayCaster : m_rayCasters)
// 	{
// 		cast(rayCaster->getOwner()->getPosition(), rayCaster->getTo());
// 	}
// }

// void LightSystem::cast(const sf::Vector2f& from, const sf::Vector2f& to, int exclusionID)
// {
// 	if (from == to)
// 		return;

// 	// Create a collision area
// 	sf::FloatRect collisionArea = buildRayBounds(from, to);
// 	// Debug::renderRect(collisionArea, sf::Color::Red);

// 	// Retrieve entities from the quadtree.
// 	std::vector<std::shared_ptr<dot::LightBounds>> bounds = m_boundsTree.search(collisionArea);

// 	if (bounds.size() < 1)
// 	{
// 		Debug::renderLine(from, to, sf::Color::White);
// 		return;
// 	}

// 	std::vector<sf::Vector2f> linePoints = buildLinePoints(from, to);

// 	for (auto& p : linePoints)
// 	{
// 		for(auto& b : bounds)
// 		{
// 			// if (exclusionID == b->getOwner()->instanceID->get())
// 				// return;

// 			sf::FloatRect lightBounds = b->getBounds();
// 			if (lightBounds.contains(p))
// 			{
// 				Debug::renderLine(from, p, sf::Color::White);
// 				return;
// 			}
// 		}
// 	}
// 	Debug::renderLine(from, to, sf::Color::White);
// }

// std::vector<sf::Vector2f> LightSystem::buildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to)
// {
// 	std::vector<sf::Vector2f> result;

// 	sf::Vector2f diff = to - from;
// 	int steps = 0;

// 	float absDiffX = abs(diff.x);
// 	float absDiffY = abs(diff.y);

// 	if (absDiffX > absDiffY)
// 	{
// 		steps = absDiffX;
// 	}
// 	else
// 	{
// 		steps = absDiffY;
// 	}

// 	float xStep = diff.x / static_cast<float>(steps);
// 	float yStep = diff.y / static_cast<float>(steps);

// 	float newX = from.x;
// 	float newY = from.y;

// 	for(int i = 0; i <= steps; ++i)
// 	{
// 		result.push_back(sf::Vector2f(newX, newY));
// 		newX += xStep;
// 		newY += yStep;
// 	}

// 	return result;
// }

// sf::FloatRect LightSystem::buildRayBounds(const sf::Vector2f& from, const sf::Vector2f& to)
// {
// 	return sf::FloatRect(
// 		((from.x < to.x) ? from.x : to.x),
// 		((from.y < to.y) ? from.y : to.y),
// 		fabs(from.x - to.x),
// 		fabs(from.y - to.y)
// 	);
// }
