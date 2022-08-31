#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"

namespace ayin {

class GameObject
{
public:
    bool isStatic{true};
    Vec2d location;
    CollisionShape* hitBox(Vec2d(location));
public:
    GameObject();
};

}

#endif // OBJECT_H
