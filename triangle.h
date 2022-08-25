#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "collisionshape.h"

class Triangle : CollisionShape
{
public:
public:
    Triangle(Vec2d location);
    virtual shapeType type() override;
    virtual Vec2d Center() override;
    virtual vector<Vec2d> Corners() override;
};

#endif // TRIANGLE_H
