#pragma once
#include "globalheader.h"
#include "ECSElements.h"
#include "Image.h"

class Sprite : public Component<Sprite>
{
public:
	Sprite(Image* image) : _sprite(image) {}
	~Sprite() {}

	void SetFlipX(const bool state) { _flipX = state; }
	void SetFlipY(const bool state) { _flipX = state; }
	void SetFlipZ(const bool state) { _flipX = state; }

	Image* _sprite;
	bool _flipX = false;
	bool _flipY = false;
	bool _flipZ = false;
};

