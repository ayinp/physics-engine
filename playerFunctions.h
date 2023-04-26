#ifndef PLAYERFUNCTIONS_H
#define PLAYERFUNCTIONS_H
#include "scene.h"
#endif // PLAYERFUNCTIONS_H

class Counter : public ayin::Component
{
public:
    int num;
public:
    Counter(ayin::GameObject* owner, std::string name, int num);
    virtual void update() override {};
    void addCount(int n){num = num + n;};
    virtual void draw(ayin::Camera& c) override {};
};



void playerColEnter(ayin::CollisionInfo info);
void playerColLeave(ayin::CollisionInfo info);
void playerInitialization(ayin::Camera& c, ayin::Scene& scene);
void playerMovement(mssm::Graphics& g, ayin::GameObject* player);
