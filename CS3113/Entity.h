#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include <stdio.h>

class Entity
{
public:
    Rectangle mBody;
    Vector2 mPosition;
    Vector2 mMovement;

    Entity();
    Entity(Rectangle body, Vector2 position);
    ~Entity();
};

#endif // ENTITY_CPP