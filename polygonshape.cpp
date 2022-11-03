#include "polygonshape.h"
using namespace ayin;
PolygonShape::PolygonShape(std::function<Vec2d ()> locFunc, std::function<Vec2d()> velFunc)
    :CollisionShape(locFunc, velFunc)
{

}
