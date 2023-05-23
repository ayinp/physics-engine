#ifndef INFOPAIR_H
#define INFOPAIR_H
#include "collisioninfo.h"

namespace ayin{

class InfoPair
{
public:
    CollisionInfo info1;
    CollisionInfo info2;
    int id;
    bool dead = false;
public:
    InfoPair(CollisionInfo info1, CollisionInfo info2, int id);
    void kill();
    bool isDead(){return dead;};
};
}

#endif // INFOPAIR_H
