#pragma once
#include "State.h"

class ButtonClicked :
    public State
{
public:
    ButtonClicked();
    virtual ~ButtonClicked();

    virtual void StateEnter();
    virtual void StateUpdate(float dt);
    virtual void StateExit();

};

