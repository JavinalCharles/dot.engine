#pragma once

#include <memory>
#include "dot/C/BoxCollider.hpp"

namespace dot
{

using dot::Collider;

class Collidable
{
public:
	virtual void onCollisionEnter(std::shared_ptr<Collider>& other) = 0;
	virtual void onCollisionStay(std::shared_ptr<Collider>& other) = 0;
	virtual void onCollisionExit(std::shared_ptr<Collider>& other) = 0;
}; // class Collidable
}; // namespace dot