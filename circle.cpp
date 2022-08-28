#include "circle.h"
#include "collisionshape.h"
using namespace ayin;

using namespace mssm;
Circle::Circle(Vec2d location, int rad)
    :CollisionShape(location), rad{rad}
{

}

ShapeType Circle::type()
{
    return ShapeType::oval;
}

Vec2d Circle::center()
{
    return location;
}

void Circle::draw(mssm::Graphics &g)
{
    g.ellipse(location, rad*2, rad*2, WHITE);
    g.ellipse(center(), 5, 5, RED, RED);
}
