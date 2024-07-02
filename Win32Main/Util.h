#pragma once
#include "globalheader.h"

bool CheckCameraBorder(D2D1_RECT_F camera, D2D1_RECT_F obj);
D2D1_RECT_F GetBounds(Vector3& pos, Vector3& rect);
D2D1_RECT_F GetBounds(D2D1_POINT_2F pos, D2D1_POINT_2F rect);