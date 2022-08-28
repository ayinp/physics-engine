#include "collision.h"

using namespace ayin;


bool collides(Circle *c1, Circle *c2)
{
    return (c1->location - c2->location).magnitude() < c1->rad + c2->rad;
}

bool collides(Rectangle *r1, Rectangle *r2)
{
    if(r1->location.x + r1->width/2 > r2->location.x - r2->width/2 &&
       r1->location.x - r1->width/2 < r2->location.x + r2->width/2 &&
       r1->location.y + r1->height/2 > r2->location.y - r2->height/2 &&
       r1->location.y - r1->height/2 < r2->location.y + r2->height/2) {
        return true;
    }
    return false;
}

bool collides(Triangle *t1, Triangle *t2)
{

}

bool collides(Circle *c, Rectangle *r)
{

}

bool collides(Circle *c, Triangle *t)
{

}

bool collides(Rectangle *r, Triangle *t)
{

}
