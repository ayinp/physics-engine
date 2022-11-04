#include "collision.h"
#include "graphics.h"
#include "clipper.h"

using namespace ayin;
using namespace ClipperLib;

//random functions
double dot(Vec2d v1, Vec2d v2){
    return v1.x * v2.x + v1.y * v2.y;
}

Vec2d perp1(Vec2d v)
{
    return {v.y, -v.x};
}

Vec2d collisionPoint(Vec2d p, Vec2d w, Vec2d a, Vec2d b)
{
    double xp = -crossProduct(w, b);

    if (abs(xp) < 0.0001) {

        return {10,10}; // CHANGE THIS
    }

    double l = dotProduct((p-a), perp1(b)) / xp;

    return p + l * w;
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

Vec2d closestPoint(Vec2d s1, Vec2d s2, Vec2d p){
    Vec2d v1 = s2-s1;
    Vec2d v2 = p-s1;
    double v1Mag = v1.magnitude();
    double l = dot(v1, v2)/v1Mag;
    double t = l/v1Mag; // if <0 or > 1 then corner, else in line!!!
    if(t <= 0){
        return s1;
    }
    if(t >= 1){
        return s2;
    }
    return s1 + t*(s2-s1);
}


//collision functions
bool collides(Circle *c1, Circle *c2, CollisionInfo& info)
{
    Vec2d v1 = c1->location() - c2->location();
    if(v1.magnitude() == 0){
        return true;
    }
    Vec2d v2 = v1/v1.magnitude();
    Vec2d v3 = v2*c1->rad;
    info.collisionPoint = c1->location() - v3;
    return (c1->location() - c2->location()).magnitude() < c1->rad + c2->rad;
}

//bool collides(Rectangle *r1, Rectangle *r2, CollisionInfo& info)
//{

//    if(r1->location().x + r1->width/2 > r2->location().x - r2->width/2 &&
//            r1->location().x - r1->width/2 < r2->location().x + r2->width/2 &&
//            r1->location().y + r1->height/2 > r2->location().y - r2->height/2 &&
//            r1->location().y - r1->height/2 < r2->location().y + r2->height/2) {
//        return true;
//    }
//    return false;
//}

bool collides(Circle *c, Rectangle *r, CollisionInfo& info)
{
    bool isAbove = c->location().y < r->topLeft().y;
    bool isLeft = c->location().x < r->topLeft().x;
    bool isBelow = c->location().y > r->bottomLeft().y;
    bool isRight = c->location().x > r->bottomRight().x;

    if(isAbove){
        if(isLeft){
            if((c->location() - r->topLeft()).magnitude() < c->rad){
                info.collisionPoint = r->topLeft();
                return true;
            }
            return false;
        }
        else if(isRight){
            if((c->location() - r->topRight()).magnitude() < c->rad){
                info.collisionPoint = r->topRight();
                return true;
            }
            return false;
        }
        else{
            if(abs(r->location().y - c->location().y) - (c->rad + r->height/2) < 0){
                info.collisionPoint = {c->location().x, r->topLeft().y};
                return true;
            }
            return false;
        }
    }
    else if(isBelow){
        if(isLeft){
            if((c->location() - r->bottomLeft()).magnitude() < c->rad){
                info.collisionPoint = r->bottomLeft();
                return true;
            }
            return false;
        }
        else if(isRight){
            if((c->location() - r->bottomRight()).magnitude() < c->rad){
                info.collisionPoint = r->bottomRight();
                return true;
            }
            return false;
        }
        else{
            if(abs(c->location().y - r->location().y) - (c->rad + r->height/2) < 0){
                info.collisionPoint = {c->location().x, r->bottomLeft().y};
                return true;
            }
            return false;
        }
    }
    else{
        if(isLeft){
            if(abs(c->location().x - r->location().x) - (c->rad + r->width/2) < 0){
                info.collisionPoint = {r->topLeft().x, c->location().y};
                return true;
            }
            return false;
        }
        else if(isRight){
            if(abs(r->location().x - c->location().x) - (c->rad + r->width/2) < 0){
                info.collisionPoint = {r->topRight().x, c->location().y};
                return true;
            }
            return false;
        }
        else{
            //COME BACK TO THIS
            return true;
        }
    }
    return false;
}

bool collides(Circle *c, Triangle *t, CollisionInfo& info)
{
    Vec2d p1 = t->corners()[0];
    Vec2d p2 = t->corners()[1];
    Vec2d p3 = t->corners()[2];
    Vec2d a = c->location();


    if((p2-p1).x * (a-p1).y - (p2-p1).y * (a-p1).x > 0){
        if(distanceToSegment(p1, p2, a) < c->rad){
            info.collisionPoint = closestPoint(p2, p1, a);
            return true;
        }
    }
    else if((p3-p2).x * (a-p2).y - (p3-p2).y * (a-p2).x > 0){
        if(distanceToSegment(p2, p3, a) < c->rad){
            info.collisionPoint = closestPoint(p3, p2, a);
            return true;
        }
    }
    else if((p1-p3).x * (a-p3).y - (p1-p3).y * (a-p3).x > 0){
        if(distanceToSegment(p3, p1, a) < c->rad){
            info.collisionPoint = closestPoint(p1, p3, a);
            return true;
        }
    }
    else{
        // COME BACK TO THIS
        info.collisionPoint = closestPoint(p1, p2, a);
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

bool collides(PolygonShape *s1, PolygonShape *s2, CollisionInfo& info)
{
    vector<Vec2d> s1Corners = s1->corners();
    vector<Vec2d> s2Corners = s2->corners();
    bool pToR = true;
    for(int i = 1; i <= s2Corners.size(); i++){
        pToR = true;
        for(int j = 0; j < s1Corners.size(); j++){
            if(toRight(s2Corners[i%s2Corners.size()], s2Corners[(i+1)%s2Corners.size()], s1Corners[j])){

            }
            else{
                pToR = false;
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
            }
            else{
                pToR = false;
                break;
            }
        }
        if(pToR){
            return false;
        }
    }

    Path p1;
    Path p2;
    Paths result;
    for(Vec2d v : s1Corners){
        p1.push_back({static_cast<cInt>(v.x), static_cast<cInt>(v.y)});
    }
    for(Vec2d v : s2Corners){
        p2.push_back({static_cast<cInt>(v.x), static_cast<cInt>(v.y)});
    }

    Clipper clip;
    clip.AddPath(p1, PolyType::ptClip, true);
    clip.AddPath(p2, PolyType::ptSubject, true);
    clip.Execute(ClipType::ctIntersection, result);

    Vec2d sum;
    int counter = 0;

    for(Path p : result){
        for(IntPoint i : p){
            sum = sum + Vec2d{i.X, i.Y};
            counter++;
        }
    }

    info.collisionPoint = sum/counter; // center of polygon made by collision

    return true;
}

bool collides(ayin::CollisionShape *s, ayin::Circle *c, CollisionInfo& info){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(c, static_cast<Circle*>(s), info);
    case ShapeType::rectangle:
        return collides(c, static_cast<Rectangle*>(s), info);
    case ShapeType::triangle:
        return collides(c, static_cast<Triangle*>(s), info);
    }
}

bool collides(ayin::CollisionShape *s, ayin::Rectangle *r, CollisionInfo& info){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), r, info);
    case ShapeType::rectangle:
//        return collides(static_cast<Rectangle*>(s), r, info);
    case ShapeType::triangle:
        return collides(static_cast<PolygonShape*>(r), static_cast<PolygonShape*>(s), info);
    }
}

bool collides(ayin::CollisionShape *s, ayin::Triangle *t, CollisionInfo& info){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), t, info);
    case ShapeType::rectangle:
    case ShapeType::triangle:
        return collides(static_cast<PolygonShape*>(s), static_cast<PolygonShape*>(t), info);
    }
}



bool collides(ayin::CollisionShape *s1, ayin::CollisionShape *s2, CollisionInfo& info)
{
    ShapeType x = s1->type();
    switch(x){
    case ShapeType::circle:
        return collides(s2, static_cast<Circle*>(s1), info);
    case ShapeType::rectangle:
        return collides(s2, static_cast<Rectangle*>(s1), info);
    case ShapeType::triangle:
        return collides(s2, static_cast<Triangle*>(s1), info);
    }
}
