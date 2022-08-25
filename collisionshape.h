#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include "graphics.h"

enum ShapeType
{
    rectangle,
    triangle,
    oval,
};

class CollisionShape
{
public:
    Vec2d location;
    Vec2d velocity;
    Vec2d acceleration;
public:
    CollisionShape(Vec2d location);
    virtual ShapeType type() = 0;
    virtual Vec2d center() = 0;
    virtual void draw(mssm::Graphics& g) = 0;
};

#endif // COLLISIONSHAPE_H
