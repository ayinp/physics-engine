#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vec2d.h"
#include "graphics.h"
#include "polygonshape.h"
#include <functional>

namespace ayin{

class Triangle : public PolygonShape
{
public:
public:
    Triangle(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, std::vector<Vec2d> points);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(Camera& c,  mssm::Color color = mssm::WHITE) override;
    Vec2d centerOfMass();
};
}

#endif // TRIANGLE_H
