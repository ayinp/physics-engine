#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "polygonshape.h"

namespace ayin{

class Polygon : public PolygonShape
{
public:
    Vec2d centerOfMass;
public:
    Polygon(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc, vector<Vec2d> points);
    virtual CollisionShape* clone(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc) override;
    virtual ShapeType type() override;
    virtual Vec2d center() override;
    virtual vector<Vec2d> corners() override;
    virtual void draw(Camera& c,  mssm::Color color = mssm::WHITE) override;
    void calcCenterOfMass();
};
}

#endif // TRIANGLE_H
