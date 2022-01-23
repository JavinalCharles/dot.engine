#pragma once

#include <memory>
#include "dot/C/Component.hpp"
#include "dot/C/Velocity.hpp"

namespace dot 
{

enum class CardinalDirection : unsigned int
{
	NONE,
	WEST,
	EAST,
	NORTH,
	SOUTH,
	N_A
};


class Direction : public dot::Component
{
public:
	Direction(dot::Entity* entity);
	void awake() override;
	CardinalDirection get();
private:
	std::shared_ptr<dot::Velocity> m_velocity;
	CardinalDirection m_currentDir;
}; // class Direction

}; // namespace dot