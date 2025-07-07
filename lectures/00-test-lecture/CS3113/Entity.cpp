#include "Entity.h"

Entity::Entity() : mPosition {0.0f, 0.0f}, mAcceleration {0.0f, 0.0f}, 
                   mVelocity {0.0f, 0.0f}, mMovement {0.0f, 0.0f}, 
                   mWidth {1.0f}, mHeight {1.0f}, mSpeed {DEFAULT_SPEED}, 
                   mAngle {0.0f} {}

Entity::Entity(int screenWidth, int screenHeight, int height, int width, 
               int speed, const char* textureFilepath) : 
                    mPosition {screenWidth / 2.0f, screenHeight / 2.0f},
                    mAcceleration {0.0f, 9.81f}, mVelocity {0.0f, 0.0f},
                    mMovement {0.0f, 0.0f}, mWidth {width}, mHeight {height},
                    mSpeed {speed}, mAngle {0.0f}, 
                    mTexture {LoadTexture(textureFilepath)} {}

Entity::~Entity() { UnloadTexture(mTexture); };

bool const Entity::isColliding(Entity* other) const
{
    float xDistance = fabs(mPosition.x - other->mPosition.x) - ((mWidth + other->mWidth) / 2.0f);
    float yDistance = fabs(mPosition.y - other->mPosition.y) - ((mHeight + other->mHeight) / 2.0f);

    return xDistance < 0.0f && yDistance < 0.0f;
}

void const Entity::checkCollisionY(Entity *collidableEntities, int collidableEntityCount)
{
    for (int i = 0; i < collidableEntityCount; i++)
    {
        // STEP 1: For every entity that our player can collide with...
        Entity *collidableEntity = &collidableEntities[i];
        
        if (isColliding(collidableEntity))
        {
            // STEP 2: Calculate the distance between its centre and our centre
            //         and use that to calculate the amount of overlap between
            //         both bodies.
            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float yOverlap = fabs(yDistance - (mHeight / 2.0f) - (collidableEntity->mHeight / 2.0f));
            
            // STEP 3: "Unclip" ourselves from the other entity, and zero our
            //         vertical velocity.
            if (mVelocity.y > 0) 
            {
                mPosition.y -= yOverlap;
                mVelocity.y  = 0;
            } else if (mVelocity.y < 0) 
            {
                mPosition.y += yOverlap;
                mVelocity.y  = 0;
            }
        }
    }
}

void Entity::update(float deltaTime, Entity* collidableEntities, int collidableEntityCount)
{
    checkCollisionY(collidableEntities, collidableEntityCount);

    // mPosition.x += mMovement.x * mSpeed * deltaTime;
    // mPosition.y += mMovement.y * mSpeed * deltaTime;

    // Our character moves from left to right, so they need an initial velocity
    mVelocity.x = mMovement.x * mSpeed;

    // And we add the gravity next
    mVelocity.x += mAcceleration.x;
    mVelocity.y += mAcceleration.y;

    mPosition.x += mVelocity.x * deltaTime;
    mPosition.y += mVelocity.y * deltaTime;
}

void Entity::render()
{
    // Part of the texture to use for drawing (UV-coordinates)
    // in this case, the entire texture
    Rectangle textureArea = {
        0.0f, 0.0f,                                      // top-left corner
        (float) mTexture.width, (float) mTexture.height  // bottom-right corner
    };

    // Screen rectangle where drawing part of texture
    Rectangle destinationArea = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mWidth),
        static_cast<float>(mHeight)
    };

    // Origin of TEXTURE
    Vector2 objectOrigin = {
        (float) mTexture.width / 2.0f,  // x-coordinate
        (float) mTexture.height / 2.0f  // y-coordinate
    };

    DrawTexturePro(mTexture, textureArea, destinationArea, objectOrigin, mAngle, WHITE);
}