#pragma once
#include "ECSElements.h"
#include "globalheader.h"
#include <dwrite.h>

class TextComponent : public Component<TextComponent>
{
public:
	TextComponent() : _text(L"Text"), _font(L"Cooper"), _fontSize(15.0f) {}
	~TextComponent() {}

	std::wstring _text;
	std::wstring _font;
	float _fontSize = 0;

	DWRITE_TEXT_ALIGNMENT _textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT _paragraphAlignemt = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
};

