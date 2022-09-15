#include "collision.h"
#include "graphics.h"

using namespace ayin;

//random functions
double dot(Vec2d v1, Vec2d v2){
    return v1.x * v2.x + v1.y * v2.y;
}

double distanceToSegment(Vec2d s1, Vec2d s2, Vec2d p){
    Vec2d v1 = s2-s1;
    Vec2d v2 = p-s1;
    double v1Mag = v1.magnitude();
    double l = dot(v1, v2)/v1Mag;
    double t = l/v1Mag; // if <0 or > 1 then corner, else in line!!!
    if(t <= 0){
        return (s1-p).magnitude();
    }
    if(t >= 1){
        return (s2-p).magnitude();
    }
    return sqrt(v2.magSquared() - l*l);
}


//collision functions
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
    bool isAbove = c->location.y < r->topLeft().y;
    bool isLeft = c->location.x < r->topLeft().x;
    bool isBelow = c->location.y > r->bottomLeft().y;
    bool isRight = c->location.x > r->bottomRight().x;

    if(isAbove){
        if(isLeft){
            if((c->location - r->topLeft()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else if(isRight){
            if((c->location - r->topRight()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else{
            if(abs(r->location.y - c->location.y) - (c->rad + r->height/2) < 0){
                return true;
            }
            return false;
        }
    }
    else if(isBelow){
        if(isLeft){
            if((c->location - r->bottomLeft()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else if(isRight){
            if((c->location - r->bottomRight()).magnitude() < c->rad){
                return true;
            }
            return false;
        }
        else{
            if(abs(c->location.y - r->location.y) - (c->rad + r->height/2) < 0){
                return true;
            }
            return false;
        }
    }
    else{
        if(isLeft){
            if(abs(c->location.x - r->location.x) - (c->rad + r->width/2) < 0){
                return true;
            }
            return false;
        }
        else if(isRight){
            if(abs(r->location.x - c->location.x) - (c->rad + r->width/2) < 0){
                return true;
            }
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}

bool collides(Circle *c, Triangle *t)
{
    Vec2d p1 = t->corners()[0];
    Vec2d p2 = t->corners()[1];
    Vec2d p3 = t->corners()[2];
    Vec2d a = c->location;

    if((p2-p1).x * (a-p1).y - (p2-p1).y * (a-p1).x > 0){
        if(distanceToSegment(p1, p2, a) < c->rad){
            return true;
        }
    }
    else if((p3-p2).x * (a-p2).y - (p3-p2).y * (a-p2).x > 0){
        if(distanceToSegment(p2, p3, a) < c->rad){
            return true;
        }
    }
    else if((p1-p3).x * (a-p3).y - (p1-p3).y * (a-p3).x > 0){
        if(distanceToSegment(p3, p1, a) < c->rad){
            return true;
        }
    }
    else{
        return true;
    }
    return false;



}

double cross(Vec2d v1, Vec2d v2){
    return v1.x*v2.y - v1.y*v2.x;
}

bool toRight(Vec2d p1, Vec2d p2, Vec2d a){
    Vec2d v1 = p2-p1;
    Vec2d v2 = a-p1;
    return cross(v1, v2) > 0; // might have to be flipped if everything is backwar
}

bool collides(Rectangle *r, Triangle *t, mssm::Graphics &g)
{
    bool pToR = true;
    for(int i = 1; i <= t->corners().size(); i++){
        pToR = true;
        for(int j = 0; j < r->corners().size(); j++){
            if(toRight(t->corners()[i%3], t->corners()[(i+1)%3], r->corners()[j])){
              //  g.line((t->corners()[i%3] + t->corners()[(i+1)%3])*.5, r->corners()[j], mssm::ORANGE);
//                pToR = true;
            }
            else{
                pToR = false;
             //   g.line((t->corners()[i%3] + t->corners()[(i+1)%3])*.5, r->corners()[j], mssm::BLUE);
            }
        }
        if(pToR){  // it was always to right, so doesn't collide
           return false;
        }
    }

    for(int i = 1; i <= r->corners().size(); i++){
        pToR = true;
        for(int j = 0; j < t->corners().size(); j++){
            if(toRight(r->corners()[i%4], r->corners()[(i+1)%4], t->corners()[j])){
                g.line((r->corners()[i%4] + r->corners()[(i+1)%4])*.5, t->corners()[j], mssm::YELLOW);
//                pToR = true;
            }
            else{
                g.line((r->corners()[i%4] + r->corners()[(i+1)%4])*.5, t->corners()[j], mssm::GREEN);
                pToR = false;
                break;
            }
        }
        if(pToR){
           return false;
        }
    }

    return true;
}
