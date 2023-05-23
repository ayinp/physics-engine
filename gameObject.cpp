#include "gameObject.h"
#include "circle.h"
#include "collision.h"
#include "polygon.h"
#include "rectangle.h"
#include "triangle.h"
#include <cmath>
#include <iostream>
#include "playerFunctions.h"
using namespace ayin;
using namespace mssm;


GameObject::GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, bool isStatic, function<void (CollisionInfo)> onCollisionEnter,
                       function<void (CollisionInfo)> onCollisionLeave, function<void (CollisionInfo)> onCollisionStay,
                       function<void (GameObject *, mssm::Graphics &, Camera &)> addUpdate)
    :width{width}, height{height}, location{location}, stat{isStatic}, collisionEnter{onCollisionEnter}, collisionLeave{onCollisionLeave},
      collisionStay{onCollisionStay}, addUpdate{addUpdate}

{
    hitBox = generateHitbox(hitboxShape);
    lastLoc = location;
}

GameObject::GameObject(Vec2d location, vector<Vec2d> points, ShapeType hitboxShape, bool isStatic, function<void (CollisionInfo)> onCollisionEnter,
                       function<void (CollisionInfo)> onCollisionLeave, function<void (CollisionInfo)> onCollisionStay,
                       function<void (GameObject*, Graphics& g, Camera& c)> addUpdate)
    :points{points}, location{location}, stat{isStatic}, collisionEnter{onCollisionEnter}, collisionLeave{onCollisionLeave},
      collisionStay{onCollisionStay}, addUpdate{addUpdate}

{
    calcWidth();
    calcHeight();
    hitBox = generateHitbox(hitboxShape);
    lastLoc = location;

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

CollisionShape* GameObject::generateHitbox(ShapeType hitboxShape)
{
    switch(hitboxShape){
    case ShapeType::circle:{
        Circle* c = new Circle([this](){return location;}, [this](){return velocity;}, width);
        return c;
        break;
    }
    case ShapeType::rectangle: {
        if(points.size()!= 0){
            Rectangle* r = new Rectangle([this](){return location;}, [this](){return velocity;}, points);
            return r;
            break;
        }
        else{
            Rectangle* r = new Rectangle([this](){return location;}, [this](){return velocity;}, width, height);
            return r;
            break;
        }
    }
    case ShapeType::triangle:{
        if(points.size()!= 0){
            Triangle* t = new Triangle([this](){return location;}, [this](){return velocity;}, points);
            return t;
            break;
        }
        else{
            cout << "you did not add any points to this triangle!" << endl;
        }
    }
    case ShapeType::polygon:{
        if(points.size()!= 0){
            Polygon* p = new Polygon([this](){return location;}, [this](){return velocity;}, points);
            return p;
            break;
        }
        else{
            cout << "you did not add any points to this polygon!" << endl;
        }
    }
    }
}

void GameObject::onCollisionEnter(CollisionInfo info)
{
    if(collisionEnter){
        collisionEnter(info);
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


Vec2d newLoc(Vec2d velocity, Vec2d lastLoc, CollisionInfo info, int c){
    Vec2d retLoc = lastLoc;
    CollisionInfo randInfo;
    CollisionShape* newHB = info.obj1->generateHitbox(info.obj1->getHitbox()->type());

    if(c < 10){
        newHB->offset = lastLoc+0.5*velocity-info.obj1->location;
        if(collides(newHB, info.obj2->getHitbox(), randInfo,0)){
            retLoc = lastLoc + 0.5*velocity;
            return newLoc(0.5*velocity, lastLoc, info, c+1);
        }
        else{
            return lastLoc;
        }
    }
    else if(c < 20){
        newHB->offset = lastLoc-2*velocity-info.obj1->location;
        if(collides(newHB, info.obj2->getHitbox(), randInfo,0)){
            retLoc = lastLoc - 0.5*velocity;
            return newLoc(2*velocity, lastLoc, info, c+1);
        }
        else{
            return lastLoc;
        }
    }
    else{
        return lastLoc;
    }


}

void GameObject::impulseHandler(mssm::Graphics &g, CollisionInfo info, bool& cols)
{
    if(info.obj2->isStatic()){
        Vec2d normal = -info.getNormal();
        Vec2d newX = normal * (-dotProduct(normal, velocity)/dotProduct(normal, normal));
        Vec2d newY = velocity + newX;
        if(dot(normal, velocity) < 0){
            location = (newLoc(velocity, lastLoc, info, 0));
            lastLoc = location;
            velocity = (newY + elasticity*newX)/mass;
            cols = true;
            if(velocity.magnitude() < 1){
                velocity = {0,0};
            }
        }
        else if(dot(normal.unit(), velocity.unit()) == -1){
            velocity = (newY + elasticity*newX);
            cols = true;
            if(velocity.magnitude() < 1){
                velocity = {0,0};
            }
        }

    }
    else{
        double m1 = mass;
        double m2 = info.obj2->mass;

        Vec2d VI1 = velocity;
        Vec2d VI2 = info.obj2->velocity;

        Vec2d VF1 = ((m1-m2)/(m1+m2))*VI1 + ((2*m2)/(m1+m2))*VI2;
        Vec2d VF2 = ((m2-m1)/(m2+m1))*VI2 + ((2*m1)/(m2+m1))*VI1;

        velocity = VF1;
        info.obj2->velocity = VF2;
    }s


}

void GameObject::draw(Camera& c)
{

    //    c.line(location, location + 100*velocity, YELLOW);
    //    c.line(location, location + 100*velocity, RED);
    for(int i = 0; i < collisionInfos.size(); i++){
        c.line(location, location +collisionInfos[i].getNormal()*50, ORANGE);
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
    //    c.ellipse(location, 20, 20, PURPLE, PURPLE);
        c.line(location, location + 100*velocity, PURPLE);
}

void GameObject::update(Graphics &g, Camera& c, Vec2d gravity)
{
    for(int i = 0; i < components.size(); i++){
        components[i]->update();
    }
    lastLoc = location;

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

    if(addUpdate){
        addUpdate(this, g, c);
    }
}


Vec2d GameObject::momentum()
{
    return mass*velocity;
}

CollisionInfo *GameObject::getCollisionInfo(GameObject *him)
{
    for(int i = 0; i < collisionInfos.size(); i++){
        if(/*him == collisionInfos[i].obj1||*/him == collisionInfos[i].obj2){
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
        if(dot(vel.unit(), info.getNormal()) <= 0.015){
            return true;
        }
        g.cout<<dot(vel.unit(), info.getNormal())<<endl;
        c.line(location, location + info.getNormal()*75, YELLOW);
        return false;
    });

}

void GameObject::normalCalcs(Graphics& g)
{
    vector<Vec2d> normals;
    for(int i = 0; i < collisionInfos.size(); i++){
        Vec2d n = collisionInfos[i].getNormal();
        double d = dot(n,  netForce);
        normals.push_back(d*n);
        if(d > 0){
            netForce -= d*n;
        }
    }
}

void GameObject::appliedForce(Vec2d grav)
{
    netForce = {0,0};
    if(affectedByGravity){
        netForce += grav*mass;
    }
    netForce += movementForce;
    //    if(abs(netForce.x) < 0.01){
    //        netForce.x = 0;
    //    }
    //    if(abs(netForce.y) < 0.01){
    //        netForce.y = 0;
    //    }


}

void GameObject::calcWidth()
{

}

void GameObject::calcHeight()
{

}





