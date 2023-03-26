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

    cout << "ENTER " << info.obj1->hasTag("player") << endl;
    info.obj1->location = info.obj1->getLastLoc();
    Vec2d normal = perp(info.obj1->location - info.collisionPoint).unit();
    ;
    cout << normal << endl;
    Vec2d newX = normal * (dotProduct(normal, info.obj1->velocity)/dotProduct(normal, normal));
    Vec2d newY = info.obj1->velocity - newX;
    info.obj1->velocity = (newX - info.obj1->getElasticity()*newY);

    if(abs(info.obj1->velocity.x) < 0.5){
        info.obj1->velocity.x = 0;
    }
    if(abs(info.obj1->velocity.y) < 0.5){
        info.obj1->velocity.y = 0;
    }
    if(info.obj2->hasTag("ground")){
        info.obj1->affectedByGravity = false;
        info.obj1->getComponent<Counter>("jumps")->num = 0;
    }
}
void playerColLeave(CollisionInfo info){
    if(info.obj1->hasTag("player") && info.obj2->hasTag("ground")){
        info.obj1->affectedByGravity = true;
    }
    else if(info.obj2->hasTag("player") && info.obj1->hasTag("ground")){
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
            player->acceleration.x = max(-0.3,-player->velocity.x);
        }
        else if(player->velocity.x < -0.1){
            player->acceleration.x = min(0.3,-player->velocity.x);
        }
        else{
            player->velocity.x = 0;
            player->acceleration.x = 0;
        }
    }
    if(((g.onKeyPress('W')|| g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space))
             && player->getComponent<Counter>("jumps")->num < 1)){

        player->velocity = {player->velocity.x, -5};
        player->getComponent<Counter>("jumps")->addCount(1);
    }
}
