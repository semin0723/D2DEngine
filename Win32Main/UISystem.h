#pragma once
#include "ECSElements.h"
#include "ECSCall.h"
#include "globalheader.h"
#include "EventListener.h"
#include "Events.h"

class UISystem : public System<UISystem>, public EventListener
{
public:
	UISystem();
	~UISystem();
	
	bool CheckMouseOnUI(D2D1_POINT_2F pos);

	void RegistEvent();
	void UnRegistEvent();

	void OnMouseButtonDown(const MouseButtonDown* event);
	void OnMouseButton(const MouseButton* event);
	void OnMouseButtonUp(const MouseButtonUp* event);

private:
	using UIGroupEntities = std::vector<EntityId>;

	UIGroupEntities _uigroups;
};

