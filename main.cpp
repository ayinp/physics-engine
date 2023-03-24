#include <iostream>
#include "graphics.h"
#include "vec2d.h"
#include "world.h"

//#include "paths.h"

//TO DO
// - fix normal on poly poly colision function in colision.cpp
//    this will help get direction of colision
//    which will help reduce the hopping
// - distinguish between in-contact and colliding so no hops!
// - impliment adding sprites, and animations
// - figure out when to call onColisionLeave and onColisionStay
//    they arent currently ever being called lmao, but they would also
//    be useful for getting rid of the hops. maybe the solution.
// - eventually I really need to consider rotation too
// - make triangles less wonky, and potentially just make them polygons
//    we should probably impliment polygons in general
// - revisit "come back to this" in circle triangle and circle rectangle colisionin colision.cpp
// - revisit "change this" in colision point function in colision.cpp
// - finish falling down function in main
// - tags method on game objects
// - collisionInfo.normal is not being set for polygon-polygon collision
// - if gameobject is deleted, we'll need to cleanup collisioninfo from other objects that it is in contact with.


using namespace std;
using namespace mssm;
using namespace ayin;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif


class Counter : public ayin::Component
{
public:
    int num;
public:
    Counter(GameObject* owner, std::string name, int num);
    virtual void update() override {};
    void addCount(int n){num = num + n;};
    virtual void draw(Camera& c) override {};
};

Counter::Counter(GameObject* owner, std::string name, int num)
    :Component(owner, name), num{num}
{

}

void playerColEnter(CollisionInfo info){

 cout << "ENTER " << info.obj1->hasTag("player") << endl;
        info.obj1->location = info.obj1->getLastLoc();
        Vec2d normal = perp(info.obj1->location - info.collisionPoint).unit();

        cout << "NORMALLL_________________________________" << endl;
        cout << normal << endl;
        Vec2d newX = normal * (dotProduct(normal, info.obj1->velocity)/dotProduct(normal, normal));
        Vec2d newY = info.obj1->velocity - newX;
        info.obj1->velocity = (newX - info.obj1->getElasticity()*newY);

        if(abs(info.obj1->velocity.x) < 1){
            info.obj1->velocity.x = 0;
        }
        if(abs(info.obj1->velocity.y) < 1){
            info.obj1->velocity.y = 0;
        }
        info.obj1->affectedByGravity = false;
        cout << "no more gravity" << endl;
}

void playerColStay(CollisionInfo info){
    cout << "STAY" << endl;
}

void playerColLeave(CollisionInfo info){
    cout << "LEAVE " << info.obj1->hasTag("player") << endl;
    if(info.obj1->hasTag("player")){
        if(info.obj2->hasTag("ground")){
            info.obj1->affectedByGravity = true;
            cout << "gravity" << endl;
        }
    }
    else if(info.obj2->hasTag("player")){
        if(info.obj1->hasTag("ground")){
            info.obj1->affectedByGravity = true;
            cout << "gravity" << endl;
        }
    }
}

int main(){
    Graphics g("mini-platformer", 1024, 768);
    Camera c(g);
    World world({0, 0.1});

    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{c.width()/2, c.height()/2}, 50, 100, ShapeType::triangle);

    p->collisionStay = playerColStay;
    p->collisionLeave = playerColLeave;
    p->collisionEnter = playerColEnter;
    p->affectedByGravity = true;
    p->setElasticity(0.2);
    p->addTag("player");
    p->addComponent(make_unique<Counter>(p.get(), "jumps", 0));
    world.objects.emplace_back(move(p));



    unique_ptr<GameObject> grnd = make_unique<GameObject>(Vec2d{g.width()/2, g.height()-25}, g.width()+200, 50, ShapeType::rectangle);
    grnd->velocity = {0,0};
    grnd->addTag("ground");
    world.objects.emplace_back(move(grnd));


    while (g.draw()) {

        world.update(c);
        world.draw(c);

        GameObject* player = world.getFirstTag("player");
        c.offset = Vec2d{g.width()/2, 3*g.height()/5} - (player->location);

        if(player){
            //player movement
            if(g.isKeyPressed('D') || g.isKeyPressed(Key::Right)){
                player->acceleration.x = 0.5;
                if(player->velocity.x >= 10){
                    player->acceleration.x = 0;
                }
            }
            else if(g.isKeyPressed('A') || g.isKeyPressed(Key::Left)){
                player->acceleration.x = -0.5;
                if(player->velocity.x <= -10){
                    player->acceleration.x = 0;
                }
            }
            else{
                if(player->velocity.x > 0.1){
                    player->acceleration.x = max(-0.1,-player->velocity.x);
                }
                else if(player->velocity.x < -0.1){
                    player->acceleration.x = min(0.1,-player->velocity.x);
                }
                else{
                    player->velocity.x = 0;
                    player->acceleration.x = 0;
                }
            }
            // player jumpin
            if(!player->isDead()){
                if((g.onKeyPress('W')|| g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space))){
                    player->velocity = {player->velocity.x, -5};
                    player->getComponent<Counter>("jumps")->addCount(1);
                }
            }
            g.cout << "Jumps: " << player->getComponent<Counter>("jumps")->num << endl;
        }
        else{

        }
    }

    return 0;

}












