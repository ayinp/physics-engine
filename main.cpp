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

//void enemyCollision(GameObject* me, GameObject* he, CollisionInfo info){
//    if(me->hasTag("enemy") && he->hasTag("player")){
//        he->kill();
//    }
//}
//void enemyUpdate(GameObject* me, Camera& c){
//    //I want them to somehow tell if theyre gonna walk off a clif and turn around
//    //for now tho ill jus make them turn around on screen
//    if(me->location.x + me->getWidth()/2 < 0){
//        me->velocity.x = -me->velocity.x;
//    }
//    if(me->location.x - me->getWidth()/2 > c.width()){
//        me->velocity.x = -me->velocity.x;
//    }

//}
void weaponCollision(GameObject* me, GameObject* he, CollisionInfo info){
    if(me->hasTag("weapon") && he->hasTag("enemy")){
        me->kill();
        he->kill();

    }
    else if(me->hasTag("weapon") && he->hasTag("ground")){

        me->location = me->getLastLoc();

        Vec2d normal = perp(me->location - info.collisionPoint).unit();

        Vec2d newX = normal * (dotProduct(normal, me->velocity)/dotProduct(normal, normal));
        Vec2d newY = me->velocity - newX;

        me->velocity = (newX - me->getElasticity()*newY);
    }

    if(abs(me->velocity.x) < 0.01){
        me->velocity.x = 0;

    }
    if(abs(me->velocity.y) < 0.01){
        me->velocity.y = 0;
    }
}

bool fallingDown(GameObject* me, GameObject* he){
    if(me->location.x - me->getWidth()/2){
        retrun true;
    }
    return false;
}

void weaponUpdate(GameObject* me, Camera& c){
    if(me->location.x + me->getWidth()/2 < 0){
        me->kill();
    }
    if(me->location.x - me->getWidth()/2 > c.width()){
        me->kill();
    }
    if(me->location.y +  me->getHeight()/2 < 0){
        me->kill();
    }
    if(me->location.y -  me->getHeight()/2 > c.height()){
        me->kill();
    }
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
//            // new guy spawn moment
//            double emySpawnRate = 0.01;
//            bool enemy = g.randomTrue(emySpawnRate);
//            if(enemy && world.whoHasTag("enemy").size() < 10){
//                int x = g.randomInt(0,1);
//                Vec2d location;
//                Vec2d velocity;
//                if(x == 0){
//                    location = {0, c.height()-100};
//                    velocity = {5,0};
//                }
//                else if(x == 1){
//                    location = {c.width(), c.height()-100};
//                    velocity = {-5,0};
//                }
//                unique_ptr<GameObject> e = make_unique<GameObject>(location, 50, 100, ShapeType::rectangle, enemyCollision, nullptr, nullptr, enemyUpdate);
//                e->affectedByGravity = false;
//                e->setElasticity(0);
//                e->velocity = velocity;
//                e->addTag("enemy");
//                world.objects.emplace_back(move(e));
//            }

//            if(g.onMousePress(MouseButton::Left)){
//                Vec2d direction = (g.mousePos()-player->location).unit();
//                Vec2d velocity = direction*5;
//                unique_ptr<GameObject> e = make_unique<GameObject>(player->location + velocity*15, 10, 10, ShapeType::circle, weaponCollision, nullptr, nullptr, weaponUpdate);
//                e->affectedByGravity = false;
//                e->velocity = velocity;
//                e->addTag("weapon");
//                world.objects.emplace_back(move(e));
//            }
        }
        else{

        }
    }

    return 0;

}












