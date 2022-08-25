#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include "graphics.h"

enum shapeType
{
    rectangle,
    triangle,
    square
};

class CollisionShape
{
public:
    Vec2d location;
    Vec2d velocity;
    Vec2d acceleration;
public:
    CollisionShape(Vec2d location);
    virtual shapeType type() = 0;
    virtual Vec2d Center() = 0;
    virtual vector<Vec2d> Corners() = 0;
    virtual void draw(mssm::Graphics& g) = 0;
    virtual void update(mssm::Graphics& g) = 0;
};

#endif // COLLISIONSHAPE_H
