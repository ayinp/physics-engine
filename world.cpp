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

void ayin::World::draw(Camera& c)
{
    for(int i = 0; i < objects.size(); i++){
        objects[i]->draw(c);
    }


}

void ayin::World::update(Camera& c)
{
    //erase dead game objects
    erase_if(objects, [](const auto& obj){return obj->isDead();});
    //update objects
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(c, gravity);
    }
    //look for colisions
    detectCollisions();
}

void World::detectCollisions()
{
    //loop over the objects
    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
            //establish an info object
            CollisionInfo info;
            if(collides(objects[i]->getHitbox(), objects[j]->getHitbox(), info)){
                objects[i]->onCollisionEnter(*objects[j], info);
                objects[j]->onCollisionEnter(*objects[i], info);
            }
        }
    }
}

std::vector<GameObject*> World::whoHasTag(string tag)
{
    vector<GameObject*> guys;
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]->hasTag(tag)){
            guys.push_back(objects[i].get());
        }
    }
    return guys;
}

GameObject *World::getFirstTag(string tag)
{
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]->hasTag(tag)){
            return objects[i].get();
        }
    }
    return nullptr;
}


