#include "world.h"

using namespace ayin;
using namespace std;

World::World(vector<Scene*> scenes)
    :scenes{move(scenes)}
{

}

void World::update(Camera &c)
{
    getCurrentScene()->update(c);
}

void World::draw(Camera &c)
{
    getCurrentScene()->draw(c);
}

Scene* World::getCurrentScene()
{
    return scenes[currentSceneIndx];
}
