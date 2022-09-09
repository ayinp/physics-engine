#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"

namespace ayin {

class GameObject
{
public:
    bool isStatic{true};
    Vec2d location;
    CollisionShape* hitBox;
public:
    GameObject(Vec2d location, CollisionShape *hitBox);
};

}

#endif // OBJECT_H
