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

    erase_if(objects, [](const auto& obj){return obj->isDead();});

//    erase_if(objects, [](const unique_ptr<GameObject>& obj)-> bool
//    { return obj->isDead() == true; });

//    //removes every element in list that returned true in line 9
//    objects.erase(std::remove_if(objects.begin(), objects.end(),
//                                 [&](const unique_ptr<GameObject>& obj)-> bool
//    { return obj->isDead() == true; }), //any condition
//                  objects.end());


    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(c, gravity);
    }
    detectCollisions();
}

void World::detectCollisions()
{
    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
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


