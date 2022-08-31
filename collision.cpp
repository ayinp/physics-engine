#include "collision.h"
#include "graphics.h"

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

bool collides(Circle *c, Rectangle *r, mssm::Graphics& g)
{
    bool isAbove = c->location.y < r->topLeft().y;
    bool isLeft = c->location.x < r->topLeft().x;
    bool isBelow = c->location.y > r->bottomLeft().y;
    bool isRight = c->location.x > r->bottomRight().x;

    g.cout << (isAbove ? "above" : "not above") << endl;
    g.cout << (isBelow ? "below" : "not below") << endl;
    g.cout << (isLeft ? "left" : "not left") << endl;
    g.cout << (isRight ? "right" : "not right") << endl;

    if(isAbove){
        if(isLeft){
            g.cout << "TL" << endl;
            if((c->location - r->topLeft()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else if(isRight){
            g.cout << "TR" << endl;
            if((c->location - r->topRight()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else{
            g.cout << "T" << endl;
            if(abs(r->location.y - c->location.y) - (c->rad + r->height/2) < 0){
                return true;
            }
            return false;
        }
    }
    else if(isBelow){
        if(isLeft){
            g.cout << "BL" << endl;
            if((c->location - r->bottomLeft()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else if(isRight){
            g.cout << "BR" << endl;
            if((c->location - r->bottomRight()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else{
            g.cout << "B" << endl;
            if(abs(c->location.y - r->location.y) - (c->rad + r->height/2) < 0){
                return true;
            }
            return false;
        }
    }
    else{
        if(isLeft){
            g.cout << "L" << endl;
            if(abs(c->location.x - r->location.x) - (c->rad + r->width/2) < 0){
                return true;
            }
            return false;
        }
        else if(isRight){
            g.cout << "R" << endl;
            if(abs(r->location.x - c->location.x) - (c->rad + r->width/2) < 0){
                return true;
            }
            return false;
        }
        else{
            g.cout << "M" << endl;
            return true;
        }
    }
    return false;
}

bool collides(Circle *c, Triangle *t)
{

}

bool collides(Rectangle *r, Triangle *t)
{

}
