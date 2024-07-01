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
