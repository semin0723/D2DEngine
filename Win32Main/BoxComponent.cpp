#include "BoxComponent.h"

BoxComponent::BoxComponent() : _left(10.0f), _top(10.0f), _right(100.0f), _bottom(100.0f)
{
}

BoxComponent::BoxComponent(float l, float t, float r, float b) : _left(l), _top(t), _right(r), _bottom(b)
{
}

BoxComponent::~BoxComponent()
{
}
