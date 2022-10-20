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

void onCollision(GameObject* me, GameObject* heHitMe){

//        me->velocity= -0.85 * me->velocity;

//        if(abs(me->velocity.y) < 0.1){
//            me->velocity.y = 0;
//        }
//        if(abs(me->velocity.x) < 0.1){
//            me->velocity.x = 0;
//        }

    me->location = me->lastLoc;
    Vec2d normal = perp(me->location - heHitMe->location);

    Vec2d newX = normal * (dotProduct(normal, me->velocity)/dotProduct(normal, normal));
    Vec2d newY = me->velocity - newX;

    me->velocity = (newX - newY);

}



int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);



    World world({0, 0.5});


    for(int i = 0; i < 2; i++){

        Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
        int width = g.randomInt(10, 100);
        GameObject obj(location, width, width, ShapeType::circle, onCollision);
        obj.velocity = {0,0}/*{g.randomDouble(-5, 5), g.randomDouble(-5, 5)}*/;
        obj.affectedByGravity = true;
        obj.wrapInX = true;
        world.objects.push_back(obj);


        //        if(i%3 == 0){
        //            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
        //            int width =  g.randomInt(10, 100);
        //            int height = g.randomInt(10, 100);
        //            GameObject obj(location, width, height, ShapeType::triangle, onCollision);
        //            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
        //            obj.affectedByGravity = true;
        //            obj.wrapInX = true;
        //            obj.wrapInY = true;
        ////            obj.mass = (width + height)/10;
        //            world.objects.push_back(obj);
        //        }
        //        else if(i%3 == 1){
        //            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
        //            int width = g.randomInt(10, 100);
        //            int height = g.randomInt(10, 100);
        //            GameObject obj(location, width, height, ShapeType::rectangle, onCollision);
        //            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
        //            obj.affectedByGravity = true;
        //            obj.wrapInX = true;
        //            obj.wrapInY = true;
        ////            obj.mass = (width + height)/10;
        //            world.objects.push_back(obj);
        //        }
        //        else if(i%3 == 2){
        //            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
        //            int width = g.randomInt(10, 100);
        //            GameObject obj(location, width, width, ShapeType::circle, onCollision);
        //            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
        //            obj.affectedByGravity = true;
        //            obj.wrapInX = true;
        //            obj.wrapInY = true;
        ////            obj.mass = (width + width)/10;
        //            world.objects.push_back(obj);
        //        }

    }

    world.objects[0].velocity = {0, 0};
    world.objects[0].affectedByGravity = false;

    Vec2d location = {g.width()/2, g.height() - 50};
    GameObject obj(location, g.width(), 50, ShapeType::rectangle, onCollision);
   obj.affectedByGravity = false;
    obj.velocity = {0,0};
    obj.acceleration = {0,0};


    world.objects.push_back(obj);
    while (g.draw()) {
        world.draw(g);
        world.update(g);
        world.objects[0].location = g.mousePos();

    }

    return 0;
}


