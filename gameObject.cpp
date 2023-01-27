#include "gameObject.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <cmath>
#include <iostream>
using namespace ayin;
using namespace mssm;

GameObject::GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionEnter,
                       function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionLeave, function<void(GameObject*, GameObject*, CollisionInfo)> onCollisionStay,
                       function<void(GameObject*, Camera& c)> addUpdate)
    :width{width}, height{height}, location{location}, collisionEnter{onCollisionEnter}, collisionLeave{onCollisionLeave},
      collisionStay{onCollisionStay}, addUpdate{addUpdate}

{
    generateHitbox(hitboxShape);
}

GameObject::GameObject(const GameObject &other)
{
    width = other.width;
    height = other.height;
    elasticity = other.elasticity;
    mass = other.mass;
    affectedByGravity = other.affectedByGravity;
    wrapInX = other.wrapInX;
    wrapInY = other.wrapInY;
    location = other.location;
    lastLoc = other.lastLoc;
    velocity = other.velocity;
    acceleration = other.acceleration;
    hitBox = other.hitBox->clone([this](){return location;}, [this](){return velocity;});
    collisionEnter = other.collisionEnter;
    collisionLeave = other.collisionLeave;
    collisionStay = other.collisionStay;
}

void GameObject::generateHitbox(ShapeType hitboxShape)
{
    switch(hitboxShape){
    case ShapeType::circle:{
        Circle* c = new Circle([this](){return location;}, [this](){return velocity;}, width);
        hitBox = c;
        break;
    }
    case ShapeType::rectangle: {
        Rectangle* r = new Rectangle([this](){return location;}, [this](){return velocity;}, width, height);
        hitBox = r;
        break;
    }
    case ShapeType::triangle:{
        Triangle* t = new Triangle([this](){return location;}, [this](){return velocity;}, 0, 0, width, height);
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
    else{
        location = lastLoc;

        Vec2d normal = perp(location - info.collisionPoint).unit();

        Vec2d newX = normal * (dotProduct(normal, velocity)/dotProduct(normal, normal));
        Vec2d newY = velocity - newX;

        velocity = (newX - elasticity*newY);


        if(abs(velocity.x) < 0.01){
            velocity.x = 0;

        }
        if(abs(velocity.y) < 0.01){
            velocity.y = 0;
        }

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

void GameObject::draw(Camera& c)
{
    c.line(location, location + 100*velocity, YELLOW);
    hitBox->draw(c);
    for(int i = 0; i < components.size(); i++){
        components[i]->draw(c);
    }
}

void GameObject::update(Camera& c, Vec2d gravity)
{
    for(int i = 0; i < components.size(); i++){
        components[i]->update();
    }

    lastLoc = location;

    Vec2d a = {0,0};

    if(affectedByGravity){
        a = acceleration + (gravity * mass);
    }
    else{
        a = acceleration;
    }

    velocity = velocity + a;
    location = location + velocity;

     c.line(location, location + 100*velocity, PURPLE);


    if(wrapInX){
        if(location.x + width/2 < 0){
            location.x = c.width() + width/2;
        }
        if(location.x - width/2 > c.width()){
            location.x = 0 - width/2;
        }
    }
    if(wrapInY){
        if(location.y + height/2 < 0){
            location.y = c.height() + height/2;
        }
        if(location.y - height/2 > c.height()){
            location.y = 0 - height/2;
        }
    }

    if(addUpdate){
        addUpdate(this, c);
    }
}

Vec2d GameObject::momentum()
{
    return mass*velocity;
}

