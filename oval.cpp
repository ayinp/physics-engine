#include "oval.h"
#include "collisionshape.h"
using namespace mssm;
Oval::Oval(Vec2d location, int width, int height)
    :CollisionShape(location), width{width}, height{height}
{

}

ShapeType Oval::type()
{
    return ShapeType::oval;
}

Vec2d Oval::center()
{
    return location;
}

void Oval::draw(mssm::Graphics &g)
{
    g.ellipse(location, width, height, WHITE, WHITE);
    g.ellipse(center(), 5, 5, RED, RED);
}
