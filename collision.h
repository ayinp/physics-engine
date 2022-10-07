#ifndef COLLISION_H
#define COLLISION_H
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

bool collides(ayin::Circle* c1, ayin::Circle* c2);
bool collides(ayin::Rectangle* r1, ayin::Rectangle* r2);
bool collides(ayin::Circle* c, ayin::Rectangle* r);
bool collides(ayin::Circle* c, ayin::Triangle* t);
bool collides(ayin::PolygonShape *s1, ayin::PolygonShape *s2);
bool collides(ayin::CollisionShape *s1, ayin::CollisionShape *s2);

#endif // COLLISION_H
