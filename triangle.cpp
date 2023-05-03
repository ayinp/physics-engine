#include "triangle.h"
#include <functional>

using namespace mssm;
using namespace ayin;

Triangle::Triangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc,  vector<Vec2d> points)
    :PolygonShape(locFunc, velFunc, points)
{
}

CollisionShape *Triangle::clone(std::function<Vec2d ()> locFunc, std::function<Vec2d()> velFunc)
{
    return new Triangle(locFunc, velFunc, points);
}

ShapeType Triangle::type()
{
    return ShapeType::triangle;
}

Vec2d Triangle::center()
{
    return location();
}

vector<Vec2d> ayin::Triangle::corners()
{
    vector<Vec2d> c;
    for(int i = 0; i < points.size(); i++){
        c.push_back(points[i] + location());
    }
    return c;
}

Vec2d Triangle::centerOfMass()
{
    Vec2d c;
    for(int i = 0; i < points.size(); i++){
        c += points[i];
    }
    c = {c.x/3, c.y/3};
    c += location();
    return c;
}

//vector<Vec2d> expand(vector<Vec2d>, double);


void Triangle::draw(Camera& c, Color color)
{
    c.polygon(corners(), color);

    for(int i = 0; i < corners().size(); i++){
        c.ellipse(corners()[i], 3, 3, WHITE, WHITE);
        c.text(corners()[i] + Vec2d{5,-5}, 15, to_string(i), WHITE);
    }
    c.ellipse(center(), 5, 5, RED, RED);
    c.ellipse(centerOfMass(), 5, 5, BLUE, BLUE);
    c.text(centerOfMass() + Vec2d{5,-5}, 15, "TRIANGLE COM", BLUE);
}
