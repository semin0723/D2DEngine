#pragma once
#include "ECSElements.h"

class BoxComponent : public Component<BoxComponent>
{
public:
    BoxComponent();
    BoxComponent(float width, float height);
    ~BoxComponent();

	float _width;
    float _height;
};

