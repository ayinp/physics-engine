#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "polygonshape.h"

namespace ayin{

class Rectangle : public PolygonShape
{
public:
    int width;
    int height;
public:
    Rectangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc,  int width, int height);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(mssm::Graphics& g,  mssm::Color color = mssm::WHITE) override;
    Vec2d topLeft();
    Vec2d topRight();
    Vec2d bottomLeft();
    Vec2d bottomRight();
};
}

#endif // RECTANGLE_H
