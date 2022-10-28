#include "gameObject.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <cmath>
#include <iostream>
using namespace ayin;
using namespace mssm;

GameObject::GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionEnter,
                       function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionLeave, function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionStay)
    :width{width}, height{height}, location{location}, collisionEnter{onCollisionEnter}, collisionLeave{onCollisionLeave},
      collisionStay{onCollisionStay}

{
    generateHitbox(hitboxShape);
}

GameObject::GameObject(const GameObject &other)
{
    width = other.width;
    height = other.height;
    elasticity = other.elasticity;
    mass = other.mass;
    isStatic = other.isStatic;
    bouncy = other.bouncy;
    affectedByGravity = other.affectedByGravity;
    wrapInX = other.wrapInX;
    wrapInY = other.wrapInY;
    location = other.location;
    lastLoc = other.lastLoc;
    velocity = other.velocity;
    if(isnan(velocity.x)){
        cout << "NOOOOOOOOOOOx" << endl;
    }
    if(isnan(velocity.y)){
        cout << "NOOOOOOOOOOOy" << endl;
    }
    acceleration = other.acceleration;
    hitBox = other.hitBox->clone([this](){return location;});
    collisionEnter = other.collisionEnter;
    collisionLeave = other.collisionLeave;
    collisionStay = other.collisionStay;
}

void GameObject::generateHitbox(ShapeType hitboxShape)
{
    switch(hitboxShape){
    case ShapeType::circle:{
        Circle* c = new Circle([this](){return location;}, width);
        hitBox = c;
        break;
    }
    case ShapeType::rectangle: {
        Rectangle* r = new Rectangle([this](){return location;}, width, height);
        hitBox = r;
        break;
    }
    case ShapeType::triangle:{
        Triangle* t = new Triangle([this](){return location;}, 0, 0, width, height);
        hitBox = t;
        break;
    }
    }
}

void GameObject::onCollisionEnter(GameObject& heHitMe, CollisionInfo info)
{
    if(collisionEnter){
        collisionEnter(this, &heHitMe, info);
    }

}

void GameObject::onCollisionLeave(GameObject& heHitMe, CollisionInfo info)
{
    if(collisionLeave){
        collisionLeave(this, &heHitMe, info);
    }
}

void GameObject::onCollisionStay(GameObject& heHitMe, CollisionInfo info)
{
    if(collisionStay){
        collisionStay(this, &heHitMe, info);
    }
}

void GameObject::draw(mssm::Graphics &g)
{
    hitBox->draw(g);
}

void GameObject::update(Graphics& g, Vec2d gravity)
{
    lastLoc = location;
    location = location + velocity;

    Vec2d a = {0,0};
    if(isnan(velocity.x)){
        cout << "NOOOOOOOOOOOx" << endl;
    }
    if(isnan(velocity.y)){
        cout << "NOOOOOOOOOOOy" << endl;
    }
    if(affectedByGravity){
        a = acceleration + (gravity * mass);
    }
    else{
        a = acceleration;
    }

    velocity = velocity + a;



    if(wrapInX){
        if(location.x + width/2 < 0){
            location.x = g.width() + width/2;
        }
        if(location.x - width/2 > g.width()){
            location.x = 0 - width/2;
        }
    }
    if(wrapInY){
        if(location.y + height/2 < 0){
            location.y = g.height() + height/2;
        }
        if(location.y - height/2 > g.height()){
            location.y = 0 - height/2;
        }
    }
}

Vec2d GameObject::momentum()
{
    return mass*velocity;
}
