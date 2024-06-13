#include "FamilyTypeId.h"

class IEntity;
class IComponent;
class ISystem;

unsigned long long FamilyTypeId<IEntity>::_count = 0u;
unsigned long long FamilyTypeId<IComponent>::_count = 0u;
unsigned long long FamilyTypeId<ISystem>::_count = 0u;

template class FamilyTypeId<IEntity>;
template class FamilyTypeId<IComponent>;
template class FamilyTypeId<ISystem>;