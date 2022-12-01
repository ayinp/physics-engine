#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>



class GameObject{};

namespace ayin{

class Component
{
public:
    GameObject* owner;
public:
    virtual void update() = 0;
};

#endif // COMPONENT_H
}



class Counter : ayin::Component
{
public:
    int num;
    std::string name;
public:
    Counter(int num, std::string name);
    virtual void update() override {};
};

Counter::Counter(int num, std::string name)
    :num{num}, name{name}
{

}
