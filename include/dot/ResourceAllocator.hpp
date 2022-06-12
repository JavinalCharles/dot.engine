#pragma once

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "dot/ResourceNotFoundError.hpp"
#include <iostream>

namespace dot
{

template <typename T>
class ResourceAllocator
{
public:
	ResourceAllocator();
	unsigned add(const std::string& filePath);
	unsigned add(const T& preLoadedResource);
	void remove(unsigned id);
	std::shared_ptr<T> get(unsigned id);
	bool has(unsigned id);

private:
	unsigned m_currentId;

	std::map<unsigned, std::shared_ptr<T>> m_resources;
}; // class ResourceAllocator

using TextureAllocator = ResourceAllocator<sf::Texture>;


template <typename T>
ResourceAllocator<T>::ResourceAllocator()
	: m_currentId(1),
	m_resources()
{
	
}

template <typename T>
unsigned ResourceAllocator<T>::add(const std::string& filePath)
{
	std::shared_ptr<T> resource = std::make_shared<T>();
	if (!resource->loadFromFile(filePath))
	{
		throw dot::ResourceNotFoundError(filePath);
	}
	std::cout << "Added resource with ID: " << m_currentId << " from:" << filePath << std::endl;
	m_resources.insert(std::make_pair(m_currentId, resource));
	return m_currentId++;
}

template <typename T>
unsigned ResourceAllocator<T>::add(const T& preLoadedResource)
{
	std::shared_ptr<T> resource = std::make_shared<T>(preLoadedResource);
	m_resources.insert(std::make_pair(m_currentId, resource));
	return m_currentId++;
}

template<typename T>
void ResourceAllocator<T>::remove(unsigned id)
{
	auto it = m_resources.find(id);
	if (it != m_resources.end())
	{
		m_resources.end(it);
	}
}

template <typename T>
std::shared_ptr<T> ResourceAllocator<T>::get(unsigned id)
{
	auto it = m_resources.find(id);
	if (it != m_resources.end())
	{
		return it->second;
	}
	return nullptr;
}

template <typename T>
bool ResourceAllocator<T>::has(unsigned id)
{
	return m_resources.find(id) != m_resources.end();
}

}; // namespace dot