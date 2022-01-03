#pragma once

#include <memory>
#include "Sigma/C/BoxCollider.hpp"

namespace Sigma
{

using Sigma::BoxCollider;

class Collidable
{
	virtual void onCollisionEnter(std::shared_ptr<BoxCollider>& other) = 0;
	virtual void onCollisionStay(std::shared_ptr<BoxCollider>& other) = 0;
	virtual void onCollisionExit(std::shared_ptr<BoxCollider>& other) = 0;
}; // class Collidable
}; // namespace Sigma