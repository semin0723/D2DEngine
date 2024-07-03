#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class DetectComponent : public Component<DetectComponent>
{
public:
	DetectComponent() {}	
	~DetectComponent() {}



	EntityId _targetEntity;
};

