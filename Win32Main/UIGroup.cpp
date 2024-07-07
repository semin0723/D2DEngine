#include "UIGroup.h"
#include "ECSCall.h"

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
