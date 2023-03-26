#ifndef SCENE_H
#define SCENE_H

#include "gameObject.h"
namespace ayin{

class Scene
{
public:
    std::vector<std::unique_ptr<GameObject>> objects;
    Vec2d gravity;
public:
    Scene(Vec2d gravity);
    void draw(Camera& c);
    void update(Camera& c);
    void detectCollisions();
    std::vector<GameObject*> whoHasTag(string tag);
    GameObject *getFirstTag(string tag);
};
}


#endif // SCENE_H
