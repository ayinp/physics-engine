#include <iostream>
#include "graphics.h"
#include "collisionshape.h"
#include "rectangle.h"
#include "vec2d.h"
//#include "paths.h"

using namespace std;
using namespace mssm;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

int main()
{
 //   Paths::findAsset("skull.png");
    Graphics g("Test", 1024, 768);

    MyRectangle rect({100,100}, 100, 100);

    while (g.draw()) {
        rect.draw(g);
    }

    return 0;
}


