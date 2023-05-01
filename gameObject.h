#ifndef OBJECT_H
#define OBJECT_H
#include "collisionshape.h"
#include <functional>
#include "collisioninfo.h"
#include "component.h"
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
    vector<unique_ptr<Component>> components;
    CollisionShape* hitBox;
    Vec2d lastLoc;
public:
    bool affectedByGravity = false;
    bool wrapInX = false;
    bool wrapInY = false;
    Vec2d location;
    Vec2d velocity = {0,0};
    Vec2d acceleration = {0,0};
    Vec2d netForce = {0,0};
    Vec2d movementForce = {0,0};
    vector<CollisionInfo> collisionInfos;
    function<void(CollisionInfo)> collisionEnter;
    function<void(CollisionInfo)> collisionLeave;
    function<void(CollisionInfo)> collisionStay;
    function<void(GameObject*, mssm::Graphics& g, Camera& c)> addUpdate;
public:
    GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void (CollisionInfo)> onCollisionEnter = nullptr,
               function<void (CollisionInfo)> onCollisionLeave = nullptr, function<void (CollisionInfo)> onCollisionStay = nullptr,
               function<void (GameObject *, mssm::Graphics &, Camera &)> addUpdate = nullptr);
    GameObject(const GameObject& other);
    void generateHitbox(ShapeType hitboxShape);
    void onCollisionEnter(CollisionInfo info);
    void onCollisionLeave(CollisionInfo info);
    void onCollisionStay(CollisionInfo info);
    void draw(Camera& c);
    void update(mssm::Graphics& g, Camera &c, Vec2d gravity);
    bool isDead() const {return dead;};
    Vec2d momentum();
    void addTag(string tag ){tags.push_back(tag);};
    bool hasTag(string tag){
        return find(tags.begin(), tags.end(), tag) != tags.end();
    };
    void setElasticity(double x){elasticity = x;};
    void setMass(double x){mass = x;};
    void kill(){dead = true;};
    bool isDead(){return dead;};
    CollisionShape* getHitbox() const {return hitBox;};
    double getWidth() const {return width;};
    double getHeight() const {return height;};
    void addComponent(unique_ptr<Component> c){components.push_back(std::move(c));};
    template<typename T>
    T* getComponent(string name);
    double getElasticity() const {return elasticity;};
    void setLastLoc(Vec2d l){lastLoc = l;};
    Vec2d getLastLoc(){return lastLoc;};
    CollisionInfo* getCollisionInfo(GameObject* him);
    bool canMove(mssm::Graphics& g, Camera &c, Vec2d vel);
    void normalCalcs();
};

template<typename T>
T *GameObject::getComponent(string name)
{
    for(int i = 0; i < components.size(); i++){
        if(components[i]->name == name){
            return dynamic_cast<T*>(components[i].get());
        }
    }
    //at somepoint I should make them not able to have the same name but that isnt important rn
    return nullptr;
}

}






#endif // OBJECT_H
