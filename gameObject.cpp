#include "gameObject.h"
using namespace ayin;

GameObject::GameObject(Vec2d location, CollisionShape *hitBox)
    :location{location}, hitBox{hitBox}
{

}
