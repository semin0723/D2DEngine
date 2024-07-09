#include "UISystem.h"
#include "Components.h"

UISystem::UISystem()
{
}

UISystem::~UISystem()
{
}

void UISystem::PreUpdate(float dt)
{
}

void UISystem::Update(float dt)
{
}

void UISystem::PostUpdate(float dt)
{
}

void UISystem::GetMouseOnUI(EntityId curid, EntityId& get, const D2D1_POINT_2F& pos)
{
	UITransform* uitf = ComponentManager->Getcomponent<UITransform>(curid);
	Vector3 uiPos = uitf->GetScreenPosition();
	Vector3 uiSize = uitf->GetRectSize();

	if (
		uiPos.x >= pos.x &&
		(uiPos.x + uiSize.x) <= pos.x &&
		uiPos.y >= pos.y &&
		(uiPos.y + uiSize.y) <= pos.y
		) {
		get = curid;
	}

	std::vector<EntityId> childEntities = EntityManager->GetEntity(curid)->GetChildEntityId();
	for (auto& child : childEntities) {
		GetMouseOnUI(child, get, pos);
	}
}

std::pair<EntityId, int> UISystem::GetEffectedEntity(const D2D1_POINT_2F& pos)
{
	EntityId effectedUI;
	for (int i = 0; i < _uigroups.size(); i++) {
		if (EntityManager->GetEntity(_uigroups[i])->Active() == false) continue;
		GetMouseOnUI(_uigroups[i], effectedUI, pos);
		if (CheckEntityId(effectedUI) == true) {
			return std::pair<EntityId, int>(effectedUI, i);
		}
		else {
			return { EntityId(), -1};
		}
	}
}

bool UISystem::CheckEntityId(EntityId& eid)
{
	if (eid._index == (std::numeric_limits<ULL>::max)() && eid._version == (std::numeric_limits<ULL>::max)()) {
		return false;
	}
	else {
		return true;
	}
}

void UISystem::SwapOrder(UIGroupEntities& group, int targetidx)
{
	EntityId tmp = group[0];
	group[0] = group[targetidx];
	group[targetidx] = tmp;
}

void UISystem::RegistEvent()
{
	RegisterCallback(&UISystem::OnMouseButtonDown);
	RegisterCallback(&UISystem::OnMouseButton);
	RegisterCallback(&UISystem::OnMouseButtonUp);
}

void UISystem::UnRegistEvent()
{
	UnRegisterCallback(&UISystem::OnMouseButtonDown);
	UnRegisterCallback(&UISystem::OnMouseButton);
	UnRegisterCallback(&UISystem::OnMouseButtonUp);
}

void UISystem::OnMouseButtonDown(const MouseButtonDown* event)
{
	// effected ui, number of uigroup
	std::pair<EntityId, int> effectedUI = GetEffectedEntity(event->_position);

	if (effectedUI.second == -1) {
		// send message to game
	}
	else {
		SwapOrder(_uigroups, effectedUI.second);
	}

}

void UISystem::OnMouseButton(const MouseButton* event)
{

}

void UISystem::OnMouseButtonUp(const MouseButtonUp* event)
{
	// effected ui, number of uigroup
	std::pair<EntityId, int> effectedUI = GetEffectedEntity(event->_position);

	if (effectedUI.second == -1) {
		// send message to game
	}
	else {
		SwapOrder(_uigroups, effectedUI.second);
	}
}
