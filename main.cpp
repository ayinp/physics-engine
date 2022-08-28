#include <iostream>
#include "graphics.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "vec2d.h"
#include "collision.h"
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

    Rectangle shape1(Vec2d{g.randomInt(0, g.width()), g.randomInt(0, g.height())}, 300, 200);


    while (g.draw()) {
        Rectangle shape2(g.mousePos(), 300, 300);
        shape1.draw(g);
        shape2.draw(g);

        if(collides(&shape1, &shape2)){
            g.cout << "AHHHHHHHHHH" << endl;
        }

        if(g.onKeyPress('R')){
            shape1.location = {g.randomInt(0, g.width()), g.randomInt(0, g.height())};
        }
    }

    return 0;
}


