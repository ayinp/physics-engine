//#include <iostream>
//#include "graphics.h"
//#include "rectangle.h"
//#include "circle.h"
//#include "triangle.h"
//#include "vec2d.h"
//#include "collision.h"
//#include "world.h"
////#include "paths.h"

//using namespace std;
//using namespace mssm;
//using namespace ayin;

//#ifndef _MSC_VER
//#pragma GCC diagnostic ignored "-Wsign-compare"
//#endif

//Vec2d perp(Vec2d v){
//    return {v.y, -v.x};
//}

//void onCollision(GameObject* me, GameObject* heHitMe, CollisionInfo info){

//    //        me->velocity= -0.85 * me->velocity;

//    //        if(abs(me->velocity.y) < 0.1){
//    //            me->velocity.y = 0;
//    //        }
//    //        if(abs(me->velocity.x) < 0.1){
//    //            me->velocity.x = 0;
//    //        }

//    me->location = me->lastLoc;
//    Vec2d normal = perp(me->location - info.collisionPoint);

//    Vec2d newX = normal * (dotProduct(normal, me->velocity)/dotProduct(normal, normal));
//    Vec2d newY = me->velocity - newX;

//    me->velocity = me->elasticity*(newX - newY);

//    if(abs(me->velocity.x) < 0.1){
//        me->velocity.x = 0;

//    }
//    if(abs(me->velocity.y) < 0.1){
//        me->velocity.y = 0;
//        me->affectedByGravity = false;
//    }


//    if(isnan(me->velocity.x)){
//        cout << "NOOOOOOOOOOOx" << endl;
//    }
//    if(isnan(me->velocity.y)){
//        cout << "NOOOOOOOOOOOy" << endl;
//    }

//}



//int main()
//{
//    //   Paths::findAsset("skull.png");
//    Graphics g("Test", 1024, 768);

//    World world({0, 0.5});



////    Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
////    GameObject myBall(g.mousePos(), 50, 50 , ShapeType::triangle, onCollision);
////    myBall.affectedByGravity = false;
////    myBall.velocity = {0,0};


//    Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
//    GameObject triangle(location, 50, 50 , ShapeType::triangle, onCollision);
//    triangle.affectedByGravity = true;
//    triangle.velocity = {g.randomDouble(-3,3),g.randomDouble(-3,3)};
//    triangle.wrapInX = true;
//    triangle.wrapInY = true;


////    GameObject grnd({g.width()/2, g.height()-25}, g.width(), 50, ShapeType::rectangle, onCollision);
////    grnd.affectedByGravity = false;
////    grnd.velocity = {0,0};


////    world.objects.push_back(grnd);
//world.objects.push_back(triangle);
//    for(int i = 0; i< 10; i++){
//        Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
//        GameObject ball(location, g.randomInt(10,100), g.randomInt(10,100) , ShapeType::circle, onCollision);
//        ball.affectedByGravity = false;
//        ball.velocity = {0,0};
//        world.objects.push_back(ball);
//    }



//    while (g.draw()) {

//        for (auto& ob :  world.objects) {
//            g.cout << ob.velocity.x << " " << ob.velocity.y << endl;
//        }

////        myBall.location = g.mousePos();
//        world.draw(g);
//        world.update(g);

////         myBall.draw(g);
//        if(g.onMousePress(MouseButton::Left)){
////            GameObject newBall(myBall);
////            newBall.affectedByGravity = true;
////            newBall.wrapInX = true;
////            newBall.wrapInY = true;
////            newBall.elasticity = g.randomDouble(0.5, 0.99);
////            myBall.width = g.randomInt(10, 100);
////            myBall.height = g.randomInt(10,100);

////            world.objects.push_back(newBall);
//        }

//    }

//    return 0;
//}


#include "graphics.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

bool lessThanThree(int v)
{
    return v < 3;
}

Vec2d perp(Vec2d v)
{
    return {v.y, -v.x};
}

Vec2d calcIntersection(Vec2d p, Vec2d w, Vec2d a, Vec2d b)
{
    double xp = -crossProduct(w, b);

    if (abs(xp) < 0.00001) {
        return { 10, 10 };
    }

    double l = dotProduct((p-a), perp(b)) / xp;

    return p + l * w;
}


int main(int argc, char* argv[])
{
    Vec2d p;
    Vec2d w;

    Vec2d a;
    Vec2d b;


    Graphics g("Test", 1024, 768);

    while (g.draw()) {

        if (g.onMousePress(MouseButton::Left)) {
            p = g.mousePos();
        }

        if (g.isMousePressed(MouseButton::Left)) {
            g.line(p, g.mousePos(), PURPLE);
        }

        if (g.onMouseRelease(MouseButton::Left)) {
            if (!g.mousePos().exactlyEquals(p)) {
                w = (g.mousePos() - p).unit();
            }
        }

        if (g.onMousePress(MouseButton::Right)) {
            a = g.mousePos();
        }

        if (g.isMousePressed(MouseButton::Right)) {
            g.line(a, g.mousePos(), PURPLE);
        }

        if (g.onMouseRelease(MouseButton::Right)) {
            if (!g.mousePos().exactlyEquals(a)) {
                b = (g.mousePos() - a).unit();
            }
        }

        int dotSize = 6;
        double unitLength = 100;

        Color lineColor{192, 234, 250, 128};
        g.line(a, a+g.width()*b, lineColor);
        g.line(a, a-g.width()*b, lineColor);


        g.ellipse(p, dotSize, dotSize, GREEN, GREEN);
        g.line(p, p+w*unitLength, GREEN);
        g.ellipse(a, dotSize, dotSize, YELLOW, YELLOW);
        g.line(a, a+b*unitLength, YELLOW);

        Vec2d xp = calcIntersection(p, w, a, b);
        g.line(p, xp, lineColor);

        g.ellipse(xp, dotSize, dotSize, ORANGE, ORANGE);
    }

    return 0;
}
