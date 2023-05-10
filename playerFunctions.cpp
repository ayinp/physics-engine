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
    //cases
    if((info.obj2->hasTag("ground") || info.obj2->hasTag("obs")) && info.getColPoint().y > info.obj1->location.y){
        info.obj1->getComponent<Counter>("jumps")->num = 0;
    }
}

//void playerColStay


void playerColLeave(CollisionInfo info){
    if((info.obj1->hasTag("player") && info.obj2->hasTag("ground")) || (info.obj1->hasTag("player") && info.obj2->hasTag("obs"))){
        info.obj1->affectedByGravity = true;
    }
    else if((info.obj2->hasTag("player") && info.obj1->hasTag("ground")) || (info.obj2->hasTag("player") && info.obj1->hasTag("ground"))){
        info.obj1->affectedByGravity = true;
    }
}

//PLAYER INITIALIZATION
void playerInitialization(Camera& c, Scene& scene){
    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{c.width()/2, c.height()/2}, 50, 100, ShapeType::rectangle,
                                                       playerColEnter, playerColLeave);
    p->affectedByGravity = true;
    p->setElasticity(0);
    p->addTag("player");
    p->addComponent(make_unique<Counter>(p.get(), "jumps", 0));

    scene.objects.emplace_back(move(p));
}

//PLAYER MOVEMENT
void playerMovement(Graphics& g, GameObject* player){
    if(g.isKeyPressed('D') || g.isKeyPressed(Key::Right)){
        //        if(player->canMove(g,c,{1,0}) ){
        //            if(player->velocity.x >= 10){
        //                player->netForce -= {0.5,0}
        //            }
        //            else{
        player->movementForce = {0.5, 0};
        //            }
        //        }
        //        else{
        //            player->canMove(g, c, {1,0});
        //            g.cout << "CAN'T MOVE RIGHT" << endl;

        //        }
    }
    else if(g.isKeyPressed('A') || g.isKeyPressed(Key::Left)){
        //        if(player->canMove(g,c, {-1,0})){
        //            if(player->velocity.x <= -10){
        //                player->acceleration.x = 0;
        //            }
        //            else{
        player->movementForce = {-0.5,0};
        //            }
        //        }
        //        else{
        //            player->canMove (g, c, {-1,0});
        //            g.cout<< "CAN'T MOVE LEFT" << endl;
        //        }
    }
    else{
        player->movementForce = {0,0};
//            player->acceleration.x = max(-0.3,-player->velocity.x);

//            player->acceleration.x = min(0.3,-player->velocity.x);

    }
    if(((g.onKeyPress('W')|| g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space))
        && player->getComponent<Counter>("jumps")->num < 1)){

        player->velocity = {player->velocity.x, -10};
        player->getComponent<Counter>("jumps")->addCount(1);
    }
}
