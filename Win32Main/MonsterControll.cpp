#include "MonsterControll.h"

MonsterControll::MonsterControll()
{
	_spawner = new MonsterSpawner;
	RegistEvent();	
}

MonsterControll::~MonsterControll()
{
	delete _spawner;
	UnRegistEvent();
}

void MonsterControll::PreUpdate(float dt)
{
}

void MonsterControll::Update(float dt)
{
}

void MonsterControll::PostUpdate(float dt)
{
}

void MonsterControll::RegistEvent()
{
	RegisterCallback(&MonsterControll::MonsterCreated);
}

void MonsterControll::UnRegistEvent()
{
	UnRegisterCallback(&MonsterControll::MonsterCreated);
}

void MonsterControll::MonsterCreated(const GameObjectCreated* event)
{
	if (event->_layer != Object_Layer::Monster) return;
	_monsters.push_back(event->_entityId);
}
