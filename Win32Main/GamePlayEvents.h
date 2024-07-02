#pragma once
#include "ECSElements.h"

struct RoundEnd : Event<RoundEnd> {
	int _curRound;
	RoundEnd(int cur) : _curRound(cur) {}
};

struct RoundStart : Event<RoundStart> {
	int _curRound;
	RoundStart(int cur) : _curRound(cur) {}
};

struct GameOver : Event<GameOver> {
	int _curRound;
	GameOver(int cur) : _curRound(cur) {}
};