#include "staticobjfunctions.h"
using namespace ayin;

void groundInitialization(Scene &scene, Vec2d location, vector<Vec2d> points, ShapeType shape)
{
    unique_ptr<GameObject> grnd = make_unique<GameObject>(location, points, shape, true);
    grnd->addTag("ground");
    scene.objects.emplace_back(move(grnd));
}

void groundInitialization(ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> grnd = make_unique<GameObject>(location, width, height, shape, true);
    grnd->addTag("ground");
    scene.objects.emplace_back(move(grnd));
}

void wallInitialization(ayin::Scene &scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape)
{
    unique_ptr<GameObject> wall = make_unique<GameObject>(location, points, shape, true);
    wall->addTag("wall");
    scene.objects.emplace_back(move(wall));
}

void wallInitialization(ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> wall = make_unique<GameObject>(location, width, height, shape, true);
    wall->addTag("wall");
    scene.objects.emplace_back(move(wall));
}


void staticObstacleInitialization(mssm::Graphics&g, ayin::Scene &scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape)
{
    unique_ptr<GameObject> obs = make_unique<GameObject>(location, points, shape, true);
    obs->addTag("obs");
    scene.objects.emplace_back(move(obs));
}

void staticObstacleInitialization(mssm::Graphics& g, ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> obs = make_unique<GameObject>(location, width, height, shape, true);
    obs->addTag("obs");
    scene.objects.emplace_back(move(obs));
}


