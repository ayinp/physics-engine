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

bool collides(PolygonShape *s1, PolygonShape *s2)
{
    vector<Vec2d> s1Corners = s1->corners();
    vector<Vec2d> s2Corners = s2->corners();
    bool pToR = true;
    for(int i = 1; i <= s2Corners.size(); i++){
        pToR = true;
        for(int j = 0; j < s1Corners.size(); j++){
            if(toRight(s2Corners[i%s2Corners.size()], s2Corners[(i+1)%s2Corners.size()], s1Corners[j])){
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

    for(int i = 1; i <= s1Corners.size(); i++){
        pToR = true;
        for(int j = 0; j < s2Corners.size(); j++){
            if(toRight(s1Corners[i%s1Corners.size()], s1Corners[(i+1)%s1Corners.size()], s2Corners[j])){
//                g.line((s1Corners[i%s1Corners.size()] + s1Corners[(i+1)%s1Corners.size()])*.5, s2Corners[j], mssm::YELLOW);
//                pToR = true;
            }
            else{
//                g.line((s1Corners[i%s1Corners.size()] +s1Corners[(i+1)%s1Corners.size()])*.5, s2Corners[j], mssm::GREEN);
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

bool collides(ayin::CollisionShape *s, ayin::Circle *c){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(c, static_cast<Circle*>(s));
    case ShapeType::rectangle:
         return collides(c, static_cast<Rectangle*>(s));
    case ShapeType::triangle:
         return collides(c, static_cast<Triangle*>(s));
    }
}

bool collides(ayin::CollisionShape *s, ayin::Rectangle *r){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), r);
    case ShapeType::rectangle:
         return collides(static_cast<Rectangle*>(s), r);
    case ShapeType::triangle:
         return collides(static_cast<PolygonShape*>(r), static_cast<PolygonShape*>(s));
    }
}

bool collides(ayin::CollisionShape *s, ayin::Triangle *t){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), t);
    case ShapeType::rectangle:
    case ShapeType::triangle:
         return collides(static_cast<PolygonShape*>(s), static_cast<PolygonShape*>(t));
    }
}



bool collides(ayin::CollisionShape *s1, ayin::CollisionShape *s2)
{
    ShapeType x = s1->type();
    switch(x){
    case ShapeType::circle:
        return collides(s2, static_cast<Circle*>(s1));
    case ShapeType::rectangle:
        return collides(s2, static_cast<Rectangle*>(s1));
    case ShapeType::triangle:
        return collides(s2, static_cast<Triangle*>(s1));
    }
}
