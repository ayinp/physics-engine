#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygonshape.h"

namespace ayin{

class Triangle : public PolygonShape
{
public:
    bool isRightTriangle = true;
    bool slopeLeft = true;
    int height;
    int width;
public:
    Triangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, bool isRightTriangle, bool slopeLeft, int width, int height);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(mssm::Graphics& g,  mssm::Color color = mssm::WHITE) override;
    Vec2d centerOfMass();
};
}

#endif // TRIANGLE_H
