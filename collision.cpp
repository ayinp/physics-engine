#include "collision.h"
#include "circle.h"
#include "clipper.h"
#include "polygon.h"

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



double distanceToSegment(Vec2d s1, Vec2d s2, Vec2d p, Vec2d &norm){
    Vec2d v1 = s2-s1;
    Vec2d v2 = p-s1;
    double v1Mag = v1.magnitude();
    double l = dot(v1, v2)/v1Mag;
    double t = l/v1Mag; // if <0 or > 1 then corner, else in line!!!
    if(t <= 0){
        norm = (s1-p).unit();
        return (s1-p).magnitude();
    }
    if(t >= 1){
        norm = (s2-p).unit();
        return (s2-p).magnitude();
    }
    norm = perp(s1-s2).unit();
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

// Circle Polygon
bool collides(Circle *c, Polygon *p, CollisionInfo& info, double minDistance)
{
//NEED A CIRCLE POLY COLISION
    return false;
}


//Circle Circle
bool collides(Circle *c1, Circle *c2, CollisionInfo& info, double minDistance)
{
    Vec2d v1 = c1->location() - c2->location();
    if(v1.magnitude() == 0){
        return true;
    }
    Vec2d v2 = v1/v1.magnitude();
    Vec2d v3 = v2*c1->rad;
    info.setColPoint(c1->location() - v3);
    //gives a vector where if you add to c2 you will get to c1
    info.setNormal((c1->location()-c2->location()).unit());
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
                info.setColPoint(r->topLeft());
                info.setNormal((c->location()-r->topLeft()).unit());
                return true;
            }
            return false;
        }
        //top right corner
        else if(isRight){
            if((c->location() - r->topRight()).magnitude() < c->rad + minDistance){
                info.setColPoint(r->topRight());
                info.setNormal((c->location()-r->topRight()).unit());
                return true;
            }
            return false;
        }
        //top side
        else{
            if(abs(r->location().y - c->location().y) - (c->rad + r->height/2) < minDistance){
                info.setColPoint({c->location().x, r->topLeft().y});
                info.setNormal((c->location()-info.getColPoint()).unit());
                return true;
            }
            return false;
        }
    }
    else if(isBelow){
        //bottom left corner
        if(isLeft){
            if((c->location() - r->bottomLeft()).magnitude() < c->rad + minDistance){
                info.setColPoint(r->bottomLeft());
                info.setNormal((c->location()-r->bottomLeft()).unit());
                return true;
            }
            return false;
        }
        //bottom right corner
        else if(isRight){
            if((c->location() - r->bottomRight()).magnitude() < c->rad + minDistance){
                info.setColPoint(r->bottomRight());
                info.setNormal((c->location()-r->bottomRight()).unit());
                return true;
            }
            return false;
        }
        //bottom side
        else{
            if(abs(c->location().y - r->location().y) - (c->rad + r->height/2) < minDistance){
                info.setColPoint({c->location().x, r->bottomLeft().y});
                info.setNormal((c->location()-info.getColPoint()).unit());
                return true;
            }
            return false;
        }
    }
    else{
        //left side
        if(isLeft){
            if(abs(c->location().x - r->location().x) - (c->rad + r->width/2) < minDistance){
                info.setColPoint({r->topLeft().x, c->location().y});
                info.setNormal((c->location()-info.getColPoint()).unit());
                return true;
            }
            return false;
        }
        //right side
        else if(isRight){
            if(abs(r->location().x - c->location().x) - (c->rad + r->width/2) < minDistance){
                info.setColPoint({r->topRight().x, c->location().y});
                info.setNormal((c->location()-info.getColPoint()).unit());
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
    cout<< "WE ARE COLIDING" <<endl;
    Vec2d p1 = t->corners()[0];
    Vec2d p2 = t->corners()[1];
    Vec2d p3 = t->corners()[2];
    Vec2d a = c->location();

    //
    if((p2-p1).x * (a-p1).y - (p2-p1).y * (a-p1).x > 0){
        Vec2d norm = {0,0};
        if(distanceToSegment(p1, p2, a, norm) < c->rad + minDistance){
            info.setColPoint(closestPoint(p2, p1, a));
            info.setNormal(norm);
            return true;
        }
    }
    else if((p3-p2).x * (a-p2).y - (p3-p2).y * (a-p2).x > 0){
        Vec2d norm = {0,0};
        if(distanceToSegment(p2, p3, a, norm) < c->rad + minDistance){
            info.setColPoint(closestPoint(p3, p2, a));
            info.setNormal(norm);
            return true;
        }
    }
    else if((p1-p3).x * (a-p3).y - (p1-p3).y * (a-p3).x > 0){
        Vec2d norm = {0,0};
        if(distanceToSegment(p3, p1, a, norm) < c->rad + minDistance){
            info.setColPoint(closestPoint(p1, p3, a));
            info.setNormal(norm);
            return true;
        }
    }
    else{
        // COME BACK TO THIS
        info.setColPoint(closestPoint(p1, p2, a));
        info.setNormal((c->center()-info.getColPoint()).unit());
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

    Vec2d norm = {0,0};
    double closest = numeric_limits<double>::max();
    for(int i = 0; i <= s2Corners.size(); i++){
        for(int j = 0; j < s1Corners.size(); j++){
            Vec2d norm1;
            double distance = distanceToSegment(s2Corners[(i+1)%s2Corners.size()], s2Corners[i], s1Corners[j], norm1);
            if(distance < closest){
                closest = distance;
                norm = norm1;
            }
        }
    }
    for(int i = 0; i <= s1Corners.size(); i++){
        for(int j = 0; j < s2Corners.size(); j++){
            Vec2d norm1;
            double distance = distanceToSegment(s1Corners[(i+1)%s1Corners.size()], s1Corners[i], s2Corners[j], norm1);
            if(distance < closest){
                closest = distance;
                norm = norm1;
            }
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
    info.setColPoint(sum/counter); // center of polygon made by collision
    info.setNormal(norm.unit());
    cout<<info.getNormal()<<endl;
    return true;
}


// double dispatching :) ---------------------------------------------------------------------------------

bool collides(ayin::CollisionShape *s, ayin::Circle *c, CollisionInfo& info, double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
    {
        bool returnVal = collides(c, static_cast<Circle*>(s), info, minDistance);
        if(returnVal){
            info.setNormal(-info.getNormal());
        }
        return returnVal;
    }

    case ShapeType::rectangle:
    {
        bool returnVal = collides(c, static_cast<Rectangle*>(s), info, minDistance);
        if(returnVal){
            info.setNormal(-info.getNormal());
        }
        return returnVal;
    }
    case ShapeType::polygon:
    {
        bool returnVal = collides(c, static_cast<Polygon*>(s), info, minDistance);
        if(returnVal){
            info.setNormal(-info.getNormal());
        }
        return returnVal;
    }
    case ShapeType::triangle:
    {
        bool returnVal = collides(c, static_cast<Triangle*>(s), info, minDistance);
        if(returnVal){
            info.setNormal(-info.getNormal());
        }
        return returnVal;
    }
    }
}

bool collides(ayin::CollisionShape *s, ayin::Rectangle *r, CollisionInfo& info, double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
        return collides(static_cast<Circle*>(s), r, info, minDistance);
    case ShapeType::rectangle:
    case ShapeType::polygon:
    case ShapeType::triangle:
        return collides(static_cast<PolygonShape*>(r), static_cast<PolygonShape*>(s), info, minDistance);
    }
}

bool collides(ayin::CollisionShape *s, ayin::Polygon *p, CollisionInfo& info, double , double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
    {
        bool col = collides(static_cast<Circle*>(s), p, info, minDistance);
        if(col){
            info.setNormal(-info.getNormal());
        }
        return col;
    }
    case ShapeType::rectangle:
    case ShapeType::polygon:
    case ShapeType::triangle:
    {
        bool col = collides(static_cast<PolygonShape*>(s), static_cast<PolygonShape*>(p), info, minDistance);
        if(col){
            info.setNormal(-info.getNormal());
        }
        return col;
    }
    }

}

bool collides(ayin::CollisionShape *s, ayin::Triangle *t, CollisionInfo& info, double , double minDistance){
    ShapeType x = s->type();
    switch(x){
    case ShapeType::circle:
    {
        bool col = collides(static_cast<Circle*>(s), t, info, minDistance);
        if(col){
            info.setNormal(-info.getNormal());
        }
        return col;
    }
    case ShapeType::rectangle:
    case ShapeType::polygon:
    case ShapeType::triangle:
    {
        bool col = collides(static_cast<PolygonShape*>(s), static_cast<PolygonShape*>(t), info, minDistance);
        if(col){
            info.setNormal(-info.getNormal());
        }
        return col;
    }
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
    case ShapeType::polygon:
        return collides(s2, static_cast<Polygon*>(s1), info, minDistance);
    case ShapeType::triangle:
        return collides(s2, static_cast<Triangle*>(s1), info, minDistance);
    }
}
