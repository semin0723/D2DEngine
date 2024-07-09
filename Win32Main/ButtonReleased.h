#pragma once
#include "State.h"

class ButtonReleased :
    public State
{
public:
    ButtonReleased();
    virtual ~ButtonReleased();

    virtual void StateEnter();
    virtual void StateUpdate(float dt);
    virtual void StateExit();

private:
    float _stateChangeInterval = 0.25f;
};

