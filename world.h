#ifndef WORLD_H
#define WORLD_H
#include "gameObject.h"

namespace ayin{

class World
{
public:
    std::vector<GameObject> objects;
public:
    World();
    void draw(mssm::Graphics& g);
    void update(mssm::Graphics& g);
};
}

#endif // WORLD_H
