#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H
#include "collisionshape.h"

namespace ayin{

class PolygonShape : public CollisionShape
{
public:
    vector<Vec2d> points;
public:
    PolygonShape(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc,  vector<Vec2d> points);
    virtual vector<Vec2d> corners() = 0;
};

}
#endif // POLYGONSHAPE_H
