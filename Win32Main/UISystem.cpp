#include "UISystem.h"

UISystem::UISystem()
{
}

UISystem::~UISystem()
{
}

bool UISystem::CheckMouseOnUI(D2D1_POINT_2F pos)
{
	return false;
}

void UISystem::RegistEvent()
{
}

void UISystem::UnRegistEvent()
{
}

void UISystem::OnMouseButtonDown(const MouseButtonDown* event)
{
	// 버튼을 누를 때 눌렸다고 판단하기.
}

void UISystem::OnMouseButton(const MouseButton* event)
{
}

void UISystem::OnMouseButtonUp(const MouseButtonUp* event)
{
}
