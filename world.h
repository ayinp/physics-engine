#ifndef WORLD_H
#define WORLD_H
#include "scene.h"

namespace ayin{
class World
{
public:
    std::vector<Scene> scenes;
public:
    World(std::vector<Scene> scenes = {});
};
}
#endif // WORLD_H
