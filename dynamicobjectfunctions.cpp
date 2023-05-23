#include "dynamicobjectfunctions.h"

using namespace ayin;
void dynamicObstacleInitialization(mssm::Graphics&g, ayin::Scene &scene, Vec2d location, vector<Vec2d> points, ayin::ShapeType shape)
{
    unique_ptr<GameObject> obs = make_unique<GameObject>(location, points, shape);
    obs->velocity = {g.randomDouble(-5,5),g.randomDouble(-5,5)};
    obs->setElasticity(0.5);
    obs->addTag("obs");
    scene.objects.emplace_back(move(obs));
}

void dynamicObstacleInitialization(mssm::Graphics& g, ayin::Scene &scene, Vec2d location, double width, double height, ayin::ShapeType shape)
{
    unique_ptr<GameObject> obs = make_unique<GameObject>(location, width, height, shape);
    obs->velocity = {g.randomDouble(-5,5),g.randomDouble(-5,5)};
    obs->setElasticity(0.5);
    obs->addTag("obs");
    scene.objects.emplace_back(move(obs));
}
