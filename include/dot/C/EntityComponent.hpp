#pragma once

#include "dot/C/Component.hpp"
#include <memory>

namespace dot
{
class EntityComponent : public dot::Component
{
public:
	EntityComponent(dot::Entity* owner);

	void lateUpdate(float deltaTime) override;

	void add(std::shared_ptr<dot::Entity> entity);
	std::vector<std::shared_ptr<dot::Entity>> getEntities();
private:
	std::vector<std::shared_ptr<dot::Entity>> m_children;

	sf::Vector2f m_offset;
}; // class Entity

}; // namespace dot
