#ifndef COMPONENT_H
#define COMPONENT_H

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
};


}


#endif // COMPONENT_H
