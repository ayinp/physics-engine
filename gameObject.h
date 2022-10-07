#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"
#include <functional>

namespace ayin {

class GameObject
{
public:
    int width;
    int height;
    bool isStatic;
    Vec2d location;
    Vec2d velocity;
    Vec2d acceleration;
    CollisionShape* hitBox;
    function<void(GameObject*, GameObject*)> collisionEnter;
    function<void(GameObject*, GameObject*)> collisionLeave;
    function<void(GameObject*, GameObject*)> collisionStay;
public:
    GameObject(Vec2d location, CollisionShape *hitBox, function<void (GameObject *, GameObject*)> onCollisionEnter = nullptr,
               function<void (GameObject *, GameObject*)> onCollisionLeave = nullptr, function<void (GameObject *, GameObject*)> onCollisionStay = nullptr);
    void onCollisionEnter(GameObject& heHitMe);
    void onCollisionLeave(GameObject& heHitMe);
    void onCollisionStay(GameObject& heHitMe);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
};

}

#endif // OBJECT_H
