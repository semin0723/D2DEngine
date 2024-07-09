#include "Sprite.h"

void Sprite::GetImage(const std::wstring& spriteKey)
{
	_sprite = ResourceSystem::GetInstance()->GetImage(spriteKey);
	_spriteSize = Vector3(_sprite->_bitmap->GetSize().width, _sprite->_bitmap->GetSize().height, 0);
}
