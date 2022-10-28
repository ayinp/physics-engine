#include "polygonshape.h"
using namespace ayin;
PolygonShape::PolygonShape(std::function<Vec2d ()> locFunc)
    :CollisionShape(locFunc)
{

}
