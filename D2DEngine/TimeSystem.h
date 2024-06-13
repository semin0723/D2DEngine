#pragma once
#include <Windows.h>
#include <cmath>

class TimeSystem
{
public:
	TimeSystem() {}
	~TimeSystem() {}

	void Initialize();
	void Update();
	const float GetFrameRate();
	const float GetDeltaTime();

private:
	LARGE_INTEGER _curTime = { 0 };
	LARGE_INTEGER _prevTime = { 0 };
	LARGE_INTEGER _frequency = { 0 };

	float _deltaTime = { 0.0f };
};

