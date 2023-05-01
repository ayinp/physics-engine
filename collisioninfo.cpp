#include "CollisionInfo.h"
#include "gameObject.h"

void ayin::CollisionInfo::reverse()
{
    normal = -normal;
    std::swap(obj1, obj2);
}

void ayin::CollisionInfo::setColPoint(Vec2d colpt)
{
    collisionPoint = colpt;
}

void ayin::CollisionInfo::setNormal(Vec2d n)
{
    normal = n;
}

void ayin::CollisionInfo::checkNorm()
{
    if(dot((obj1->location - obj2->location), normal) > 0){
        normal = -normal;
    }
}

