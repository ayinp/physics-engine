#include "infopair.h"

using namespace ayin;

InfoPair::InfoPair(CollisionInfo info1, CollisionInfo info2, int id)
    :info1{info1}, info2{info2}, id{id}
{

}

void InfoPair::kill()
{
    dead = true;
    info1.dead = true;
    info2.dead = true;
}

void InfoPair::impulseHandler()
{

    if(info1.obj2->isStatic()){
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
    }


}
