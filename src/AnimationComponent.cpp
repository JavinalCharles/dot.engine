#include "dot/C/AnimationComponent.hpp"
#include "dot/E/Entity.hpp"
#include "dot/C/Direction.hpp"
#include <iostream>

using dot::AnimationComponent;

AnimationComponent::AnimationComponent(Entity* owner)
	: Component(owner),
	m_currentAnimation(0, nullptr)
{

}

void AnimationComponent::awake()
{
	m_sprite = m_owner->getComponent<dot::Sprite>();
	// m_direction = m_owner->getComponent<dot::Direction>();
}

void AnimationComponent::update(float deltaTime)
{
	if (m_currentAnimation.first == 0)
		return;

	bool newFrame = m_currentAnimation.second->updateFrame(deltaTime);
	
	if (!newFrame)
		return;
	
	const FrameData* data = m_currentAnimation.second->getCurrentFrame();
	m_sprite->load(data->id);
	m_sprite->setTextureRect(data->x, data->y, data->width, data->height);
	
}

void AnimationComponent::addAnimation(unsigned state, std::shared_ptr<Animation> animation)
{
	m_animations.insert(std::make_pair(state, animation));
	// std::cout << "Entered AnimationComponent::addAnimation() " << state << std::endl;
	if (m_currentAnimation.first == 0)
	{
		Debug::log("Setting AnimationState to: " + std::to_string(state));
		setAnimationState(state);
	}
	// std::cout << "Exiting AnimationComponent::addAnimation()" << std::endl;
}

void AnimationComponent::setAnimationState(unsigned state)
{
	// std::cout << "Entered AnimationComponent::setAnimationState()" << state << std::endl;
	if (m_currentAnimation.first == state)
		return;

	auto animation = m_animations.find(state);
	if (animation != m_animations.end())
	{

		m_currentAnimation.first = animation->first;
		m_currentAnimation.second = animation->second;
		m_currentAnimation.second->reset();
	}
	else
	{
		// TODO: Throw an exception here, probably
		Debug::logError("AnimationState not found!");
	}
}

unsigned AnimationComponent::getAnimationState() const
{
	return m_currentAnimation.first;
}

void AnimationComponent::addAnimationAction(unsigned state, unsigned frame, AnimationAction action)
{
	auto animation = m_animations.find(state);

	if (animation != m_animations.end())
	{
		animation->second->addFrameAction(frame, action);
	}
	else
	{
		Debug::logWarning("AnimationComponent::addAnimationAction: AnimationState not found. Ignoring.");
	}
}