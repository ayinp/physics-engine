#include "infopair.h"

using namespace ayin;

InfoPair::InfoPair(CollisionInfo info1, CollisionInfo info2, int id)
    :info1{info1}, info2{info2}, id{id}
{

}

void InfoPair::kill()
{
    dead = true;
    info1.dead = true;
    info2.dead = true;
}
