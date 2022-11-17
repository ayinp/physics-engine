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

void enemyCollision(GameObject* me, GameObject* heHitMe, CollisionInfo info){
 heHitMe->dead = true;
}

//things I find out I need to do to make this better
//-make it so I can add sprites, and animations!
//-include world as a parametar in the on-collision in case I want to like effect the world when things collide
//-make some destinction in type of game object --> if a bullet hits the player, something different will happen than a tree.
//-a better way of referrnig to player other than world.objects[number]
//-distinguish between in-contact and colliding so no hops!
//-game object should have a property "dead" and then world should erase all the dead guys

int main(){
    Graphics g("mini-platformer", 1024, 768);

    World world({0, 0.3});

    unique_ptr<GameObject> p = make_unique<GameObject>(Vec2d{g.width()/2, g.height()/2}, 50, 100, ShapeType::triangle);
    p->affectedByGravity = true;
    p->elasticity = 0.2;
    world.objects.emplace_back(move(p));

    unique_ptr<GameObject> grnd = make_unique<GameObject>(Vec2d{g.width()/2, g.height()-25}, g.width()+200, 50, ShapeType::rectangle);
    grnd->velocity = {0,0};
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
                location = {-100, g.height()-100};
                velocity = {5,0};
            }
            else if(x == 1){
                location = {g.width()+100, g.height()-100};
                velocity = {-5,0};
            }
            unique_ptr<GameObject> e = make_unique<GameObject>(location, 50, 100, ShapeType::rectangle, enemyCollision);
            e->affectedByGravity = false;
            e->elasticity = 0;
            e->velocity = velocity;
            world.objects.emplace_back(move(e));
        }

        //GUNS ->this currently doesnt work

        if(g.onKeyPress(MouseButton::Left)){
            Vec2d direction = (player->location-g.mousePos()).unit();
            Vec2d velocity = direction*5;
            unique_ptr<GameObject> e = make_unique<GameObject>(player->location + velocity*10, 10, 10, ShapeType::circle, enemyCollision);
            e->affectedByGravity = false;
            e->elasticity = 1;
            e->velocity = velocity;
            world.objects.emplace_back(move(e));
        }

    }

    return 0;

}












