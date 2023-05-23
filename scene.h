#ifndef SCENE_H
#define SCENE_H

#include "gameObject.h"
#include "infopair.h"
#include "uniqueid.h"

namespace ayin{

class Scene
{
public:
    std::vector<std::unique_ptr<GameObject>> objects;
    std::vector<InfoPair> infoPairs;
    Vec2d gravity;
    UniqueIdSystem id;
public:
    Scene(Vec2d gravity);
    void draw(Camera& c);
    void update(mssm::Graphics &g, Camera& c);
    void detectCollisions(mssm::Graphics& g);
    void processCollisions(mssm::Graphics &g);

    std::vector<GameObject*> whoHasTag(string tag);
    GameObject *getFirstTag(string tag);
};
}


#endif // SCENE_H
