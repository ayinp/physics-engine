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
    for(int i = 0; i < objects.size(); i++){
        for(int j = 0; j < objects[i]->collisionInfos.size(); j++){
            objects[i]->collisionInfos[j].dead = true;
        }
    }
    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
            //establish an info object
            CollisionInfo info;
            if(collides(objects[i]->getHitbox(), objects[j]->getHitbox(), info, 10)){
                info.obj1 = objects[i].get();
                info.obj2 = objects[j].get();
                bool alreadyColiding = false;
                CollisionInfo* existing = info.obj1->getCollisionInfo(info.obj2);
                if(existing){
                    info.obj1->onCollisionStay(info);
                    info.obj2->onCollisionStay(info);
                    alreadyColiding = true;
                    existing->dead = false;
                    info.obj2->getCollisionInfo(info.obj1)->dead = false;
                    break;
                }
                if(!alreadyColiding){
                    info.obj1->collisionInfos.push_back(info);
                    info.obj2->collisionInfos.push_back(info);
                    info.obj1->onCollisionEnter(info);
                    info.obj2->onCollisionEnter(info);
                }
            }
        }
    }
    for(int i = 0; i < objects.size(); i++){
        erase_if(objects[i]->collisionInfos, [this, i](const auto& info){
            objects[i]->onCollisionLeave(info);
            return info.dead;});
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


