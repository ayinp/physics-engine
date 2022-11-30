#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"
#include <functional>
#include "collisioninfo.h"

namespace ayin {

class GameObject
{
private:
    double width;
    double height;
    double elasticity = 1;
    double mass = 1;
    bool dead = false;
    vector<string> tags;
    CollisionShape* hitBox;
    Vec2d lastLoc;
public:
    bool affectedByGravity = false;
    bool wrapInX = false;
    bool wrapInY = false;
    Vec2d location;
    Vec2d velocity = {0,0};
    Vec2d acceleration = {0,0};
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionEnter;
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionLeave;
    function<void(GameObject*, GameObject*, CollisionInfo)> collisionStay;
public:
    GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionEnter = nullptr,
               function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionLeave = nullptr, function<void (GameObject *, GameObject *, CollisionInfo)> onCollisionStay = nullptr);
    GameObject(const GameObject& other);
    void generateHitbox(ShapeType hitboxShape);
    void onCollisionEnter(GameObject& heHitMe, CollisionInfo info);
    void onCollisionLeave(GameObject& heHitMe, CollisionInfo info);
    void onCollisionStay(GameObject& heHitMe, CollisionInfo info);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics &g, Vec2d gravity);
    bool isDead() const {return dead;};
    Vec2d momentum();
    void addTag(string tag){tags.push_back(tag);};
    bool hasTag(string tag){
        return find(tags.begin(), tags.end(), tag) != tags.end();
    };
    void setElasticity(double x){elasticity = x;};
    void setMass(double x){mass = x;};
    void kill(){dead = true;};
    bool isDead(){return dead;};
    CollisionShape* getHitbox() const {return hitBox;}
};

}

#endif // OBJECT_H
