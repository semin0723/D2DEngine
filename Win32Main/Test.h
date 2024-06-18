#pragma once
#include "Event.h"
#include "EventListener.h"
#include "RenderComponent.h"

struct DrawRectangle : public Event< DrawRectangle> {
	float left;
	float top;
	float right;
	float bottom;
	DrawRectangle(float _left, float _top, float _right, float _bottom) :
		left(_left), top(_top), right(_right), bottom(_bottom)
	{}
};

class Test : public EventListener
{
public:
	Test();
	~Test();

	

private:
	void RegistEvent();
	void UnRegistEvent();
	void eventTest(const DrawRectangle* event);

	RenderComponent* _render	{ 0 };
		
	friend class DemoApp;
};

