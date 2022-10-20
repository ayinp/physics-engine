#include "gameObject.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
using namespace ayin;
using namespace mssm;

GameObject::GameObject(Vec2d location, double width, double height, ShapeType hitboxShape, function<void(GameObject*, GameObject*)> onCollisionEnter,
                       function<void(GameObject*, GameObject*)> onCollisionLeave, function<void(GameObject*, GameObject*)> onCollisionStay)
    :width{width}, height{height}, location{location}, collisionEnter{onCollisionEnter}, collisionLeave{onCollisionLeave},
      collisionStay{onCollisionStay}

{
    generateHitbox(hitboxShape);
}

void GameObject::generateHitbox(ShapeType hitboxShape)
{
    switch(hitboxShape){
    case ShapeType::circle:{
        Circle* c = new Circle(location, width);
        hitBox = c;
        break;
    }
    case ShapeType::rectangle: {
        Rectangle* r = new Rectangle(location, width, height);
        hitBox = r;
        break;
    }
    case ShapeType::triangle:{
        Triangle* t = new Triangle(location, 0, 0, width, height);
        hitBox = t;
        break;
    }
    }
}

void GameObject::onCollisionEnter(GameObject& heHitMe)
{
    if(collisionEnter){
        collisionEnter(this, &heHitMe);
    }

}

void GameObject::onCollisionLeave(GameObject& heHitMe)
{
    if(collisionLeave){
        collisionLeave(this, &heHitMe);
    }
}

void GameObject::onCollisionStay(GameObject& heHitMe)
{
    if(collisionStay){
        collisionStay(this, &heHitMe);
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


    hitBox->location = location;
}

Vec2d GameObject::momentum()
{
    return mass*velocity;
}
