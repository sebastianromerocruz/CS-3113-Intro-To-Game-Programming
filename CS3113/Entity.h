#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <stdio.h>

class Entity
{
private:
    Rectangle mBody;
    Vector2 mPosition;
    Vector2 mMovement;
    Texture2D mTexture;

    void frameReset();

public:
    static const int DEFAULT_SIZE = 40;

    Entity();
    Entity(Rectangle body, Vector2 position);
    Entity(int screenWidth, int screenHeight);
    Entity(int screenWidth, int screenHeight, int height, int width, const char* textureFilepath);
    ~Entity();

    void update();

    void moveUp()    { mMovement.y = -1; }
    void moveDown()  { mMovement.y =  1; }
    void moveLeft()  { mMovement.x = -1; }
    void moveRight() { mMovement.x =  1; }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    const Rectangle getBody()     const { return mBody;     }
    const Vector2   getPosition() const { return mPosition; }
    const Vector2   getMovement() const { return mMovement; }

    void setBody(Rectangle newBody)       { mBody = newBody;         }
    void setPosition(Vector2 newPosition) { mPosition = newPosition; }
    void setMovement(Vector2 newMovement) { mMovement = newMovement; }
};

#endif // ENTITY_CPP