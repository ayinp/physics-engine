#include "collisionshape.h"
#include "gameObject.h"
using namespace ayin;

CollisionShape::CollisionShape(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc)
    :locFunc{locFunc}, velFunc{velFunc}
{

}

Vec2d CollisionShape::location()
{
    return locFunc();
}

Vec2d CollisionShape::velocity()
{
    return velFunc();
}
