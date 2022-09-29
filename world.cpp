#include "world.h"
using namespace mssm;
using namespace ayin;

World::World()
{

}

void ayin::World::draw(mssm::Graphics &g)
{
    for(int i = 0; i < objects.size(); i++){
        objects[i].draw(g);
    }


}

void ayin::World::update(mssm::Graphics &g)
{
    for(int i = 0; i < objects.size(); i++){
        objects[i].update(g);
    }
}
