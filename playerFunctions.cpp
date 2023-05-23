#include "graphics.h"
#include "scene.h"
#include "playerFunctions.h"
using namespace ayin;
using namespace mssm;
using namespace std;

// PLAYER COMPONENT CLASSES


Counter::Counter(GameObject* owner, std::string name, int num)
    :Component(owner, name), num{num}
{

}

//PLAYER COLLISION FUNCTIONS
void playerColEnter(CollisionInfo info){

}

void playerColStay(CollisionInfo info){

}

void playerColLeave(CollisionInfo info){

}

//PLAYER INITIALIZATION
void playerInitialization(Camera& c, Scene& scene){
    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{c.width()/2, c.height()/2}, 50, 100, ShapeType::rectangle,
                                                       playerColEnter, playerColLeave);
//    p->affectedByGravity = /*true*/ false;
    p->setElasticity(0.3);
    p->addTag("player");
    p->addComponent(make_unique<Counter>(p.get(), "jumps", 0));

    scene.objects.emplace_back(move(p));
}

//PLAYER MOVEMENT
void playerMovement(Graphics& g, GameObject* player){
    if((g.isKeyPressed('D') || g.isKeyPressed(Key::Right)) && player->velocity.x < 10){
        player->movementForce = {0.8, 0};
    }
    else if((g.isKeyPressed('A') || g.isKeyPressed(Key::Left)) && player->velocity.x > -10){
        player->movementForce = {-0.8,0};
    }
    else if((g.isKeyPressed('w') || g.isKeyPressed(Key::Up)) && player->velocity.y > -10){
        player->movementForce = {0, -0.8};
    }
    else if((g.isKeyPressed('s') || g.isKeyPressed(Key::Down)) && player->velocity.y < 10){
        player->movementForce = {0, 0.8};
    }
    else{
        player->movementForce = {0,0};
    }
//    if(((g.onKeyPress('W')|| g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space))
//        && player->getComponent<Counter>("jumps")->num < 1)){

//        player->velocity = {player->velocity.x, -10};
//        player->getComponent<Counter>("jumps")->addCount(1);
//    }
}
