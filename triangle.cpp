#include "triangle.h"

using namespace mssm;
using namespace ayin;

Triangle::Triangle(Vec2d location, bool isRightTriangle, bool slopeLeft, int width, int height)
    :CollisionShape(location), isRightTriangle{isRightTriangle}, slopeLeft{slopeLeft}, width{width}, height{height}
{

}

ShapeType Triangle::type()
{
    return ShapeType::triangle;
}

Vec2d Triangle::center()
{
    return location;
}

Vec2d Triangle::centerOfMass()
{
    if(isRightTriangle){
        if(slopeLeft){
            Vec2d bottomRight = {location.x + width/2, location.y + height/2};
            return {bottomRight.x - width/3, bottomRight.y - height/3};
        }
        else{
            Vec2d bottomLeft = {location.x - width/2, location.y + height/2};
            return {bottomLeft.x + width/3, bottomLeft.y - height/3};
        }
    }
    else{
        Vec2d bottomCenter =  {location.x, location.y + height/2};
        return {bottomCenter.x, bottomCenter.y - height/3};
    }
}

vector<Vec2d> Triangle::corners()
{
    Vec2d corner1;
    Vec2d corner2;
    Vec2d corner3;

    if(isRightTriangle){
        if(slopeLeft){ //right angle is on right, hypot on left
            corner1 = {location.x + width/2, location.y - height/2};
            corner2 = {location.x - width/2, location.y + height/2};
            corner3 = {location.x + width/2, location.y + height/2};
        }
        else{ // right angle is on left, hypot on right
            corner1 = {location.x - width/2, location.y - height/2};
            corner2 = {location.x - width/2, location.y + height/2};
            corner3 = {location.x + width/2, location.y + height/2};
        }
    }
    else{ //equilatoral

        corner1 = {location.x, location.y - height/2};
        corner2 = {location.x - width/2, location.y + height/2};
        corner3 = {location.x + width/2, location.y + height/2};
    }

    return {corner1, corner2, corner3};
}

void Triangle::draw(mssm::Graphics &g)
{
    g.polygon(corners(), WHITE, WHITE);

    g.ellipse(corners()[0], 5, 5, RED, RED);
    g.ellipse(corners()[1], 5, 5, GREEN, GREEN);
    g.ellipse(corners()[2], 5, 5, YELLOW, YELLOW);

    g.ellipse(center(), 5, 5, RED, RED);
    g.ellipse(centerOfMass(), 5, 5, BLUE, BLUE);
}
