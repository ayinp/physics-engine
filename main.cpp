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

void onCollision(GameObject* me, GameObject* heHitMe, CollisionInfo info, Graphics& g){


    g.ellipse(info.collisionPoint, 15,15, RED, RED);
    me->location = me->lastLoc;
    Vec2d normal = perp(me->location - info.collisionPoint).unit();

    Vec2d newX = normal * (dotProduct(normal, me->velocity)/dotProduct(normal, normal));
    Vec2d newY = me->velocity - newX;

    me->velocity = me->elasticity*(newX - newY);

    if(isnan(me->velocity.x)){
        cout << "NOOOOOOOOOOOx" << endl;
    }
    if(isnan(me->velocity.y)){
        cout << "NOOOOOOOOOOOy" << endl;
    }

    if(abs(me->velocity.x) < 0.1){
        me->velocity.x = 0;

    }
    if(abs(me->velocity.y) < 0.1){
        me->velocity.y = 0;
    }

}



int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);

    World world({0, 0.5});






    GameObject grnd({g.width()/2, g.height()-25}, g.width(), 50, ShapeType::rectangle, [&g](GameObject *a, GameObject *b, CollisionInfo c){onCollision(a,b,c, g);});
    grnd.affectedByGravity = false;
    grnd.velocity = {0,0};

        world.objects.push_back(grnd);


        for(int i = 0; i< 9; i++){

             if(i%3 == 0){
                Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height()-100)};
                GameObject ball(location, g.randomInt(10,100), g.randomInt(10,100) , ShapeType::rectangle, [&g](GameObject *a, GameObject *b, CollisionInfo c){onCollision(a,b,c, g);});
                ball.affectedByGravity = true;
                ball.wrapInX = true;
                ball.wrapInY = true;
                ball.velocity = {g.randomDouble(-3, 3), g.randomDouble(-3, 3)};
                ball.elasticity = g.randomDouble(0.7, 0.95);
                world.objects.push_back(ball);

            }
            else if(i%3 == 1){
                Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height()-100)};
                GameObject ball(location, g.randomInt(10,100), g.randomInt(10,100) , ShapeType::triangle, [&g](GameObject *a, GameObject *b, CollisionInfo c){onCollision(a,b,c, g);});
                ball.affectedByGravity = true;
                ball.wrapInX = true;
                ball.wrapInY = true;
                ball.velocity = {g.randomDouble(-3, 3), g.randomDouble(-3, 3)};
                ball.elasticity = g.randomDouble(0.7, 0.95);
                world.objects.push_back(ball);
            }
             else if(i%3 == 2){
                 Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height()-100)};
                 GameObject ball(location, g.randomInt(10,100), g.randomInt(10,100) , ShapeType::circle, [&g](GameObject *a, GameObject *b, CollisionInfo c){onCollision(a,b,c, g);});
                 ball.affectedByGravity = true;
                 ball.wrapInX = true;
                 ball.wrapInY = true;
                 ball.velocity = {g.randomDouble(-3, 3), g.randomDouble(-3, 3)};
                 ball.elasticity = g.randomDouble(0.7, 0.95);
                 world.objects.push_back(ball);
             }

        }



    while (g.draw()) {


        world.draw(g);
        world.update(g);

        //         myBall.draw(g);
        if(g.onMousePress(MouseButton::Left)){
            //            GameObject newBall(myBall);
            //            newBall.affectedByGravity = true;
            //            newBall.wrapInX = true;
            //            newBall.wrapInY = true;
            //            newBall.elasticity = g.randomDouble(0.5, 0.99);
            //            myBall.width = g.randomInt(10, 100);
            //            myBall.height = g.randomInt(10,100);

            //            world.objects.push_back(newBall);
        }

    }

    return 0;
}


