#include "world.h"
#include "collision.h"
#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
using namespace mssm;
using namespace ayin;

World::World(Vec2d gravity)
    :gravity{gravity}
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
        objects[i].update(g, gravity);
    }
    detectCollisions();
}

void World::detectCollisions()
{
    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
            CollisionInfo info;
            if(collides(objects[i].hitBox, objects[j].hitBox, info)){
                objects[i].onCollisionEnter(objects[j], info);
                objects[j].onCollisionEnter(objects[i], info);
            }

        }
    }
}


