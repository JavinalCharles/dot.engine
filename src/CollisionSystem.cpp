#include "dot/S/CollisionSystem.hpp"
#include "dot/Debug/Debug.hpp"


using dot::CollisionSystem;

CollisionSystem::CollisionSystem()
	: m_collisionTree(10, 15, 0, {0, 0, 4200, 2048}, nullptr)
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
	for (auto& e : entities)
	{
		auto collider = e->getComponent<dot::BoxCollider>();
		if(collider)
		{
			if (collider->getOwner()->transform->isStatic())
			{
				m_collisionTree.insert(collider);
			}
			else
			{
				unsigned layer = collider->getLayer();
				auto itr = m_collidables.find(layer);

				if(itr != m_collidables.end())
				{
					m_collidables[layer].push_back(collider);
				}
				else
				{
					m_collidables.insert(std::make_pair(layer, std::vector<std::shared_ptr<dot::BoxCollider>>{collider}));
				}
			}
		}
	}
}

void CollisionSystem::processRemovals()
{
	for(auto& layer : m_collidables)
	{
		auto itr = layer.second.begin();
		while(itr != layer.second.end())
		{
			if ((*itr)->getOwner()->isQueuedForRemoval())
			{
				auto id = (*itr)->getOwner()->instanceID->get();
				auto jtr = m_objectsColliding.begin();
				while (jtr != m_objectsColliding.end())
				{
					auto pair = *jtr;
					if(pair.first->getOwner()->instanceID->get() == id || pair.second->getOwner()->instanceID->get() == id)
					{
						jtr = m_objectsColliding.erase(jtr);
					}
					else 
					{
						++jtr;
					}
				}

				itr = layer.second.erase(itr);
			}
			else
			{
				++itr;
			}
		}
	}
}

void CollisionSystem::update()
{
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
	for (auto maps = m_collidables.begin(); maps != m_collidables.end(); ++maps)
	{
		if(m_collisionLayers[maps->first].getMask() == 0)
		{
			continue;
		}
		for(auto collidable : maps->second)
		{
			// If this collidable is static then no need to check
			// if it's colliding with other objects
			if(collidable->getOwner()->transform->isStatic())
			{
				continue;
			}

			std::vector<std::shared_ptr<dot::BoxCollider>> collisions = m_collisionTree.search(collidable->getCollidable());
			for (auto collision : collisions)
			{
				// Make sure we do not resolve collisions between the same object
				if (collidable->getOwner()->instanceID->get() == collision->getOwner()->instanceID->get())
				{
					continue;
				}

				bool layersCollide = m_collisionLayers[collidable->getLayer()].getBit(((int)collision->getLayer()));

				if(layersCollide)
				{
					Manifold m = collidable->intersects(collision);
					if(m.colliding)
					{
						
						auto collisionPair = m_objectsColliding.emplace(std::make_pair(collidable, collision));
						if (collisionPair.second)
						{
							collidable->getOwner()->onCollisionEnter(collision);
							collision->getOwner()->onCollisionEnter(collidable);

						}

						Debug::renderRect(collision->getCollidable(), sf::Color::Red);
						Debug::renderRect(collidable->getCollidable(), sf::Color::Red);

						if (collision->getOwner()->transform->isStatic())
						{
							collidable->resolveOverlap(m);
						}
						else
						{
							// TODO: how shall we handle collision when both objects are not static?
							// We could implement rigidbodies and mass
							collidable->resolveOverlap(m);
						}
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
		std::shared_ptr<dot::BoxCollider> first = pair.first;
		std::shared_ptr<dot::BoxCollider> second = pair.second;

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