#include "TimeSystem.h"

void TimeSystem::Initialize()
{
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_curTime);
}

void TimeSystem::Update()
{
    _prevTime = _curTime;
    QueryPerformanceCounter(&_curTime);

    _deltaTime = (float)(_curTime.QuadPart - _prevTime.QuadPart) / (float)(_frequency.QuadPart);
}

const float TimeSystem::GetFrameRate()
{
    if (_deltaTime == 0) return 0;
    return ceil((1.0f / _deltaTime));
}

const float TimeSystem::GetDeltaTime()
{
    return _deltaTime;
}
