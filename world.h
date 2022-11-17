#ifndef WORLD_H
#define WORLD_H
#include "gameObject.h"

namespace ayin{

class World
{
public:
    std::vector<std::unique_ptr<GameObject>> objects;
    Vec2d gravity;
public:
    World(Vec2d gravity);
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
    void detectCollisions();
};
}

#endif // WORLD_H
