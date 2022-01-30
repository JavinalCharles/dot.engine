#pragma once
#include <memory>

#include "dot/C/LightBounds.hpp"
#include "dot/C/Drawable.hpp"

namespace dot
{
class DrawnLightBounds : public dot::LightBounds
{
public:
	DrawnLightBounds(dot::Entity* owner);

	virtual void awake() override;

	virtual sf::FloatRect getBounds() override;

private:
	std::shared_ptr<dot::Drawable> m_drawable;
}; // class DrawnLightBounds

}; // namespace dot