#pragma once
#include "Component.h"

// 이벤트의 종류 : 생성, 삭제, 이동, 회전, 충돌, 그리기, 행동
enum class EventType {
    Create,
    Destroy,
    Move,
    Rotate,
    Render,
};

// Entity의 정보를 들고 있어야 함.
struct Event {
    EventType _event;
    /* Entity _entity; */
    /* <struct type> EntityInfo; */
};

class EventComponent :
    public Component
{
public:

private:

};

