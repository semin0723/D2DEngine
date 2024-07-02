#include "Monster.h"
#include "Components.h"

void Monster::Initialize()
{
	AddComponent<Transform>();
	AddComponent<StatComponent>();
}
