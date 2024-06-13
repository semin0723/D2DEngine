#include "IEntity.h"

IEntity::IEntity() : _active(true)
{
}

void IEntity::SetActive(bool state)
{
	if (_active == state) return;

	if (state == true) {
		OnEnable();
	}
	else {
		OnDisable();
	}
	_active = state;
}
