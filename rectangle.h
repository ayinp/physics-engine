#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "collisionshape.h"

namespace ayin{

class Rectangle : public CollisionShape
{
public:
    int width;
    int height;
public:
    Rectangle(Vec2d location, int width, int height);
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    vector<Vec2d> corners();
    Vec2d topLeft();
    Vec2d topRight();
    Vec2d bottomLeft();
    Vec2d bottomRight();
    virtual void draw(mssm::Graphics& g) override;
};
}

#endif // RECTANGLE_H
