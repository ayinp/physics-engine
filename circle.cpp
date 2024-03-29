#include "circle.h"
#include "collisionshape.h"
using namespace ayin;

using namespace mssm;
Circle::Circle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, int rad)
    :CollisionShape(locFunc, velFunc), rad{rad}
{

}

CollisionShape *Circle::clone(std::function<Vec2d ()> locFunc, std::function<Vec2d()> velFunc)
{
    return new Circle(locFunc, velFunc, rad);
}

ShapeType Circle::type()
{
    return ShapeType::circle;
}

Vec2d Circle::center()
{
    return location();
}

void Circle::draw(Camera& c, Color color)
{
    c.ellipse(location(), rad*2, rad*2, color, color);
    c.ellipse(center(), 5, 5, RED, RED);
}
