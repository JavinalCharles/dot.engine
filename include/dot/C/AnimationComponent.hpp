#pragma once

#include <map>
#include "dot/Animation.hpp"
#include "dot/C/Component.hpp"
#include "dot/Utilities/EnumClassHash.hpp"
#include "dot/C/Sprite.hpp"
#include "dot/C/Direction.hpp"

using dot::Entity;
using dot::Component;
using dot::Animation;
using dot::Sprite;
using dot::AnimationAction;
using dot::CardinalDirection;


namespace dot
{

using AnimationList = std::unordered_map<CardinalDirection, std::shared_ptr<Animation>, dot::EnumClassHash>;

class AnimationComponent : public Component
{
public:
	AnimationComponent(Entity* owner);

	void awake() override;
	void update(float deltaTime) override;

	void addAnimation(unsigned state, AnimationList& animationList);

	void setAnimationState(unsigned state);

	unsigned getAnimationState() const;

	void setAnimationDirection(CardinalDirection dir);

	void addAnimationAction(unsigned state, CardinalDirection dir, unsigned frame, AnimationAction action);
private:
	std::shared_ptr<Sprite> m_sprite;
	std::unordered_map<unsigned, AnimationList, EnumClassHash> m_animations;
	std::pair<unsigned, std::shared_ptr<Animation>> m_currentAnimation;
	CardinalDirection m_currentDirection;

	std::shared_ptr<dot::Direction> m_direction;
}; // class ANimationComponent

}; // namespace dot


