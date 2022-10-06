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
    function<void()> collisionEnter;
    function<void()> collisionLeave;
    function<void()> collisionStay;
public:
    GameObject(Vec2d location, CollisionShape *hitBox, function<void()> onCollisionEnter = nullptr,
               function<void()> onCollisionLeave = nullptr, function<void()> onCollisionStay = nullptr);
    void onCollisionEnter(GameObject HeHitMe);
    void onCollisionLeave(GameObject HeHitMe);
    void onCollisionStay(GameObject HeHitMe);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
};

}

#endif // OBJECT_H
