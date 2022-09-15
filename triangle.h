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
    Triangle(Vec2d location, bool isRightTriangle, bool slopeLeft, int width, int height);
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(mssm::Graphics& g) override;
    Vec2d centerOfMass();
};
}

#endif // TRIANGLE_H
