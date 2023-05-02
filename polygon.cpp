#include "triangle.h"

using namespace mssm;
using namespace ayin;

Polygon::Polygon(std::function<Vec2d()> locFunc, std::function<Vec2d()> velFunc,  vector<Vec2d> points)
    :PolygonShape(locFunc, velFunc, points)
{
    calcCenterOfMass();
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
    vector<Vec2d> corners;
    for(int i = 0; i < points.size(); i++){
        corners.push_back(points[i] + location());
    }
    return corners;
}

void Polygon::calcCenterOfMass()
{
    vector<Vec2d> pointsOld = points;
    vector<Vec2d> pointsNew;
    vector<Vec2d> centers;
    vector<double> areas;
    Vec2d p1;
    Vec2d p2;
    Vec2d p3;
    while(pointsOld.size() > 3){
        for(int i = 0; i < pointsOld.size(); i++){
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
    p1 = pointsOld[0];
    p2 = pointsOld[1];
    p3 = pointsOld[2];
    centers.push_back({(p1+p2+p3)/3});
    areas.push_back((p2.x-p1.x)*(p3.y-p1.y) - (p3.x-p1.x)*(p2.y-p1.y));

    for(int i = 0; i < centers.size(); i++){
        centerOfMass += centers[i]/areas[i];
    }

    centerOfMass += location();
}

//vector<Vec2d> expand(vector<Vec2d>, double);


void Polygon::draw(Camera& c, Color color)
{
    c.polygon(corners(), color);

    for(int i = 0; i < corners().size(); i++){
        c.text(corners()[i] + Vec2d{-5,-5}, 5, to_string(i), WHITE);
    }
    c.ellipse(center(), 5, 5, RED, RED);
    c.ellipse(centerOfMass, 5, 5, BLUE, BLUE);
}
