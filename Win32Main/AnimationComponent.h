#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include "Animation.h"

class AnimationComponent : public Component<AnimationComponent>
{
public:
	AnimationComponent();
	~AnimationComponent();

	void ChangeAnimation(std::wstring& stateName);
	void AddAnimation(std::wstring key, Animation* animation);

	Animation* GetCurAnimation() { return _animations[_curAnimationState]; }

	int _curFrame = 0;
	float _curTime = 0;
	std::wstring _curAnimationState;
	std::unordered_map<std::wstring, Animation*> _animations;
};

