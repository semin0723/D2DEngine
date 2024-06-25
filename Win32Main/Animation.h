#pragma once
#include "globalheader.h"
#include <d2d1.h>

struct FrameInfo {
	float _left;
	float _top;
	float _right;
	float _bottom;
	float _playTime;

	FrameInfo() {
		_left = 0;
		_top = 0;
		_right = 0;
		_bottom = 0;
		_playTime = 0;
	}
	FrameInfo(const float left, const float top, const float right, const float bottom, const float duration) {
		_left = left;
		_top = top;
		_right = right;
		_bottom = bottom;
		_playTime = duration;
	}
};

class Animation {
public:
	Animation() {}
	~Animation() { 
		if (_animationBitmapSource) _animationBitmapSource->Release(); 
		_frames.clear();
	}

	bool _isLoop = false;

	ID2D1Bitmap* _animationBitmapSource = { 0 };
	std::vector<FrameInfo> _frames;
};
