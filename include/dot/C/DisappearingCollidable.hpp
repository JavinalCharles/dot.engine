#pragma once

#include "dot/C/Component.hpp"
#include "dot/C/Collidable.hpp"

namespace dot
{
class DisappearingCollidable : public dot::Component, public dot::Collidable
{
public:
	DisappearingCollidable(dot::Entity* owner);

	virtual void onCollisionEnter(std::shared_ptr<dot::Collider>& other) override;
	virtual void onCollisionStay(std::shared_ptr<dot::Collider>& other) override;
	virtual void onCollisionExit(std::shared_ptr<dot::Collider>& other) override;

}; // class DisappearingCollidable


}; // namespace dot