#pragma once

#include <memory>
#include "dot/C/BoxCollider.hpp"

namespace dot
{

using dot::BoxCollider;

class Collidable
{
	virtual void onCollisionEnter(std::shared_ptr<BoxCollider>& other) = 0;
	virtual void onCollisionStay(std::shared_ptr<BoxCollider>& other) = 0;
	virtual void onCollisionExit(std::shared_ptr<BoxCollider>& other) = 0;
}; // class Collidable
}; // namespace dot