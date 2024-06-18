#include "Test.h"

Test::Test()
{
	RegistEvent();
}

Test::~Test()
{
	UnRegistEvent();
}

void Test::RegistEvent()
{
	RegisterCallback(&Test::eventTest);
}

void Test::UnRegistEvent()
{
	UnRegisterCallback(&Test::eventTest);
}

void Test::eventTest(const DrawRectangle* event)
{
	_render->DrawFillRectangle(event->left, event->top, event->right, event->bottom, GRAY);
}
