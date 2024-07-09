#pragma once
#include "ResourceSystem.h"
#include "ECSElements.h"

class Sprite : public Component<Sprite>
{
public:
	Sprite(std::wstring spriteKey) {
		GetImage(spriteKey);
	}
	~Sprite() {}

	void SetFlipX(const bool state) { _flipX = state; }
	void SetFlipY(const bool state) { _flipY = state; }
	void SetFlipZ(const bool state) { _flipZ = state; }

	void GetImage(const std::wstring& spriteKey);

	Image* _sprite;
	Vector3 _spriteSize;
	bool _flipX = false;
	bool _flipY = false;
	bool _flipZ = false;	
};

