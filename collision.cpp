#include "collision.h"
#include "clipper.h"

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

using namespace ayin;
using namespace ClipperLib;

//random functions -------------------------------------------------------------------------------------------

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

double cross(Vec2d v1, Vec2d v2){
    return v1.x*v2.y - v1.y*v2.x;
}

bool toRight(Vec2d p1, Vec2d p2, Vec2d a){
    Vec2d v1 = p2-p1;
    Vec2d v2 = a-p1;
    return cross(v1, v2) > 0;
}

vector<Vec2d> expand(vector<Vec2d>points, double val){
    vector<Vec2d> returnList;
    for(int i = 0; i < points.size(); i++){
        Vec2d line = (points[i] - points[(i+1)%points.size()]);
        returnList.push_back(perp1(line).unit()*val+points[i]);
        returnList.push_back(perp1(line).unit()*val+points[(i+1)%points.size()]);
    }
    return returnList;
}

//collision functions ----------------------------------------------------------------------------------------

//Circle Circle
bool collides(Circle *c1, Circle *c2, CollisionInfo& info, double minDistance)
{
    Vec2d v1 = c1->location() - c2->location();
    if(v1.magnitude() == 0){
        return true;
    }
    Vec2d v2 = v1/v1.magnitude();
    Vec2d v3 = v2*c1->rad;
    info.collisionPoint = c1->location() - v3;
    //gives a vector where if you add to c2 you will get to c1
    info.normal = c1->location()-c2->location();
    return (c1->location() - c2->location()).magnitude() < c1->rad + c2->rad + minDistance;
}

// Circle Rectangle
bool collides(Circle *c, Rectangle *r, CollisionInfo& info, double minDistance)
{
    bool isAbove = c->location().y < r->topLeft().y;
    bool isLeft = c->location().x < r->topLeft().x;
    bool isBelow = c->location().y > r->bottomLeft().y;
    bool isRight = c->location().x > r->bottomRight().x;

    if(isAbove){
        //top left corner
        if(isLeft){
            if((c->location() - r->topLeft()).magnitude() < c->rad + minDistance){
                info.collisionPoint = r->topLeft();
                info.normal = c->location()-r->topLeft();
                return true;
            }
            return false;
        }
        //top right corner
        else if(isRight){
            if((c->location() - r->topRight()).magnitude() < c->rad + minDistance){
                info.collisionPoint = r->topRight();
                info.normal = c->location()-r->topRight();
                return true;
            }
            return false;
        }
        //top side
        else{
            if(abs(r->location().y - c->location().y) - (c->rad + r->height/2) < minDistance){
                info.collisionPoint = {c->location().x, r->topLeft().y};
                info.normal = c->location()-info.collisionPoint;
                return true;
            }
            return false;
        }
    }
    else if(isBelow){
        //bottom left corner
        if(isLeft){
            if((c->location() - r->bottomLeft()).magnitude() < c->rad + minDistance){
                info.collisionPoint = r->bottomLeft();
                info.normal = c->location()-r->bottomLeft();
                return true;
            }
            return false;
        }
        //bottom right corner
        else if(isRight){
            if((c->location() - r->bottomRight()).magnitude() < c->rad + minDistance){
                info.collisionPoint = r->bottomRight();
                info.normal = c->location()-r->bottomRight();
                return true;
            }
            return false;
        }
        //bottom side
        else{
            if(abs(c->location().y - r->location().y) - (c->rad + r->height/2) < minDistance){
                info.collisionPoint = {c->location().x, r->bottomLeft().y};
                info.normal = c->location()-info.collisionPoint;
                return true;
            }
            return false;
        }
    }
    else{
        //left side
        if(isLeft){
            if(abs(c->location().x - r->location().x) - (c->rad + r->width/2) < minDistance){
                info.collisionPoint = {r->topLeft().x, c->location().y};
                info.normal = c->location()-info.collisionPoint;
                return true;
            }
            return false;
        }
        //right side
        else if(isRight){
            if(abs(r->location().x - c->location().x) - (c->rad + r->width/2) < minDistance){
                info.collisionPoint = {r->topRight().x, c->location().y};
                info.normal = c->location()-info.collisionPoint;
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

// Circle Triangle
bool collides(Circle *c, Triangle *t, CollisionInfo& info, double minDistance)
{
    Vec2d p1 = t->corners()[0];
    Vec2d p2 = t->corners()[1];
    Vec2d p3 = t->corners()[2];
    Vec2d a = c->location();

    //
    if((p2-p1).x * (a-p1).y - (p2-p1).y * (a-p1).x > 0){
        if(distanceToSegment(p1, p2, a) < c->rad + minDistance){
            info.collisionPoint = closestPoint(p2, p1, a);
            info.normal = c->location()-info.collisionPoint;
            return true;
        }
    }
    else if((p3-p2).x * (a-p2).y - (p3-p2).y * (a-p2).x > 0){
        if(distanceToSegment(p2, p3, a) < c->rad + minDistance){
            info.collisionPoint = closestPoint(p3, p2, a);
            info.normal = c->location()-info.collisionPoint;
            return true;
        }
    }
    else if((p1-p3).x * (a-p3).y - (p1-p3).y * (a-p3).x > 0){
        if(distanceToSegment(p3, p1, a) < c->rad + minDistance){
            info.collisionPoint = closestPoint(p1, p3, a);
            info.normal = c->location()-info.collisionPoint;
            return true;
        }
    }
    else{
        // COME BACK TO THIS
        info.collisionPoint = closestPoint(p1, p2, a);
        info.normal = c->location()-info.collisionPoint;
        return true;
    }
    return false;



}

// Polygon Polygon
bool collides(PolygonShape *s1, PolygonShape *s2, CollisionInfo& info, double minDistance)
{
    vector<Vec2d> s1Corners = minDistance != 0 ? expand(s1->corners(), minDistance/2): s1->corners();
    vector<Vec2d> s2Corners = minDistance != 0 ? expand(s2->corners(), minDistance/2): s2->corners();
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

    double closest = numeric_limits<double>::max();
    for(int i = 0; i <= s2Corners.size(); i++){
        for(int j = 0; j < s1Corners.size(); j++){
            double distance = distanceToSegment(s2Corners[(i+1)%s1Corners.size()], s2Corners[i], s1Corners[i]);
            if(distance < closest){
                closest = distance;
                //need to store which guys gave me the smallest
            }
        }
    }
    for(int i = 0; i <= s1Corners.size(); i++){
        for(int j = 0; j < s2Corners.size(); j++){

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

    for(Path& p : result){
        for(IntPoint i : p){
            sum = sum + Vec2d{i.X, i.Y};
            counter++;
        }
    }
    if(counter == 0){
        return false;
    }
    info.collisionPoint = sum/counter; // center of polygon made by collision
    info.normal = (s1->location()-info.collisionPoint).unit();
    return true;
}


// double dispatching :) ---------------------------------------------------------------------------------

bool collides(ayin::CollisionShape *s, ayin::Circle *c, CollisionInfo& info, double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(c, static_cast<Circle*>(s), info, minDistance);
    case ShapeType::rectangle:
        return collides(c, static_cast<Rectangle*>(s), info, minDistance);
    case ShapeType::triangle:
        return collides(c, static_cast<Triangle*>(s), info, minDistance);
    }
}

bool collides(ayin::CollisionShape *s, ayin::Rectangle *r, CollisionInfo& info, double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), r, info, minDistance);
    case ShapeType::rectangle:
    case ShapeType::triangle:
        return collides(static_cast<PolygonShape*>(r), static_cast<PolygonShape*>(s), info, minDistance);
    }
}

bool collides(ayin::CollisionShape *s, ayin::Triangle *t, CollisionInfo& info, double , double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), t, info, minDistance);
    case ShapeType::rectangle:
    case ShapeType::triangle:
        return collides(static_cast<PolygonShape*>(s), static_cast<PolygonShape*>(t), info, minDistance);
    }
}

bool collides(ayin::CollisionShape *s1, ayin::CollisionShape *s2, CollisionInfo& info, double minDistance)
{
    ShapeType x = s1->type();
    switch(x){
    case ShapeType::circle:
        return collides(s2, static_cast<Circle*>(s1), info, minDistance);
    case ShapeType::rectangle:
        return collides(s2, static_cast<Rectangle*>(s1), info, minDistance);
    case ShapeType::triangle:
        return collides(s2, static_cast<Triangle*>(s1), info, minDistance);
    }
}
