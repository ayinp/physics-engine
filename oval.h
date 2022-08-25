#ifndef OVAL_H
#define OVAL_H

#include "collisionshape.h"

class Oval : CollisionShape
{
public:
    int width;
    int height;
public:
    Oval(Vec2d location, int width, int height);
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual void draw(mssm::Graphics& g) override;
};

#endif // OVAL_H
