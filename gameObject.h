#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"

namespace ayin {

class GameObject
{
public:
    int width;
    int height;
    bool isStatic{true};
    Vec2d location;
    Vec2d velocity;
    CollisionShape* hitBox;
public:
    GameObject(Vec2d location, CollisionShape *hitBox);
    bool onCollisionEnter(GameObject HeHitMe);
    bool onCollisionLeave(GameObject HeHitMe);
    bool onCollisionStay(GameObject HeHitMe);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
};

}

#endif // OBJECT_H
