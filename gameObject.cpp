#include "gameObject.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include <cmath>
#include <iostream>
#include "playerFunctions.h"
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
        Vec2d normal = -info.normal;
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
//    affectedByGravity = false;
    if(collisionStay){
        collisionStay(info);
    }
    else{
    }


}

void GameObject::draw(Camera& c)
{

//    c.line(location, location + 100*velocity, YELLOW);
//    c.line(location, location + 100*velocity, RED);
    for(int i = 0; i < collisionInfos.size(); i++){
        c.line(location, location +collisionInfos[i].normal*50, ORANGE);
    }
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
    c.ellipse(location, 20, 20, PURPLE, PURPLE);
    c.line(location, location + 100*velocity, PURPLE);

}

void GameObject::update(Graphics &g, Vec2d gravity)
{
    netForce = {0,0};
    for(int i = 0; i < components.size(); i++){
        components[i]->update();
    }
    lastLoc = location;


    if(affectedByGravity){
        netForce += gravity;
    }
    playerMovement(g, this);

    normalCalcs();
    acceleration = netForce/mass;
    velocity = velocity + acceleration;
    location = location + velocity;


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

//    if(addUpdate){
//        addUpdate(this, g);
//    }
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

bool GameObject::canMove(Graphics& g, Camera& c, Vec2d vel)
{
    //returns true if you can move in the direction of vel
    return all_of(collisionInfos.begin(), collisionInfos.end(), [this, vel, &c, &g](auto& info)
    {
        if(dot(vel.unit(), info.normal) <= 0.015){
            return true;
        }
        g.cout<<dot(vel.unit(), info.normal)<<endl;
        c.line(location, location + info.normal*75, YELLOW);
        return false;
    });

}

void GameObject::normalCalcs()
{
    for(int i = 0; i < collisionInfos.size(); i++){
        Vec2d n = collisionInfos[i].normal.unit();
        double d = dot(n, netForce);
        netForce -= d*n;
    }
}




