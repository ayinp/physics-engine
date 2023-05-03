#include "polygon.h"
#include <functional>

using namespace mssm;
using namespace ayin;

Polygon::Polygon(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc,  vector<Vec2d> points)
    :PolygonShape(locFunc, velFunc, points)
{
}

CollisionShape *Polygon::clone(std::function<Vec2d ()> locFunc, std::function<Vec2d()> velFunc)
{
    return new Polygon(locFunc, velFunc, points);
}

ShapeType Polygon::type()
{
    return ShapeType::polygon;
}

Vec2d Polygon::center()
{
    return location();
}

vector<Vec2d> ayin::Polygon::corners()
{
    vector<Vec2d> c;
    for(int i = 0; i < points.size(); i++){
        c.push_back(points[i] + location());
    }
    return c;
}

Vec2d Polygon::centerOfMass()
{
    Vec2d c;
    vector<Vec2d> pointsOld = points;
    vector<Vec2d> pointsNew;
    vector<Vec2d> centers;
    vector<double> areas;
    Vec2d p1;
    Vec2d p2;
    Vec2d p3;
    Vec2d p4;
    while(pointsOld.size() > 4){
        for(int i = 0; i < pointsOld.size()-1; i+=2){
            p1 = pointsOld[i];
            p2 = pointsOld[(i+1)%pointsOld.size()];
            p3 = pointsOld[(i+2)%pointsOld.size()];

            centers.push_back({(p1+p2+p3)/3});
            areas.push_back((p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y));
            if(i==0){
                pointsNew.push_back(p1);
            }
            pointsNew.push_back(p3);
        }
        pointsOld = pointsNew;
        pointsNew.clear();
    }
    if(pointsOld.size() == 4){
        p1 = pointsOld[0];
        p2 = pointsOld[1];
        p3 = pointsOld[2];
        p4 = pointsOld[3];
        centers.push_back({(p1+p2+p3)/3});
        areas.push_back((p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y));
        centers.push_back({(p3+p4+p1)/3});
        areas.push_back((p4.x-p3.x)*(p1.y-p3.y) - (p1.x-p3.x)*(p4.y-p3.y));
    }
    if(pointsOld.size() == 3){
        p1 = pointsOld[0];
        p2 = pointsOld[1];
        p3 = pointsOld[2];
        centers.push_back({(p1+p2+p3)/3});
        areas.push_back((p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y));
    }

    for(int i = 0; i < centers.size(); i++){
        c += centers[i]/areas[i];
    }

    c = {c.x/points.size(), c.y/points.size()};
    c += location();
    return c;
}

//vector<Vec2d> expand(vector<Vec2d>, double);


void Polygon::draw(Camera& c, Color color)
{
    c.polygon(corners(), color);

    for(int i = 0; i < corners().size(); i++){
        c.ellipse(corners()[i], 3, 3, WHITE, WHITE);
        c.text(corners()[i] + Vec2d{5,-5}, 15, to_string(i), WHITE);
    }
    c.ellipse(center(), 5, 5, RED, RED);
    c.ellipse(centerOfMass(), 5, 5, BLUE, BLUE);
}
