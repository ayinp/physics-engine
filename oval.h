#ifndef OVAL_H
#define OVAL_H

#include "collisionshape.h"

class Oval : CollisionShape
{
public:
public:
    Oval(Vec2d location);
    virtual shapeType type() override;
    virtual Vec2d Center() override;
    virtual vector<Vec2d> Corners() override;
};

#endif // OVAL_H
