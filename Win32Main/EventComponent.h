#pragma once
#include "Component.h"

// �̺�Ʈ�� ���� : ����, ����, �̵�, ȸ��, �浹, �׸���, �ൿ
enum class EventType {
    Create,
    Destroy,
    Move,
    Rotate,
    Render,
};

// Entity�� ������ ��� �־�� ��.
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

