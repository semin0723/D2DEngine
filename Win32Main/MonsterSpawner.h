#pragma once
#include "ECSCall.h"
#include "ECSElements.h"
#include "globalheader.h"
#include "EventListener.h"
#include "Events.h"

class MonsterSpawner : public EventListener
{
public:
	MonsterSpawner() { RegistEvent(); }
	~MonsterSpawner() { UnRegistEvent(); }

	void RegistEvent();
	void UnRegistEvent();

	void OnRoundEnd(const RoundEnd* event);
	void OnRoundStart(const RoundStart* event);
	
	void SpawnMonster();

	const int GetCurRound() const { return _curRound; }
private:
	int _spawnCount = 25;
	int _curRound = 0;
	int _nextRound = 1;

	Vector3 _spawnPosition;
};

/*
	라운드 당 스폰 마릿수 25마리.
	라운드당 몬스터 스펙은 파일 시스템을 통해 가져오기.
	스폰 위치 지정.

*/