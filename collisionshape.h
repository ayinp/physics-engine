#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include "camera.h"
#include "graphics.h"
#include <functional>


namespace ayin {

enum ShapeType
{
    rectangle,
    triangle,
    polygon,
    circle
};

class CollisionShape
{
private:
    std::function<Vec2d()> locFunc;
    std::function<Vec2d()> velFunc;
public:
    Vec2d offset = {0,0};

    CollisionShape(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) = 0;
    Vec2d location();
    Vec2d velocity();
    virtual ShapeType type() = 0;
    virtual Vec2d center() = 0;
    virtual void draw(Camera& c, mssm::Color color = mssm::WHITE) = 0;
};

}

#endif // COLLISIONSHAPE_H
