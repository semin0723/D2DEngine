#include "AnimationComponent.h"

AnimationComponent::AnimationComponent() : _curAnimationState(L"")
{
}

AnimationComponent::~AnimationComponent()
{
	_animations.clear();
}

void AnimationComponent::ChangeAnimation(std::wstring& stateName)
{
	_curAnimationState = stateName;
}

void AnimationComponent::AddAnimation(std::wstring key, Animation* animation)
{
	if (_animations.find(key) == _animations.end()) {
		_animations[key] = animation;
	}
}
