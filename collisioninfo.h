#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H



#include "vec2d.h"

namespace ayin {

class GameObject;

class CollisionInfo
{
public:
    Vec2d collisionPoint;
    Vec2d normal;
    GameObject* obj1;
    GameObject* obj2;
    bool dead = false;
public:
    void reverse();

};

}

#endif // COLLISIONINFO_H
