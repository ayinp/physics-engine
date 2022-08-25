#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "collisionshape.h"

class MyRectangle : CollisionShape
{
public:
    int width;
    int height;
public:
    MyRectangle(Vec2d location, int width, int height);
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    vector<Vec2d> corners();
    virtual void draw(mssm::Graphics& g) override;
};

#endif // RECTANGLE_H
