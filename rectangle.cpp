#include "rectangle.h"

using namespace mssm;

MyRectangle::MyRectangle(Vec2d location, int width, int height)
    :CollisionShape(location), width{width}, height{height}
{

}

Vec2d MyRectangle::Center()
{
    return {location.x + (width/2), location.y + (height/2)};
}

vector<Vec2d> MyRectangle::Corners()
{
    Vec2d topLeft = location;
    Vec2d topRight = {location.x + width, location.y};
    Vec2d bottomLeft = {location.x, location.y + height};
    Vec2d bottomRight = {location.x + width, location.y + height};

    return {topLeft, topRight, bottomLeft, bottomRight};
}

void MyRectangle::draw(Graphics &g)
{
    g.rect(location, width, height, WHITE, WHITE);
    g.points(Corners(), RED);
    g.point(Center(), YELLOW);
}
