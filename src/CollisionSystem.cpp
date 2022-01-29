#include "dot/S/CollisionSystem.hpp"
#include "dot/Debug/Debug.hpp"


using dot::CollisionSystem;

CollisionSystem::CollisionSystem()
	: m_collisionTree(10, 10, 0, {0, 0, 4200, 2048}, nullptr)
{

}

CollisionSystem::~CollisionSystem()
{
	Debug::log("CollisionSystem::~CollisionSystem() entered");
	m_collisionTree.clear();
	m_objectsColliding.clear();
	m_collidables.clear();
	m_collisionLayers.clear();
	Debug::log("CollisionSystem::~CollisionSystem() exiting");
}

void CollisionSystem::addCollisionLayers(unsigned collisionLayer, dot::Bitmask collisionBitmask)
{
	m_collisionLayers.insert(std::make_pair(collisionLayer, collisionBitmask));
}

void CollisionSystem::add(std::vector<std::shared_ptr<dot::Entity>>& entities)
{
	// Debug::log("Adding " + std::to_tring(entities.size()) + " colliders to the collision system");
	for (auto& e : entities)
	{
		auto collider = e->getComponent<dot::Collider>();
		if(collider != nullptr)
		{
			// unsigned layer = collider->getLayer();

			// auto itr = m_collidables.find(layer);

			m_collisionTree.insert(collider);

			if (!collider->getOwner()->transform->isStatic())
			{
				m_nonStatics.push_back(collider);
			}
		}
	}
}

void CollisionSystem::processRemovals()
{
	m_collisionTree.clearRemovedObjects();
	auto iter = m_nonStatics.begin();
	while(iter != m_nonStatics.end())
	{
		auto obj = *iter;
		if(obj->getOwner()->isQueuedForRemoval())
		{
			unsigned long long id = obj->getOwner()->instanceID->get();
			auto jtr = m_objectsColliding.begin();
			while(jtr != m_objectsColliding.end())
			{
				auto pair = *jtr;
				if (pair.first->getOwner()->instanceID->get() == id || pair.second->getOwner()->instanceID->get() == id)
				{
					jtr = m_objectsColliding.erase(jtr);
				}
				else
				{
					++jtr;
				}
			}

			iter = m_nonStatics.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CollisionSystem::updatePositions()
{
	for (auto& c : m_nonStatics)
	{
		c->updateTree();
	}
}

void CollisionSystem::update()
{
	updatePositions();
	// m_collisionTree.drawDebug();
	processCollidingEntities();

	// m_collisionTree.clear();

	// for (auto maps = m_collidables.begin(); maps != m_collidables.end(); ++maps)
	// {
	// 	for (auto collidable : maps->second)
	// 	{
	// 		m_collisionTree.insert(collidable);
	// 	}
	// }

	resolve();
}

void CollisionSystem::resolve()
{
	for (auto& collider : m_nonStatics)
	{
		if (m_collisionLayers[collider->getLayer()].getMask() == 0)
		{
			continue;
		}

		std::vector<std::shared_ptr<dot::Collider>> collisions = m_collisionTree.search(collider->getCollidable());

		for (auto& collision : collisions)
		{
			if (collider->getOwner()->instanceID->get() == collision->getOwner()->instanceID->get())
			{
				continue;
			}

			bool layersCollide = m_collisionLayers[collider->getLayer()].getBit(static_cast<int>(collision->getLayer()));
			if (layersCollide)
			{
				Manifold m = collider->intersects(collision);

				if (m.colliding)
				{
					auto collisionPair = m_objectsColliding.emplace(std::make_pair(collider, collision));

					if (collisionPair.second)
					{
						collider->getOwner()->onCollisionEnter(collision);
						collision->getOwner()->onCollisionEnter(collider);
					}

					Debug::renderRect(collision->getCollidable(), sf::Color::Red);
					Debug::renderRect(collider->getCollidable(), sf::Color::Red);

					if(collision->getOwner()->transform->isStatic())
					{
						collider->resolveOverlap(m);
					}
					else
					{
						// TODO: Haw shall we handle collisions when bot objects are not static?
						// Possibility: RigidBodies and Mass
						collider->resolveOverlap(m);
					}
				}
			}
		}
	}
}

void CollisionSystem::processCollidingEntities()
{
	auto itr = m_objectsColliding.begin();
	while(itr != m_objectsColliding.end())
	{
		auto pair = *itr;
		std::shared_ptr<dot::Collider> first = pair.first;
		std::shared_ptr<dot::Collider> second = pair.second;

		if (first->getOwner()->isQueuedForRemoval() || second->getOwner()->isQueuedForRemoval())
		{
			first->getOwner()->onCollisionExit(second);
			second->getOwner()->onCollisionExit(first);

			itr = m_objectsColliding.erase(itr);
		}
		else 
		{
			Manifold m = first->intersects(second);
			if (!m.colliding)
			{
				first->getOwner()->onCollisionExit(second);
				second->getOwner()->onCollisionExit(first);
				itr = m_objectsColliding.erase(itr);
			}
			else
			{
				first->getOwner()->onCollisionStay(second);
				second->getOwner()->onCollisionStay(first);
				++itr;
			}
		}
	}
}