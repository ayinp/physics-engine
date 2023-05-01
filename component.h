#ifndef COMPONENT_H
#define COMPONENT_H
#include "camera.h"
#include "graphics.h"
#include <string>

namespace ayin{
class GameObject;

class Component
{
public:
    GameObject* owner;
    std:: string name;
public:
    Component(GameObject* owner, std::string name);
    virtual void update() = 0;
    virtual void revUpdate() = 0;
    virtual void draw(Camera& c) = 0;
};


}


#endif // COMPONENT_H
