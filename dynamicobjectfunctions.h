#ifndef DYNAMICOBJECTFUNCTIONS_H
#define DYNAMICOBJECTFUNCTIONS_H

#include "scene.h"

void dynamicObstacleInitialization(mssm::Graphics &g, ayin::Scene& scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape);
void dynamicObstacleInitialization(mssm::Graphics &g, ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape);

#endif // DYNAMICOBJECTFUNCTIONS_H
