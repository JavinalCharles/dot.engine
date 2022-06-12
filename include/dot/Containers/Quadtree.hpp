#pragma once

#include <memory>
#include <vector>
#include "dot/C/Collider.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"

namespace dot
{

template <typename T>
class Quadtree
{
public:
	Quadtree();
	Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent);

	void drawDebug();

	void insert(std::shared_ptr<T> object);
	void remove(std::shared_ptr<T> object);

	void clear();
	void clearRemovedObjects();

	void updatePosition(std::shared_ptr<T> object, bool originalTree = true);

	std::vector<std::shared_ptr<T>> search(const sf::FloatRect& area);

	const sf::FloatRect& getBounds() const;

private:
	void search(const sf::FloatRect& area, std::vector<std::shared_ptr<T>>& overlappingObjects);
	void removeID(unsigned long long id);

	int getChildIndexForObject(const sf::FloatRect& objectBounds);

	void split();

	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int m_maxObjects;
	int m_maxLevels;
	int m_level;
	sf::FloatRect m_bounds;

	Quadtree* m_parent;

	std::shared_ptr<Quadtree<T>> m_children[4];

	std::vector<std::shared_ptr<T>> m_objects;
}; // class Quadtree

typedef Quadtree<dot::Collider> CollisionTree;
typedef Quadtree<dot::Drawable> DrawableTree;

template<typename T>
Quadtree<T>::Quadtree()
	: Quadtree<T>(5, 5, 0, {0, 0, 1920, 1920}, nullptr)
{

}

template<typename T>
Quadtree<T>::Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree<T>* parent)
	: m_maxObjects(maxObjects),
	m_maxLevels(maxLevels),
	m_level(level),
	m_bounds(bounds),
	m_parent(parent)
{

}

template<typename T>
void Quadtree<T>::drawDebug()
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

template<typename T>
void Quadtree<T>::insert(std::shared_ptr<T> object)
{
	// Debug::log("Quadtree<T>::insert() entered.");
	// Debug::log("InstanceID: " + std::to_string(object->getOwner()->instanceID->get()));

	sf::FloatRect bounds = object->getBounds();
	// Debug::log("Got FloatRect." + std::to_string(bounds.top) + " " + std::to_string(bounds.left) + " " + std::to_string(bounds.width) + " " + std::to_string(bounds.height));

	if(!m_bounds.intersects(bounds))
	{
		// do nothing if the object is out of bounds.
		return;
	}

	if (m_children[0] != nullptr)
	{
		int index = this->getChildIndexForObject(bounds);
		if (index != thisTree)
		{
			m_children[index]->insert(object);
			return;
		}
		else
		{
			object->setTree(this);
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
				int index = this->getChildIndexForObject(obj->getBounds());

				if (index != thisTree)
				{
					m_children[index]->insert(obj);
					objIterator = m_objects.erase(objIterator);
				}
				else
				{
					obj->setTree(this);
					++objIterator;
				}
			}
		}
	}
}

template<typename T>
void Quadtree<T>::remove(std::shared_ptr<T> object)
{
	// Debug::log("Quadtree<T>::remove()");
	unsigned long long id = object->getOwner()->instanceID->get();
	// Debug::log("InstanceID: " + std::to_string(id));
	int index = getChildIndexForObject(object->getBounds());

	if (index == thisTree || m_children[index] == nullptr)
	{
		// Debug::log("Removing from current tree");
		this->removeID(id);
	}
	else
	{
		// Debug::log("Removing to a child tree");
		return m_children[index]->remove(object);
	}
}

template<typename T>
void Quadtree<T>::clear()
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

template<typename T>
void Quadtree<T>::clearRemovedObjects()
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

template<typename T>
void Quadtree<T>::removeID(unsigned long long id)
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

template<typename T>
void Quadtree<T>::updatePosition(std::shared_ptr<T> object, bool originalTree)
{
	// Debug::log("Quadtree<T>::updatePosition()");
	sf::FloatRect bounds = object->getBounds();
	unsigned long long id = object->getOwner()->instanceID->get();
	// Debug::log("Object ID: " + std::to_string(id));
	// Debug::log("Current level: " + std::to_string(m_level));
	/**
	 * Checks if the bounds is still
	 * within the bounds of the collision tree.
	 * Send back to parent if it doesn't.
	 **/
	if (!m_bounds.intersects(bounds))
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
			int index = getChildIndexForObject(bounds);
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
	// Debug::log("Exiting Quadtree<T>::updatePosition()");
}

template<typename T>
std::vector<std::shared_ptr<T>> Quadtree<T>::search(const sf::FloatRect& area)
{
	std::vector<std::shared_ptr<T>> returnList;

	search(area, returnList);

	return returnList;
}

template<typename T>
void Quadtree<T>::search(const sf::FloatRect& area, std::vector<std::shared_ptr<T>>& returnList)
{
	for(auto& collider : m_objects)
	{
		if (area.intersects(collider->getBounds()))
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

template<typename T>
const sf::FloatRect& Quadtree<T>::getBounds() const
{
	return m_bounds;
}

template<typename T>
int Quadtree<T>::getChildIndexForObject(const sf::FloatRect& objectBounds)
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

template<typename T>
void Quadtree<T>::split()
{
	const int childWidth = m_bounds.width / 2;
	const int childHeight = m_bounds.height / 2;

	m_children[childNE] = std::make_shared<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top, childWidth, childHeight), this);
    m_children[childNW] = std::make_shared<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top, childWidth, childHeight), this);
    m_children[childSW] = std::make_shared<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left, m_bounds.top + childHeight, childWidth, childHeight), this);
    m_children[childSE] = std::make_shared<Quadtree<T>>(m_maxObjects, m_maxLevels, m_level + 1, sf::FloatRect(m_bounds.left + childWidth, m_bounds.top + childHeight, childWidth, childHeight), this);
}











}; // namespace dot
