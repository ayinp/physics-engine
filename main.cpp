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

void onCollision(GameObject* me, GameObject* heHitMe){
    me->velocity.y = -0.85 * me->velocity.y;


    // momentum = mass*velocity
    //
//    me->affectedByGrav ity = false;
}



int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);



    World world({0, 0.5});


    for(int i = 0; i < 6; i++){
        if(i%3 == 0){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
            int width =  g.randomInt(10, 100);
            int height = g.randomInt(10, 100);
            GameObject obj(location, width, height, ShapeType::triangle, onCollision);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            obj.affectedByGravity = true;
             obj.wrapInX = true;
              obj.wrapInY = true;
            world.objects.push_back(obj);
        }
        else if(i%3 == 1){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
            int width = g.randomInt(10, 100);
            int height = g.randomInt(10, 100);
            GameObject obj(location, width, height, ShapeType::rectangle, onCollision);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            obj.affectedByGravity = true;
            obj.wrapInX = true;
            obj.wrapInY = true;
            world.objects.push_back(obj);
        }
        else if(i%3 == 2){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height() - 500)};
            int width = g.randomInt(10, 100);
            GameObject obj(location, width, width, ShapeType::circle, onCollision);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            obj.affectedByGravity = true;
             obj.wrapInX = true;
             obj.wrapInY = true;
            world.objects.push_back(obj);
        }

    }

    world.objects[0].velocity = {0, 0};
    world.objects[0].affectedByGravity = false;

    Vec2d location = {g.width()/2, g.height() - 50};
    GameObject obj(location, g.width(), 50, ShapeType::rectangle, onCollision);
    obj.velocity = {0,0};

    world.objects.push_back(obj);
    while (g.draw()) {
        world.draw(g);
        world.update(g);
        world.objects[0].location = g.mousePos();

    }

    return 0;
}


