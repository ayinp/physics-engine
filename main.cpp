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

int main()
{
    //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);



    World world;


    for(int i = 0; i < 6; i++){
        if(i%3 == 0){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
            Triangle* t = new Triangle(location, 0, 0, g.randomInt(10, 100), g.randomInt(10, 100));
            GameObject obj(location, t);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            world.objects.push_back(obj);
        }
        else if(i%3 == 1){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
            Rectangle* r = new Rectangle(location, g.randomInt(10, 100), g.randomInt(10, 100));
            GameObject obj(location, r);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            world.objects.push_back(obj);
        }
        else if(i%3 == 2){
            Vec2d location = {g.randomDouble(0, g.width()), g.randomDouble(0, g.height())};
            Circle* c = new Circle(location, g.randomInt(10, 100));
            GameObject obj(location, c);
            obj.velocity = {g.randomDouble(-5, 5), g.randomDouble(-5, 5)};
            world.objects.push_back(obj);
        }

    }


    while (g.draw()) {
        world.draw(g);
        world.update(g);
    }

    return 0;
}


