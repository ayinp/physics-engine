#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"
#include <functional>
#include "collisioninfo.h"

namespace ayin {

class GameObject
{
public:
    double width;
    double height;
    bool isStatic; 
    double mass = 1;
    bool bouncy;
    bool affectedByGravity;
    bool wrapInX;
    bool wrapInY;
    Vec2d location;
    Vec2d lastLoc;
    Vec2d velocity;
    Vec2d acceleration;
    CollisionShape* hitBox;
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionEnter;
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionLeave;
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionStay;
public:
    GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionEnter = nullptr,
               function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionLeave = nullptr, function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionStay = nullptr);
    void generateHitbox(ShapeType hitboxShape);
    void onCollisionEnter(GameObject& heHitMe, CollisionInfo info);
    void onCollisionLeave(GameObject& heHitMe, CollisionInfo info);
    void onCollisionStay(GameObject& heHitMe, CollisionInfo info);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics &g, Vec2d gravity);
    Vec2d momentum();
};

}

#endif // OBJECT_H
