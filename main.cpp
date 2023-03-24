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

int main(){
    Graphics g("mini-platformer", 1024, 768);
    Camera c(g);
    World world({0, 0.3});

    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{c.width()/2, c.height()/2}, 50, 100, ShapeType::triangle);
    p->affectedByGravity = true;
    p->setElasticity(0.2);
    p->addTag("player");
    p->addTag("test");
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
                    player->acceleration.x = -0.5;
                }
                else if(player->velocity.x < 0.1){
                    player->acceleration.x = 0.5;
                }
                else{
                    player->velocity.x = 0;
                    player->acceleration.x = 0;
                }
            }
            // player jumpin
            if(!player->isDead()){
                if((g.onKeyPress('W')|| g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space))){
                    player->velocity = {0, -10};
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












