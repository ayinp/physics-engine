#include "rectangle.h"

using namespace mssm;
using namespace ayin;

Rectangle::Rectangle(Vec2d location, int width, int height)
    :PolygonShape(location), width{width}, height{height}
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
    return {topLeft(), bottomLeft(), bottomRight(), topRight()};
}

Vec2d Rectangle::topLeft()
{
    return {location.x - width/2, location.y - height/2};
}

Vec2d Rectangle::topRight()
{
    return {location.x + width/2, location.y - height/2};
}

Vec2d Rectangle::bottomLeft()
{
     return {location.x - width/2, location.y + height/2};
}

Vec2d Rectangle::bottomRight()
{
     return {location.x + width/2, location.y + height/2};
}

void Rectangle::draw(Graphics &g, Color color)
{
    g.rect({location.x-width/2, location.y-height/2}, width, height, color);
    for(int i = 0; i < corners().size(); i++){
        g.ellipse(corners()[i], 5, 5, RED, RED);
    }
    g.ellipse(center(), 5, 5, RED, RED);
}
