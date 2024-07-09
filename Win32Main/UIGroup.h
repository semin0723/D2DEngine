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

	// groupOrder이 낮을수록 앞에 그려짐. 
	// 그룹별 우선순위 내림차순 정렬
	UINT _groupOrder = 0;
};

