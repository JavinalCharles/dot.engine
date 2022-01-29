#include "dot/Containers/CollisionTree.hpp"

#include "dot/Debug/Debug.hpp"

using dot::CollisionTree;

CollisionTree::CollisionTree()
	: CollisionTree(5, 5, 0, {0, 0, 1920, 1920}, nullptr)
{

}

CollisionTree::CollisionTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, CollisionTree* parent)
	: m_maxObjects(maxObjects),
	m_maxLevels(maxLevels),
	m_level(level),
	m_bounds(bounds),
	m_parent(parent)
{

}

void CollisionTree::drawDebug()
{

    if(m_children[0] != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            m_children[i]->drawDebug();
        }
    }
    
    Debug::renderRect(m_bounds, sf::Color::Red);
     
}

void CollisionTree::insert(std::shared_ptr<dot::Collider> object)
{
	// Debug::log("CollisionTree::insert() entered.");
	// Debug::log("InstanceID: " + std::to_string(object->getOwner()->instanceID->get()));

	sf::FloatRect collidable = object->getCollidable();
	// Debug::log("Got FloatRect." + std::to_string(collidable.top) + " " + std::to_string(collidable.left) + " " + std::to_string(collidable.width) + " " + std::to_string(collidable.height));

	if(!m_bounds.intersects(collidable))
	{
		// do nothing if the object is out of bounds.
		return;
	}

	if (m_children[0] != nullptr)
	{
		int index = this->getChildIndexForObject(collidable);
		if (index != thisTree)
		{
			m_children[index]->insert(object);
			return;
		}
		else
		{
			object->setCollisionTree(this);
			m_objects.emplace_back(object);
		}
	}
	else {
		m_objects.emplace_back(object);

		if(m_objects.size() > m_maxObjects && m_level < m_maxLevels && m_children[0] == nullptr)
		{
			this->split();
			auto objIterator = m_objects.begin();
			while(objIterator != m_objects.end())
			{
				auto obj = *objIterator;
				int index = this->getChildIndexForObject(obj->getCollidable());

				if (index != thisTree)
				{
					m_children[index]->insert(obj);
					objIterator = m_objects.erase(objIterator);
				}
				else
				{
					obj->setCollisionTree(this);
					++objIterator;
				}
			}
		}
	}
}

void CollisionTree::remove(std::shared_ptr<dot::Collider> object)
{
	Debug::log("CollisionTree::remove()");
	unsigned long long id = object->getOwner()->instanceID->get();
	Debug::log("InstanceID: " + std::to_string(id));
	int index = getChildIndexForObject(object->getCollidable());

	if (index == thisTree || m_children[index] == nullptr)
	{
		Debug::log("Removing from current tree");
		this->removeID(id);
	}
	else
	{
		Debug::log("Removing to a child tree");
		return m_children[index]->remove(object);
	}
}

void CollisionTree::clear()
{
	m_objects.clear();

	for(int i = 0; i < 4; ++i)
	{
		if (m_children[i] != nullptr)
		{
			m_children[i]->clear();
			m_children[i] = nullptr;
		}
	}
}

void CollisionTree::clearRemovedObjects()
{
	auto iter = m_objects.begin();
	while(iter != m_objects.end())
	{
		auto obj = *iter;
		if(obj->getOwner()->isQueuedForRemoval())
		{
			iter = m_objects.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	for(int i = 0; i < 4; ++i)
	{
		if (m_children[i] != nullptr)
		{
			m_children[i]->clearRemovedObjects();
		}
	}
}

void CollisionTree::removeID(unsigned long long id)
{
	auto objIterator = m_objects.begin();
	while(objIterator != m_objects.end())
	{
		if ((*objIterator)->getOwner()->instanceID->get() == id)
		{
			objIterator = m_objects.erase(objIterator);
		}
		else
		{
			++objIterator;
		}
	}
}

void CollisionTree::updatePosition(std::shared_ptr<dot::Collider> object, bool originalTree)
{
	Debug::log("CollisionTree::updatePosition()");
	sf::FloatRect collidable = object->getCollidable();
	unsigned long long id = object->getOwner()->instanceID->get();
	Debug::log("Object Collider ID: " + std::to_string(id));
	Debug::log("Current level: " + std::to_string(m_level));
	/**
	 * Checks if the collidable is still
	 * within the bounds of the collision tree.
	 * Send back to parent if it doesn't.
	 **/
	if (!m_bounds.intersects(collidable))
	{
		if (m_parent != nullptr)
		{
			// Debug::log("Sending to parent tree");
			m_parent->updatePosition(object, false);
			if(originalTree)
			{
				// Debug::log("Removing from original tree");
				this->remove(object);
			}
		}
		// do nothing if the parent is null.
	}
	else
	{
		if (!originalTree)
		{
			// Debug::log("Re-inserting to a new tree");
			this->insert(object);
		}
		else
		{
			int index = getChildIndexForObject(collidable);
			if (index != thisTree && m_children[0] != nullptr)
			{
				// Debug::log("Removing from this tree");
				this->remove(object);
				// Debug::log("Inserting to a child tree");
				m_children[index]->insert(object);
			}
			else
			{
				// Debug::log("Object is still within original tree");
			}
			// Else do nothing since the object is not going to change tree.
		}
	}
	// Debug::log("Exiting CollisionTree::updatePosition()");
}

std::vector<std::shared_ptr<dot::Collider>> CollisionTree::search(const sf::FloatRect& area)
{
	std::vector<std::shared_ptr<dot::Collider>> returnList;

	search(area, returnList);

	

	return returnList;
}

void CollisionTree::search(const sf::FloatRect& area, std::vector<std::shared_ptr<dot::Collider>>& returnList)
{
	for(auto& collider : m_objects)
	{
		if (area.intersects(collider->getCollidable()))
		{
			returnList.emplace_back(collider);
		}
	}
	if (m_children[0] != nullptr)
	{
		for(int i = 0; i < 4; ++i)
		{
			if (m_children[i]->getBounds().intersects(area))
			{
				m_children[i]->search(area, returnList);
			}
		}
	}
}

const sf::FloatRect& CollisionTree::getBounds() const
{
	return m_bounds;
}

int CollisionTree::getChildIndexForObject(const sf::FloatRect& objectBounds)
{
	int index = -1;

	double verticalDividingLine = m_bounds.left + m_bounds.width * 0.5f;
	double horizontalDividingLine = m_bounds.top + m_bounds.height * 0.5f;

	bool north = objectBounds.top < horizontalDividingLine && (objectBounds.height + objectBounds.top < horizontalDividingLine);
    bool south = objectBounds.top > horizontalDividingLine;
    bool west = objectBounds.left < verticalDividingLine && (objectBounds.left + objectBounds.width < verticalDividingLine);
    bool east = objectBounds.left > verticalDividingLine;
    
    if(east)
    {
        if(north)
        {
            index = childNE;
        }
        else if(south)
        {
            index = childSE;
        }
    }
    else if(west)
    {
        if(north)
        {
            index = childNW;
        }
        else if(south)
        {
            index = childSW;
        }
    }
    
    return index;
}

void CollisionTree::split()
{
	const int childWidth = m_bounds.width / 2;
	const int childHeight = m_bounds.height / 2;

	m_children[childNE] = std::make_shared<CollisionTree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top, childWidth, childHeight), this);
    m_children[childNW] = std::make_shared<CollisionTree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top, childWidth, childHeight), this);
    m_children[childSW] = std::make_shared<CollisionTree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top + childHeight, childWidth, childHeight), this);
    m_children[childSE] = std::make_shared<CollisionTree>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top + childHeight, childWidth, childHeight), this);
}