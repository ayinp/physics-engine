#include "gameObject.h"
using namespace ayin;

GameObject::GameObject(Vec2d location, CollisionShape *hitBox)
    :location{location}, hitBox{hitBox}
{

}

void GameObject::draw(mssm::Graphics &g)
{
    hitBox->draw(g);
}

void GameObject::update(mssm::Graphics &g)
{
    location = location + velocity;

    // i know this has hard coding shut up

    if(location.x + 50 < 0){
        location.x = g.width() + 50;
    }
    else if(location.x - 50 > g.width()){
        location.x = 0 - 50;
    }

    if(location.y + 50 < 0){
        location.y = g.height() + 50;
    }
    else if(location.y - 50 > g.height()){
        location.y = 0 - 50;
    }

    hitBox->location = location;
}
