#include "Util.h"

bool CheckBorder(D2D1_RECT_F obj1, D2D1_RECT_F obj2)
{
    if (
        obj1.left > obj2.right ||
        obj1.right < obj2.left ||
        obj1.top > obj2.bottom ||
        obj1.bottom < obj2.top
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

std::wstring StringToWstring(std::string& str)
{
    std::wstring tmp;
    tmp.assign(str.begin(), str.end());
    wprintf(tmp.c_str());
    return tmp;
}

std::string WstringToString(std::wstring& wstr)
{
    std::string tmp;
    tmp.assign(wstr.begin(), wstr.end());
    printf(tmp.c_str());
    return tmp;
}
