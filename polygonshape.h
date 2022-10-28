#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H
#include "collisionshape.h"

namespace ayin{

class PolygonShape : public CollisionShape
{
public:
    PolygonShape(std::function<Vec2d()> locFunc);
    virtual vector<Vec2d> corners() = 0;
};

}
#endif // POLYGONSHAPE_H
