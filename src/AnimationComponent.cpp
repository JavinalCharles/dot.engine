#include "dot/C/AnimationComponent.hpp"
#include "dot/E/Entity.hpp"
#include "dot/C/Direction.hpp"
#include <iostream>

using dot::AnimationComponent;

AnimationComponent::AnimationComponent(Entity* owner)
	: Component(owner),
	m_currentAnimation(0, nullptr),
	m_currentDirection(CardinalDirection::NONE)
{

}

void AnimationComponent::awake()
{
	m_sprite = m_owner->getComponent<dot::Sprite>();
	m_direction = m_owner->getComponent<dot::Direction>();
}

void AnimationComponent::update(float deltaTime)
{
	if (m_allowDirectionalAnimations)
		setAnimationDirection(m_direction->get());

	if (m_currentAnimation.first != 0)
	{
		bool newFrame = m_currentAnimation.second->updateFrame(deltaTime);
		if (newFrame)
		{
			const FrameData* data = m_currentAnimation.second->getCurrentFrame();
			m_sprite->load(data->id);
			m_sprite->setTextureRect(data->x, data->y, data->width, data->height);
		}
	}
}

void AnimationComponent::addAnimation(unsigned state, AnimationList& animationList)
{
	m_animations.insert(std::make_pair(state, animationList));
	// std::cout << "Entered AnimationComponent::addAnimation() " << state << std::endl;
	if (m_currentAnimation.first == 0)
	{
		std::cout << "Setting AnimationState to: " << state << std::endl;
		setAnimationState(state);
	}
	// std::cout << "Exiting AnimationComponent::addAnimation()" << std::endl;
}

void AnimationComponent::setAnimationState(unsigned state)
{
	// std::cout << "Entered AnimationComponent::setAnimationState()" << state << std::endl;
	if (m_currentAnimation.first == state)
	{
		return;
	}

	auto animationList = m_animations.find(state);
	if (animationList != m_animations.end())
	{
		auto animation = animationList->second.find(m_currentDirection);
		if (animation != animationList->second.end())
		{
			// std::cout << "Setting up m_currentAnimation" << std::endl;
			m_currentAnimation.first = animationList->first;
			m_currentAnimation.second = animation->second;
			m_currentAnimation.second->reset();
		}
		else 
		{
			// std::cout << "required animation cannot be found in animationList" << std::endl;
		}
	}
	else
	{
		// std::cout << "animationList cannot be found in m_animations." << std::endl;
	}

	// std::cout << "Exiting AnimationComponent::setAnimationState()" << std::endl;
}

unsigned AnimationComponent::getAnimationState() const
{
	return m_currentAnimation.first;
}

void AnimationComponent::setAnimationDirection(CardinalDirection dir)
{
	if (dir != m_currentDirection)
	{
		m_currentDirection = dir;

		auto animationList = m_animations.find(m_currentAnimation.first);

		if (animationList != m_animations.end())
		{
			auto animation = animationList->second.find(m_currentDirection);
			if (animation != animationList->second.end())
			{
				m_currentAnimation.second = animation->second;
				m_currentAnimation.second->reset();
			}
		}
	}
}

void AnimationComponent::addAnimationAction(unsigned state, CardinalDirection dir, unsigned frame, AnimationAction action)
{
	auto animationList = m_animations.find(state);

	if (animationList != m_animations.end())
	{
		auto animation = animationList->second.find(dir);
		if (animation != animationList->second.end())
		{
			animation->second->addFrameAction(frame, action);
		}
	}
}

void AnimationComponent::setDirectionalAnimations(bool allowDirectionalAnimation)
{
	m_allowDirectionalAnimations = allowDirectionalAnimation;
	if (!m_allowDirectionalAnimations)
	{
		setAnimationDirection(CardinalDirection::N_A);
	}
}