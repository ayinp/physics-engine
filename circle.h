#ifndef OVAL_H
#define OVAL_H

#include "collisionshape.h"
namespace ayin {

class Circle : public CollisionShape
{
public:
    int rad;
public:
    Circle(Vec2d location, int rad);
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual void draw(mssm::Graphics& g) override;
};
}

#endif // OVAL_H
