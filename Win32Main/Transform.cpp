#include "Transform.h"

Transform::Transform() : _position{ 0, 0, 0 }, _scale{ 1, 1, 1 }, _rotate{ 0, 0, 0 }
{

}

Transform::Transform(Vector3& pos, Vector3& scale, Vector3& rot) : _position(pos), _scale(scale), _rotate(rot)
{
}
