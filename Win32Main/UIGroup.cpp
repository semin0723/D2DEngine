#include "UIGroup.h"
#include "ECSCall.h"

UINT UIGroup::orderidx = 0;

void UIGroup::AddChildUI(EntityId id)
{
    IEntity* ownerEntity = EntityManager->GetEntity(_owner);
    ownerEntity->AddChildEntity(id);
}

const Childs& UIGroup::GetChildUI()
{
    IEntity* ownerEntity = EntityManager->GetEntity(_owner);
    return ownerEntity->GetChildEntityId();
}
