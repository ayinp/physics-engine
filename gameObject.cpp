#include "gameObject.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <cmath>
#include <iostream>
using namespace ayin;
using namespace mssm;



GameObject::GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void(CollisionInfo)> onCollisionEnter,
                       function<void(CollisionInfo)> onCollisionLeave, function<void(CollisionInfo)> onCollisionStay,
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

void GameObject::onCollisionEnter(CollisionInfo info)
{

    if(collisionEnter){
        collisionEnter(info);
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

void GameObject::onCollisionLeave(CollisionInfo info)
{

    if(collisionLeave){
        collisionLeave(info);
    }

}

void GameObject::onCollisionStay(CollisionInfo info)
{
    if(collisionStay){
        collisionStay(info);
    }
}

void GameObject::draw(Camera& c)
{

    c.line(location, location + 100*velocity, YELLOW);
    c.line(location, location + 100*velocity, RED);
    if(affectedByGravity){
        hitBox->draw(c, WHITE);
    }
    else{
        hitBox->draw(c, RED);
    }
    c.text(Vec2d{10,10}+location, 50, to_string(collisionInfos.size()));
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

CollisionInfo *GameObject::getCollisionInfo(GameObject *him)
{
    for(int i = 0; i < collisionInfos.size(); i++){
        if(him == collisionInfos[i].obj1||him == collisionInfos[i].obj2){
            return &collisionInfos[i];
        }
    }
    return nullptr;
}

bool GameObject::canMove(Vec2d vel)
{
    //returns true if you can move in the direction of vel
    return any_of(collisionInfos.begin(), collisionInfos.end(), [vel](auto& info){return dot(vel, info.normal) <= 0;});

}




