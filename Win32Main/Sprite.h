#pragma once
#include "globalheader.h"
#include "ECSElements.h"
#include <d2d1.h>

class Sprite : public Component<Sprite>
{
public:
	Sprite();
	~Sprite();

	ID2D1Bitmap* _sprite = { 0 };
	bool _flipX = false;
	bool _flipY = false;
	bool _flipZ = false;
};

