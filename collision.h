#ifndef COLLISION_H
#define COLLISION_H
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "collisioninfo.h"

bool collides(ayin::Circle* c1, ayin::Circle* c2, ayin::CollisionInfo& info);
bool collides(ayin::Rectangle* r1, ayin::Rectangle* r2, ayin::CollisionInfo& info);
bool collides(ayin::Circle* c, ayin::Rectangle* r, ayin::CollisionInfo& info);
bool collides(ayin::Circle* c, ayin::Triangle* t, ayin::CollisionInfo& info);
bool collides(ayin::PolygonShape *s1, ayin::PolygonShape *s2, ayin::CollisionInfo& info);
bool collides(ayin::CollisionShape *s1, ayin::CollisionShape *s2, ayin::CollisionInfo& info);

#endif // COLLISION_H
