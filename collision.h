#ifndef COLLISION_H
#define COLLISION_H
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "graphics.h"

bool collides(ayin::Circle* c1, ayin::Circle* c2);
bool collides(ayin::Rectangle* r1, ayin::Rectangle* r2);
bool collides(ayin::Triangle* t1, ayin::Triangle* t2);
bool collides(ayin::Circle* c, ayin::Rectangle* r, mssm::Graphics& g);
bool collides(ayin::Circle* c, ayin::Triangle* t);
bool collides(ayin::Rectangle* r, ayin::Triangle* t);

#endif // COLLISION_H
