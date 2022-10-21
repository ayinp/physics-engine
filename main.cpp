#include <iostream>
#include "graphics.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "vec2d.h"
#include "collision.h"
#include "world.h"
//#include "paths.h"

using namespace std;
using namespace mssm;
using namespace ayin;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

Vec2d perp(Vec2d v){
    return {v.y, -v.x};
}

void onCollision(GameObject* me, GameObject* heHitMe, CollisionInfo info){

//        me->velocity= -0.85 * me->velocity;

//        if(abs(me->velocity.y) < 0.1){
//            me->velocity.y = 0;
//        }
//        if(abs(me->velocity.x) < 0.1){
//            me->velocity.x = 0;
//        }

    me->location = me->lastLoc;
    Vec2d normal = perp(me->location - info.collisionPoint);

    Vec2d newX = normal * (dotProduct(normal, me->velocity)/dotProduct(normal, normal));
    Vec2d newY = me->velocity - newX;

    me->velocity = (newX - newY);

}



int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);



    World world({0, 0.5});


    for(int i = 0; i < 10; i++){

        Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
        int width = g.randomInt(10, 100);
        GameObject obj(location, width, width, ShapeType::circle, onCollision);
        obj.velocity = {0,0}/*{g.randomDouble(-5, 5), g.randomDouble(-5, 5)}*/;
        obj.affectedByGravity = false;

        world.objects.push_back(obj);
    }

    world.objects[0].velocity = {0, 0};
    world.objects[0].affectedByGravity = false;

    Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
    GameObject obj(location, 50, 50 , ShapeType::circle, onCollision);
    obj.affectedByGravity = false;
    obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
    obj.acceleration = {0,0};
    obj.wrapInX = true;
    obj.wrapInY = true;


    world.objects.push_back(obj);
    while (g.draw()) {
        world.draw(g);
        world.update(g);
        world.objects[0].location = g.mousePos();

    }

    return 0;
}


