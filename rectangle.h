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
    virtual shapeType type() override;
    virtual Vec2d Center() override;
    virtual vector<Vec2d> Corners() override;
    virtual void draw(mssm::Graphics& g) override;
    virtual void update(mssm::Graphics& g) override;
};

#endif // RECTANGLE_H
