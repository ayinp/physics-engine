#include "scene.h"
#include "collision.h"
#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif
using namespace mssm;
using namespace ayin;

Scene::Scene(Vec2d gravity)
    :gravity{gravity}
{

}

void ayin::Scene::draw(Camera& c)
{
    for(int i = 0; i < objects.size(); i++){
        objects[i]->draw(c);
    }



}

void ayin::Scene::update(Graphics& g, Camera& c)
{
    //erase dead game objects
    erase_if(objects, [](const auto& obj){return obj->isDead();});

    detectCollisions(g);

    processCollisions(g);

    //forces and normals
    for(int i = 0; i < objects.size(); i++){
        objects[i]->appliedForce(gravity);
        objects[i]->normalCalcs(g);
    }
    //    for(int i = 0; i < objects.size(); i++){
    //        objects[i]->normalCalcs(g);
    //    }
    //update objects
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(g, c, gravity);
    }

}

void Scene::processCollisions(Graphics& g){
    //    for(int i = 0; i < objects.size(); i++){
    //        int count = 0;
    //        bool cols = true;
    //        while(cols){
    //            count++;
    //            cols = false;
    //            for(int j = 0; j < objects[i]->collisionInfos.size(); j++){
    //                objects[i]->impulseHandler(g, objects[i]->collisionInfos[j], cols);
    //            }
    //            if(count > 10){
    //                break;
    //            }
    //        }
    //    }
    g.cout<<infoPairs.size()<<endl;
    int count = 0;
    bool cols = true;
    while(cols){
        for(int i = 0; i < infoPairs.size(); i++){
            count++;
            cols = false;

            if(!infoPairs[i].info1.obj1->isStatic()){
                infoPairs[i].info1.obj1->impulseHandler(g, infoPairs[i].info1, cols);
            }
            else if(!infoPairs[i].info1.obj2->isStatic()){
                infoPairs[i].info1.obj2->impulseHandler(g, infoPairs[i].info2, cols);
            }
            else{
                if(!infoPairs[i].info1.obj1->hasTag("wall") && !infoPairs[i].info1.obj2->hasTag("wall") ){
                    g.cout<< infoPairs[i].info1.obj1->isStatic() << infoPairs[i].info1.obj2->isStatic() <<endl;
                }
            }

        }
        if(count > 10){
            g.cerr << "BREAK LOOP" << endl;
            break;
        }
    }
}

void Scene::detectCollisions(Graphics &g)
{
    for(int i = 0; i < infoPairs.size(); i++){
        if(!collides(infoPairs[i].info1.obj1->getHitbox(), infoPairs[i].info1.obj2->getHitbox(), infoPairs[i].info1, 2)){
            infoPairs[i].kill();
        }

    }


    for(int i = 0; i < objects.size(); i++){
        for(int j = 0; j < objects[i]->collisionInfos.size(); j++){
            CollisionInfo &info = objects[i]->collisionInfos[j];
            if(collides(info.obj1->getHitbox(), info.obj2->getHitbox(), info, 2)){
                info.checkNorm();
                info.obj1->onCollisionStay(info);
            }
            else{
                info.kill();
            }

        }
    }


    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
            //establish an info object
            CollisionInfo info;
            if(collides(objects[i]->getHitbox(), objects[j]->getHitbox(), info, 0)){
                info.obj1 = objects[i].get();
                info.obj2 = objects[j].get();
                CollisionInfo* existing = info.obj1->getCollisionInfo(info.obj2);
                if(!existing){
                    CollisionInfo info2 = info;
                    info2.reverse();

                    info.checkNorm();
                    info2.checkNorm();

                    info.obj1->collisionInfos.push_back(info);
                    info.obj2->collisionInfos.push_back(info2);

                    info.obj1->onCollisionEnter(info);
                    info.obj2->onCollisionEnter(info2);

                    infoPairs.push_back(InfoPair(info, info2, id.newId()));
                }
            }
        }
    }

    for(int i = 0; i < objects.size(); i++){
        erase_if(objects[i]->collisionInfos, [this, i](const auto& info){
            if(info.dead){
                objects[i]->onCollisionLeave(info);
            }
            return info.dead;
        });
    }

    erase_if(infoPairs, [this](const auto& ip){return ip.dead;});
}

std::vector<GameObject*> Scene::whoHasTag(string tag)
{
    vector<GameObject*> guys;
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]->hasTag(tag)){
            guys.push_back(objects[i].get());
        }
    }
    return guys;
}

GameObject *Scene::getFirstTag(string tag)
{
    for(int i = 0; i < objects.size(); i++){
        if(objects[i]->hasTag(tag)){
            return objects[i].get();
        }
    }
    return nullptr;
}


