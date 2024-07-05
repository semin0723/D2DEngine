#pragma once
#include "globalheader.h"
#include <d2d1.h>

struct FrameInfo {
	int _left;
	int _top;
	int _pixelSize;
	float _timePerFrame;

	FrameInfo() {
		_left = 0;
		_top = 0;
		_pixelSize = 0;
		_timePerFrame = 0;
	}
	FrameInfo(const float left, const float top, const float pixelSize, const float time) {
		_left = left;
		_top = top;
		_pixelSize = pixelSize;
		_timePerFrame = time;
	}
};

class Animation {
public:
	Animation() {}
	Animation(int frameCount) : _frames(frameCount) {}
	~Animation() { 
		_frames.clear();
	}

	bool _isLoop = false;

	std::vector<FrameInfo> _frames;
};
