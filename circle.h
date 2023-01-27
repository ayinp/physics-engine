#ifndef OVAL_H
#define OVAL_H

#include "collisionshape.h"
namespace ayin {

class Circle : public CollisionShape
{
public:
    int rad;
public:
    Circle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, int rad);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual void draw(Camera& c,  mssm::Color color = mssm::WHITE) override;
};
}

#endif // OVAL_H
