#include "AnimationComponent.h"

AnimationComponent::AnimationComponent()
{
}

AnimationComponent::~AnimationComponent()
{
	_animations.clear();
}

void AnimationComponent::ChangeAnimation(std::string& stateName)
{
	_curAnimationState = stateName;
}
