#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include <stdio.h>

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;
    Vector2 mAcceleration;
    Texture2D mTexture;
    int mWidth;
    int mHeight;
    int mSpeed;
    int mAngle = 0;

    bool const isColliding(Entity* other) const;
    void const checkCollisionY(Entity *collidableEntities, int collidableEntityCount);

public:
    static const int DEFAULT_SIZE = 40;
    static const int DEFAULT_SPEED = 5;

    Entity();
    Entity(int screenWidth, int screenHeight, 
        int height, int width, 
        int speed, const char* textureFilepath);
    ~Entity();

    void update(float deltaTime, Entity* collidableEntities, int collidableEntityCount);
    void render();

    void moveUp()    { mMovement.y = -1; }
    void moveDown()  { mMovement.y =  1; }
    void moveLeft()  { mMovement.x = -1; }
    void moveRight() { mMovement.x =  1; }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    const Vector2   getPosition()     const { return mPosition;     }
    const Vector2   getMovement()     const { return mMovement;     }
    const Vector2   getVelocity()     const { return mVelocity;     }
    const Vector2   getAcceleration() const { return mAcceleration; }
    const int       getWidth()        const { return mWidth;        }
    const int       getHeight()       const { return mHeight;       }

    void setPosition(Vector2 newPosition) { mPosition = newPosition; }
    void setMovement(Vector2 newMovement) { mMovement = newMovement; }
    void setVelocity(Vector2 newVelocity) { mVelocity = newVelocity; }
    void setAcceleration(Vector2 newAcceleration) { mAcceleration = newAcceleration; }
};

#endif // ENTITY_CPP