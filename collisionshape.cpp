#include "collisionshape.h"
#include "gameObject.h"
using namespace ayin;

CollisionShape::CollisionShape(std::function<Vec2d()> locFunc)
    :locFunc{locFunc}
{

}

Vec2d CollisionShape::location()
{
    return locFunc();
}
