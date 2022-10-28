#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include "graphics.h"
#include <functional>


namespace ayin {

enum ShapeType
{
    rectangle,
    triangle,
    circle
};

class CollisionShape
{
private:
    std::function<Vec2d()> locFunc;
public:
    CollisionShape(std::function<Vec2d()> locFunc);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc) = 0;
    Vec2d location();
    virtual ShapeType type() = 0;
    virtual Vec2d center() = 0;
    virtual void draw(mssm::Graphics& g, mssm::Color color = mssm::WHITE) = 0;
};

}

#endif // COLLISIONSHAPE_H
