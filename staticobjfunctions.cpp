#include "staticobjfunctions.h"
using namespace ayin;

void groundInitialization(Scene &scene, Vec2d location, double width, double height, ShapeType shape)
{
    unique_ptr<GameObject> grnd = make_unique<GameObject>(location, width, height, shape);
    grnd->velocity = {0,0};
    grnd->addTag("ground");
    scene.objects.emplace_back(move(grnd));
}

void wallInitialization(ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> wall = make_unique<GameObject>(location, width, height, shape);
    wall->velocity = {0,0};
    wall->addTag("wall");
    scene.objects.emplace_back(move(wall));
}


void obstacleiInitialization(ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> obs = make_unique<GameObject>(location, width, height, shape);
    obs->velocity = {0,0};
    obs->addTag("obs");
    scene.objects.emplace_back(move(obs));
}
