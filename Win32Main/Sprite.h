#pragma once
#include "ResourceSystem.h"
#include "ECSElements.h"

class Sprite : public Component<Sprite>
{
public:
	Sprite(std::wstring spriteKey) {
		_sprite = ResourceSystem::GetInstance()->GetImage(spriteKey);
		_spriteSize = Vector3(_sprite->_bitmap->GetSize().width, _sprite->_bitmap->GetSize().height, 0);
	}
	~Sprite() {}

	void SetFlipX(const bool state) { _flipX = state; }
	void SetFlipY(const bool state) { _flipY = state; }
	void SetFlipZ(const bool state) { _flipZ = state; }

	Image* _sprite;
	Vector3 _spriteSize;
	bool _flipX = false;
	bool _flipY = false;
	bool _flipZ = false;	
};

