#pragma once
#include <d2d1.h>

class Image {
public:
	Image() {}
	~Image() { _bitmap->Release(); }

	ID2D1Bitmap* _bitmap{ 0 };
};