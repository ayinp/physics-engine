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

    me->velocity = me->elasticity*(newX - newY);

    if(abs(me->velocity.x) < 0.1){
        me->velocity.x = 0;

    }
    if(abs(me->velocity.y) < 0.1){
        me->velocity.y = 0;
        me->affectedByGravity = false;
    }


    if(isnan(me->velocity.x)){
        cout << "NOOOOOOOOOOOx" << endl;
    }
    if(isnan(me->velocity.y)){
        cout << "NOOOOOOOOOOOy" << endl;
    }

}



int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);

    World world({0, 0.5});



//    Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
//    GameObject myBall(g.mousePos(), 50, 50 , ShapeType::triangle, onCollision);
//    myBall.affectedByGravity = false;
//    myBall.velocity = {0,0};


    Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
    GameObject triangle(location, 50, 50 , ShapeType::triangle, onCollision);
    triangle.affectedByGravity = true;
    triangle.velocity = {g.randomDouble(-3,3),g.randomDouble(-3,3)};
    triangle.wrapInX = true;
    triangle.wrapInY = true;


//    GameObject grnd({g.width()/2, g.height()-25}, g.width(), 50, ShapeType::rectangle, onCollision);
//    grnd.affectedByGravity = false;
//    grnd.velocity = {0,0};


//    world.objects.push_back(grnd);
world.objects.push_back(triangle);
    for(int i = 0; i< 10; i++){
        Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
        GameObject ball(location, g.randomInt(10,100), g.randomInt(10,100) , ShapeType::circle, onCollision);
        ball.affectedByGravity = false;
        ball.velocity = {0,0};
        world.objects.push_back(ball);
    }



    while (g.draw()) {

        for (auto& ob :  world.objects) {
            g.cout << ob.velocity.x << " " << ob.velocity.y << endl;
        }

//        myBall.location = g.mousePos();
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


