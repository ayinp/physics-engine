#include "groundfunctions.h"
using namespace ayin;

void groundInitialization(Camera &c, Scene &scene, Vec2d location, double width, double height, ShapeType shape)
{
    unique_ptr<GameObject> grnd = make_unique<GameObject>(location, width, height, shape);
    grnd->velocity = {0,0};
    grnd->addTag("ground");
    scene.objects.emplace_back(move(grnd));
}
