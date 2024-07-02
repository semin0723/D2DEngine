#include "Util.h"

bool CheckCameraBorder(D2D1_RECT_F camera, D2D1_RECT_F obj)
{
    if (
        obj.left > camera.right ||
        obj.right < camera.left ||
        obj.top > camera.bottom ||
        obj.bottom < camera.top
        ) {
        return false;
    }
    return true;
}

D2D1_RECT_F GetBounds(Vector3& pos, Vector3& rect)
{
    return { pos.x, pos.y, pos.x + rect.x, pos.y + rect.y };
}

D2D1_RECT_F GetBounds(D2D1_POINT_2F pos, D2D1_POINT_2F rect)
{
    return { pos.x, pos.y, pos.x + rect.x, pos.y + rect.y };
}
