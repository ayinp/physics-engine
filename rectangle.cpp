#include "rectangle.h"

using namespace mssm;
using namespace ayin;

Rectangle::Rectangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, vector<Vec2d> points)
    :PolygonShape(locFunc, velFunc, points)
{
    setWidth();
    setHeight();
}

Rectangle::Rectangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, double width , double height)
    :PolygonShape(locFunc, velFunc), width{width}, height{height}
{
}

CollisionShape *Rectangle::clone(std::function<Vec2d ()> locFunc, std::function<Vec2d()> velFunc)
{
    return new Rectangle(locFunc, velFunc, points);
}

ShapeType Rectangle::type()
{
    return ShapeType::rectangle;
}

Vec2d Rectangle::center()
{
    return location();
}

vector<Vec2d> Rectangle::corners()
{
     return {topLeft(), bottomLeft(), bottomRight(), topRight()};
}

Vec2d Rectangle::topLeft()
{
    return {location().x - width/2, location().y - height/2};
}

Vec2d Rectangle::topRight()
{
    return {location().x + width/2, location().y - height/2};
}

Vec2d Rectangle::bottomLeft()
{
    return {location().x - width/2, location().y + height/2};
}

Vec2d Rectangle::bottomRight()
{
    return {location().x + width/2, location().y + height/2};
}

double Rectangle::setHeight()
{
    if(points.size() >= 2){
        if(points[0].y != points[1].y){
            height = abs(points[0].y-points[1].y);
        }
        else{
            height = abs(points[0].y-points[2].y);
        }
    }
}

double Rectangle::setWidth()
{
    if(points.size() >= 2){
        if(points[0].x != points[1].x){
            width = abs(points[0].x-points[1].x);
        }
        else{
            width = abs(points[0].x-points[2].x);
        }
    }
}

void Rectangle::draw(Camera& c, Color color)
{
    c.rect({location().x-width/2, location().y-height/2}, width, height, color);
    for(int i = 0; i < corners().size(); i++){
        c.ellipse(corners()[i], 3, 3, WHITE, WHITE);
        c.text(corners()[i] + Vec2d{5,-5}, 15, to_string(i), WHITE);
    }
    c.ellipse(center(), 5, 5, RED, RED);
}
