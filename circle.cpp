#include "circle.h"
#include "collisionshape.h"
using namespace ayin;

using namespace mssm;
Circle::Circle(std::function<Vec2d()> locFunc, int rad)
    :CollisionShape(locFunc), rad{rad}
{

}

CollisionShape *Circle::clone(std::function<Vec2d ()> locFunc)
{
    return new Circle(locFunc, rad);
}

ShapeType Circle::type()
{
    return ShapeType::circle;
}

Vec2d Circle::center()
{
    return location();
}

void Circle::draw(mssm::Graphics &g, Color color)
{
    g.ellipse(location(), rad*2, rad*2, color);
    g.ellipse(center(), 5, 5, RED, RED);
}
