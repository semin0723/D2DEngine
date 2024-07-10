#pragma once
#include "globalheader.h"

bool CheckBorder(D2D1_RECT_F obj1, D2D1_RECT_F obj2);
D2D1_RECT_F GetBounds(Vector3& pos, Vector3& rect);
D2D1_RECT_F GetBounds(D2D1_POINT_2F pos, D2D1_POINT_2F rect);
std::wstring StringToWstring(std::string& str);
std::string WstringToString(std::wstring& wstr);