#include "rectangle.h"

using namespace mssm;
using namespace ayin;

Rectangle::Rectangle(Vec2d location, int width, int height)
    :CollisionShape(location), width{width}, height{height}
{

}

ShapeType Rectangle::type()
{
    return ShapeType::rectangle;
}

Vec2d Rectangle::center()
{
    return location;
}

vector<Vec2d> Rectangle::corners()
{
    Vec2d topLeft = {location.x - width/2, location.y - height/2};
    Vec2d topRight = {location.x + width/2, location.y - height/2};
    Vec2d bottomLeft = {location.x - width/2, location.y + height/2};
    Vec2d bottomRight = {location.x + width/2, location.y + height/2};

    return {topLeft, topRight, bottomLeft, bottomRight};
}

void Rectangle::draw(Graphics &g)
{
    g.rect({location.x-width/2, location.y-height/2}, width, height, WHITE, WHITE);
    for(int i = 0; i < corners().size(); i++){
        g.ellipse(corners()[i], 5, 5, RED, RED);
    }
    g.ellipse(center(), 5, 5, RED, RED);

}
