#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygonshape.h"

namespace ayin{
class Rectangle : public PolygonShape
{
public:
    double width;
    double height;
public:
    Rectangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, vector<Vec2d> points);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(Camera& c,  mssm::Color color = mssm::WHITE) override;
    Vec2d topLeft();
    Vec2d topRight();
    Vec2d bottomLeft();
    Vec2d bottomRight();
    double setHeight();
    double setWidth();
};
}

#endif // RECTANGLE_H
