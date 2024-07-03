#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class DetectComponent : public Component<DetectComponent>
{
public:
	DetectComponent() {}	
	~DetectComponent() {}


	float _detectRange = 0;
	EntityId _targetEntity;
};

