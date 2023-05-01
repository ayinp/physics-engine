#ifndef WORLD_H
#define WORLD_H
#include "scene.h"

namespace ayin{
class World
{
public:
    std::vector<Scene*> scenes;
    int currentSceneIndx = 0;
public:
    World(std::vector<Scene*> scenes = {});
    void update(mssm::Graphics &g, Camera &c);
    void draw(Camera& c);
    Scene *getCurrentScene();
};
}
#endif // WORLD_H
