#include "dot/C/DisappearingCollidable.hpp"
#include "dot/E/Entity.hpp"
#include "dot/Debug/Debug.hpp"

using dot::DisappearingCollidable;

DisappearingCollidable::DisappearingCollidable(dot::Entity* owner)
	: dot::Component(owner)
{
}

void DisappearingCollidable::onCollisionEnter(std::shared_ptr<dot::Collider>& other)
{
	// Debug::log("DisappearingCollidable::onCollisionEnter()");
	// Debug::log("Queueing object for removal: " + m_owner->instanceID->get());
	m_owner->queueForRemoval();
}

void DisappearingCollidable::onCollisionStay(std::shared_ptr<dot::Collider>& other)
{

}

void DisappearingCollidable::onCollisionExit(std::shared_ptr<dot::Collider>& other)
{

}