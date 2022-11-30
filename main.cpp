#include <iostream>
#include "graphics.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "vec2d.h"
#include "collision.h"
#include "world.h"
//#include "paths.h"

using namespace std;
using namespace mssm;
using namespace ayin;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

//TO DO
// make normal vector as field in collision info
// set when I set collision point
// make sure objects are like
// traveling towards eachother
// not away
// because away they arent colliding lol

void enemyCollision(GameObject* me, GameObject* he, CollisionInfo info){
    if(me->hasTag("enemy") && he->hasTag("player")){
        he->kill();
    }
}
void enemyUpdate(GameObject* me, Graphics& g){
    //I want them to somehow tell if theyre gonna walk off a clif and turn around
    //for now tho ill jus make them turn around on screen
        if(me->location.x + me->getWidth()/2 < 0){
            me->velocity.x = -me->velocity.x;
        }
        if(me->location.x - me->getWidth()/2 > g.width()){
            me->velocity.x = -me->velocity.x;
        }

}
void weaponCollision(GameObject* me, GameObject* he, CollisionInfo info){
    if(me->hasTag("weapon") && he->hasTag("enemy")){
        me->kill();
        he->kill();

    }
}
void weaponUpdate(GameObject* me, Graphics& g){
    if(me->location.x + me->getWidth()/2 < 0){
        me->kill();
    }
    if(me->location.x - me->getWidth()/2 > g.width()){
        me->kill();
    }
    if(me->location.y +  me->getHeight()/2 < 0){
        me->kill();
    }
    if(me->location.y -  me->getHeight()/2 > g.height()){
        me->kill();
    }
}



//things I find out I need to do to make this better
//-make it so I can add sprites, and animations!
//-distinguish between in-contact and colliding so no hops!
//-it would be cool to have a method that can report the number of objects with a certain tag in the world
//-add camera


int main(){
    Graphics g("mini-platformer", 1024, 768);

    World world({0, 0.3});

    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{g.width()/2, g.height()/2}, 50, 100, ShapeType::triangle);
    p->affectedByGravity = true;
    p->setElasticity(0.2);
    p->addTag("player");
    p->addTag("test");
    world.objects.emplace_back(move(p));

    unique_ptr<GameObject> grnd = make_unique<GameObject>(Vec2d{g.width()/2, g.height()-25}, g.width()+200, 50, ShapeType::rectangle);
    grnd->velocity = {0,0};
    grnd->addTag("ground");
    world.objects.emplace_back(move(grnd));

    GameObject* player = world.objects[0].get();

    while (g.draw()) {

        world.update(g);
        world.draw(g);

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
        if(g.onKeyPress('W')||g.onKeyPress(Key::Up) || g.onKeyPress(Key::Space)){
            player->velocity = {0, -10};
        }

        // new guy spawn moment
        double emySpawnRate = 0.01;
        bool enemy = g.randomTrue(emySpawnRate);
        if(enemy){
            int x = g.randomInt(0,1);
            Vec2d location;
            Vec2d velocity;
            if(x == 0){
                location = {0, g.height()-100};
                velocity = {5,0};
            }
            else if(x == 1){
                location = {g.width(), g.height()-100};
                velocity = {-5,0};
            }
            unique_ptr<GameObject> e = make_unique<GameObject>(location, 50, 100, ShapeType::rectangle, enemyCollision, nullptr, nullptr, enemyUpdate);
            e->affectedByGravity = false;
            e->setElasticity(0);
            e->velocity = velocity;
            e->addTag("enemy");
            world.objects.emplace_back(move(e));
        }

        if(g.onMousePress(MouseButton::Left)){
            g.cerr << "SHOT" << endl;
            Vec2d direction = (g.mousePos()-player->location).unit();
            Vec2d velocity = direction*5;
            unique_ptr<GameObject> e = make_unique<GameObject>(player->location + velocity*15, 10, 10, ShapeType::circle, weaponCollision, nullptr, nullptr, weaponUpdate);
            e->affectedByGravity = false;
            e->velocity = velocity;
            e->addTag("weapon");
            world.objects.emplace_back(move(e));
        }


    }

    return 0;

}












