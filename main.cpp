#include <iostream>
#include "graphics.h"
#include "vec2d.h"
#include "scene.h"
#include "playerFunctions.h"
#include "staticobjfunctions.h"
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

// - make scenes more versatile --> scene components??

using namespace std;
using namespace mssm;
using namespace ayin;

#ifndef _MSC_VER
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

bool playing = false;

void enterScreen(Graphics& g){
    g.cout << "press space to play" << endl;
    if(g.isKeyPressed(' ')){
        playing = true;
        return;
    }
    return;
}

void game(Graphics& g, Camera& c, World& world , bool& debug){

    if(g.onKeyPress('T')){
        debug = !debug;
    }
    if(debug){
        if(g.onKeyPress('P') || (g.isKeyPressed('P') && g.isCtrlKeyPressed())){
            world.update(g,c);
        }
    }
    else{
        world.update(g,c);
    }
    world.draw(c);

    GameObject* player = world.getCurrentScene()->getFirstTag("player");
    c.offset = Vec2d{g.width()/2, 3*g.height()/5} - (player->location);

    g.cout<< "PLAYER LOC: " <<  player->location << endl;
    g.cout<< "PLAYER VEL: " <<  player->velocity << endl;


    if(player){
        //player movement
        playerMovement(g, player);
        g.cout << "Jumps: " << player->getComponent<Counter>("jumps")->num << endl;
    }
    else{
        playing = false;
    }
}

int main(){
    Graphics g("mini-platformer", 1024, 768);
    while(g.draw()){
        Camera c(g);
        Scene scene0({0, 0.1});

        playerInitialization(c, scene0);


        groundInitialization(scene0, Vec2d{g.width()/2, g.height() + 25}, g.width(), 25, ShapeType::rectangle);

        wallInitialization(scene0, Vec2d{0, g.height()/2 - 50}, 25, g.height(), ShapeType::rectangle);

//        obstacleInitialization(scene0, Vec2d{g.width()/2+50, 500}, {{0,-100}, {-100, 100}, {100, 100}}, ShapeType::triangle);

//        obstacleInitialization(scene0, Vec2d{800, 400}, 50,50, ShapeType::circle);
//        obstacleInitialization(scene0, Vec2d{900, 400}, 50,50, ShapeType::circle);
        //    obstacleInitialization(scene0, Vec2d{500,200}, {{0,-100}, {-100,0}, {-100, 10}, {10, 30}, {100, -40}, {-20, -30}}, ShapeType::polygon);

        World world({move(&scene0)});
        bool debug = false;

        while (g.draw()) {
            if(!playing){
                enterScreen(g);
            }
            else{
                game(g, c, world, debug);
            }
            if(g.onKeyPress('R')){
                break;
            }
        }
    }

    return 0;

}












