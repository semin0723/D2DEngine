#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include "Animation.h"

class AnimationComponent : public Component<AnimationComponent>
{
public:
	AnimationComponent();
	~AnimationComponent();

	void ChangeAnimation(std::string& stateName);

	int _curFrame = 0;
	std::string _curAnimationState;
	std::unordered_map<std::string, Animation*> _animations;
};

