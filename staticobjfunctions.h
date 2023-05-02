#ifndef GROUNDFUNCTIONS_H
#define GROUNDFUNCTIONS_H
#include "scene.h"
#endif

void groundInitialization(ayin::Scene& scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape);
void groundInitialization(ayin::Scene& scene, Vec2d location, double width, double height, ayin::ShapeType shape);
void wallInitialization(ayin::Scene& scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape);
void wallInitialization(ayin::Scene& scene, Vec2d location, double width, double height, ayin::ShapeType shape);
void obstacleInitialization(ayin::Scene& scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape);
void obstacleInitialization(ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape);
