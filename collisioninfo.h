#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H



#include "vec2d.h"

namespace ayin {

class GameObject;

class CollisionInfo
{
private:
    Vec2d collisionPoint;
    Vec2d normal;
public:
    GameObject* obj1;
    GameObject* obj2;
    bool dead = false;
public:
    void reverse();
    void setColPoint(Vec2d colpt);
    void setNormal(Vec2d n);
    void kill(){dead = true;};
    void checkNorm();
    Vec2d getColPoint(){return collisionPoint;};
    Vec2d getNormal(){return normal;};
    bool isDead(){return dead;};
};

}

#endif // COLLISIONINFO_H
