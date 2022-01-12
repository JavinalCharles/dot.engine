#include "dot/C/Camera.hpp"
#include "dot/E/Entity.hpp"

using dot::Camera;

Camera::Camera(dot::Entity* owner)
	: dot::Component(owner)
{

}

void Camera::lateUpdate(float deltaTime)
{
	if (m_owner->context->window)
	{
		sf::View view = m_owner->context->window->getView();
		const sf::Vector2f& targetPos = m_owner->transform->getPosition();
		view.setCenter(targetPos.x, targetPos.y);
		m_owner->context->window->setView(view);
	}
}