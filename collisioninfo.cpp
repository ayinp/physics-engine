#include "CollisionInfo.h"

void ayin::CollisionInfo::reverse()
{
    normal = -normal;
    std::swap(obj1, obj2);
}

