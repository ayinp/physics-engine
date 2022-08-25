#include <iostream>
#include "graphics.h"
#include "rectangle.h"
#include "oval.h"
#include "triangle.h"
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

    MyRectangle rect({100,100}, 100, 150);
    Oval oval({300, 100}, 100, 150);
    MyTriangle triangle({500, 100}, true, true, 100, 150);
    MyTriangle triangle2({700, 100}, true, false, 100, 150);
    MyTriangle triangle3({900, 100}, false, false, 100, 150);

    while (g.draw()) {
        rect.draw(g);
        oval.draw(g);
        triangle.draw(g);
        triangle2.draw(g);
        triangle3.draw(g);
    }

    return 0;
}


