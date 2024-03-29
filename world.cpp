#include "world.h"

using namespace ayin;
using namespace std;

World::World(vector<Scene*> scenes)
    :scenes{move(scenes)}
{

}

void World::update(mssm::Graphics &g, Camera& c)
{
    getCurrentScene()->update(g,c);
}

void World::draw(Camera &c)
{
    getCurrentScene()->draw(c);
}

Scene* World::getCurrentScene()
{
    return scenes[currentSceneIndx];
}
