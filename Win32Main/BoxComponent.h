#pragma once
#include "ECSElements.h"

class BoxComponent : public Component<BoxComponent>
{
public:
    BoxComponent();
    BoxComponent(float l, float t, float r, float b);
    ~BoxComponent();

	float _left;
    float _top;
    float _right;
    float _bottom;
};

