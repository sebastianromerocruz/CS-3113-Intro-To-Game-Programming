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
    Vector2 mVelocity;
    Vector2 mAcceleration;
    Texture2D mTexture;
    int mScreenWidth;
    int mScreenHeight;
    int mWidth;
    int mHeight;
    int mSpeed;

    int mAngle = 0;

    void frameReset();

public:
    static const int DEFAULT_SIZE = 40;
    static const int DEFAULT_SPEED = 5;

    Entity();
    Entity(Rectangle body, Vector2 position);
    Entity(int screenWidth, int screenHeight);
    Entity(int screenWidth, int screenHeight, 
        int height, int width, 
        int speed, const char* textureFilepath);
    ~Entity();

    void update(float deltaTime);
    void render();

    void moveUp()    { mMovement.y = -1; }
    void moveDown()  { mMovement.y =  1; }
    void moveLeft()  { mMovement.x = -1; }
    void moveRight() { mMovement.x =  1; }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }
    bool const checkCollision(Entity* other) const;

    const Rectangle getBody()         const { return mBody;     }
    const Vector2   getPosition()     const { return mPosition; }
    const Vector2   getMovement()     const { return mMovement; }
    const Vector2   getVelocity()     const { return mVelocity; }
    const Vector2   getAcceleration() const { return mAcceleration; }

    void setBody(Rectangle newBody)       { mBody = newBody;         }
    void setPosition(Vector2 newPosition) { mPosition = newPosition; }
    void setMovement(Vector2 newMovement) { mMovement = newMovement; }
    void setVelocity(Vector2 newVelocity) { mVelocity = newVelocity; }
    void setAcceleration(Vector2 newAcceleration) { mAcceleration = newAcceleration; }
};

#endif // ENTITY_CPP