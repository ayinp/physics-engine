#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "collisionshape.h"

namespace ayin{

class Triangle : public CollisionShape
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
    Vec2d centerOfMass();
    vector<Vec2d> corners();
    virtual void draw(mssm::Graphics& g) override;
};
}

#endif // TRIANGLE_H
