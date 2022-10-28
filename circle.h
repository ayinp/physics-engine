#ifndef OVAL_H
#define OVAL_H

#include "collisionshape.h"
namespace ayin {

class Circle : public CollisionShape
{
public:
    int rad;
public:
    Circle(std::function<Vec2d()> locFunc, int rad);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual void draw(mssm::Graphics& g,  mssm::Color color = mssm::WHITE) override;
};
}

#endif // OVAL_H
