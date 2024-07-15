#pragma once
#include "ECSElements.h"
#include "globalheader.h"

class TextComponent : Component<TextComponent>
{
public:
	TextComponent() : _text(L"Text"), _font(L"Cooper"), _fontSize(15.0f) {}
	~TextComponent() {}

	std::wstring _text;
	std::wstring _font;
	float _fontSize = 0;
};

