#pragma once

#include "dot/C/Component.hpp"
#include "dot/Window.hpp"

class dot::Entity;

namespace dot
{
class LightBlend : public dot::Component
{
public:
	LightBlend(dot::Entity* owner);

	virtual void render(dot::Window& window) = 0;
private:


}; // class LightBlend

}; // namespace dot