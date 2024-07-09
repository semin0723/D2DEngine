#pragma once
#include "ECSElements.h"
#include "globalheader.h"

using Childs = std::vector<EntityId>;

class UIGroup : public Component<UIGroup>
{
	
public:
	UIGroup() {}
	~UIGroup() {}

	void AddChildUI(EntityId id);
	const Childs& GetChildUI();

	// groupOrder�� �������� �տ� �׷���. 
	// �׷캰 �켱���� �������� ����
	UINT _groupOrder = 0;
};

