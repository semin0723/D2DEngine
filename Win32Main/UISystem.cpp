#include "UISystem.h"
#include "Components.h"

UISystem::UISystem()
{
	RegistEvent();
}

UISystem::~UISystem()
{
	UnRegistEvent();
	//for (auto& i : _uigroups) {
	//	DestroyUI(i);
	//}
}

void UISystem::PreUpdate(float dt)
{
}

void UISystem::Update(float dt)
{
	for (int i = 0; i < _uigroups.size(); i++) {
		if (EntityManager->GetEntity(_uigroups[i])->Active() == false) continue;
		UpdateUI(_uigroups[i], dt);
	}
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
		uiPos.x <= pos.x &&
		(uiPos.x + uiSize.x) >= pos.x &&
		uiPos.y <= pos.y &&
		(uiPos.y + uiSize.y) >= pos.y
		) {
		get = curid;
	}

	ButtonComponent* btnc = ComponentManager->Getcomponent<ButtonComponent>(curid);
	if (btnc != nullptr && get != curid) {
		if (btnc->_curState == Button_State::Pressed) {
			btnc->ChangeState(Button_State::Released);
		}
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
	return { EntityId(), -1 };
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
	UIGroup* uigroup1 = ComponentManager->Getcomponent<UIGroup>(group[0]);
	UIGroup* uigroup2 = ComponentManager->Getcomponent<UIGroup>(group[targetidx]);

	UINT tmporder = uigroup1->_groupOrder;
	uigroup1->_groupOrder = uigroup2->_groupOrder;
	uigroup2->_groupOrder = tmporder;

	std::sort(group.begin(), group.end(), [&](EntityId& a, EntityId& b) {
		UIGroup* uileft = ComponentManager->Getcomponent<UIGroup>(a);
		UIGroup* uiright = ComponentManager->Getcomponent<UIGroup>(b);
		return uileft->_groupOrder < uiright->_groupOrder;
		});
}

void UISystem::SwapOrder(UIGroupEntities& group, EntityId targetId)
{
	int idx = 0;
	for (; idx < group.size(); idx++) {
		if (group[idx] == targetId) break;
	}
	SwapOrder(group, idx);
}

void UISystem::UpdateUI(EntityId id, float dt)
{
	UITransform* uitf = ComponentManager->Getcomponent<UITransform>(id);
	uitf->UpdatePosition();

	ButtonComponent* btnc = ComponentManager->Getcomponent<ButtonComponent>(id);
	if (btnc != nullptr) {
		btnc->_states[btnc->_curState]->StateUpdate(dt);
	}

	std::vector<EntityId> childEntities = EntityManager->GetEntity(id)->GetChildEntityId();

	for (auto& child : childEntities) {
		UpdateUI(child, dt);
	}
}

void UISystem::DestroyUI(EntityId id)
{
	std::vector<EntityId> childEntities = EntityManager->GetEntity(id)->GetChildEntityId();
	for (auto& child : childEntities) {
		DestroyUI(child);
	}
	EntityManager->DestroyEntity(id);
}

void UISystem::SetActive(EntityId id, bool state)
{
	EntityManager->GetEntity(id)->SetActive(state);
	std::vector<EntityId> childs = EntityManager->GetEntity(id)->GetChildEntityId();
	for (auto& child : childs) {
		SetActive(child, state);
	}
}

void UISystem::RegistEvent()
{
	RegisterCallback(&UISystem::OnUICreate);
	RegisterCallback(&UISystem::OnUIDestroyed);
	RegisterCallback(&UISystem::OnMouseButtonDown);
	RegisterCallback(&UISystem::OnMouseButton);
	RegisterCallback(&UISystem::OnMouseButtonUp);
	RegisterCallback(&UISystem::ChangeUIstate);
}

void UISystem::UnRegistEvent()
{
	UnRegisterCallback(&UISystem::OnUICreate);
	UnRegisterCallback(&UISystem::OnUIDestroyed);
	UnRegisterCallback(&UISystem::OnMouseButtonDown);
	UnRegisterCallback(&UISystem::OnMouseButton);
	UnRegisterCallback(&UISystem::OnMouseButtonUp);
	UnRegisterCallback(&UISystem::ChangeUIstate);
}

void UISystem::OnMouseButtonDown(const MouseButtonDown* event)
{
	// effected ui, number of uigroup
	std::pair<EntityId, int> effectedUI = GetEffectedEntity(event->_position);

	if (effectedUI.second == -1) {
		ecs->SendEvent<ClickInGame>(event->_position);
	}
	else {
		SwapOrder(_uigroups, effectedUI.second);
		ButtonComponent* btnc = ComponentManager->Getcomponent<ButtonComponent>(effectedUI.first);
		if (btnc != nullptr) {
			if (btnc->_curState == Button_State::Normal) {
				btnc->ChangeState(Button_State::Pressed);
			}
		}
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
		ButtonComponent* btnc = ComponentManager->Getcomponent<ButtonComponent>(effectedUI.first);
		if (btnc != nullptr) {
			if (btnc->_curState == Button_State::Pressed) {
				btnc->ChangeState(Button_State::Clicked);
			}
		}
	}
}

void UISystem::OnUICreate(const GameObjectCreated* event)
{
	if (event->_layer != Object_Layer::UI) return;
	_uigroups.push_back(event->_entityId);
}

void UISystem::OnUIDestroyed(const GameObjectDestroyed* event)
{
	if (event->_layer != Object_Layer::UI) return;
	for (UIGroupEntities::iterator it = _uigroups.begin(); it != _uigroups.end(); it++) {
		if (*it == event->_entityId) {
			DestroyUI(event->_entityId);
			break;
		}
	}
}

void UISystem::ChangeUIstate(const UIStateChange* event)
{
	SetActive(event->_eid, event->_state);
	SwapOrder(_uigroups, event->_eid);
}
