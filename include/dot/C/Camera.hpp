#pragma once

#include "dot/C/Component.hpp"

namespace dot
{
class Camera : public dot::Component
{
public:
	Camera(dot::Entity* owner);

	void lateUpdate(float deltaTime) override;
}; // namespace Camera

}; // namespace dot