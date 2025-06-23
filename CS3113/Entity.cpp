#include "Entity.h"

Entity::Entity() : mBody { 0.0f, 0.0f, 0.0f, 0.0f }, mPosition { 0.0f, 0.0f }, 
                   mMovement { 0.0f, 0.0f }, mScreenWidth {0}, mScreenHeight {0}, 
                   mSpeed {DEFAULT_SPEED} {}

Entity::Entity(Rectangle body, Vector2 position) : mBody {body}, 
                                                   mPosition {position}, 
                                                   mMovement { 0.0f, 0.0f },
                                                   mScreenWidth {0}, 
                                                   mScreenHeight {0}, 
                                                   mSpeed {DEFAULT_SPEED} {}

Entity::Entity(int screenWidth, int screenHeight) : mMovement { 0.0f, 0.0f }, 
                                                    mSpeed {DEFAULT_SPEED}
{
    mScreenHeight = screenHeight;
    mScreenWidth = screenWidth;

    mBody = {
        screenWidth  / 2.0f,
        screenHeight / 2.0f,
        DEFAULT_SIZE,
        DEFAULT_SIZE
    };

    mPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
}

Entity::Entity(int screenWidth, int screenHeight, int height, int width, int speed, const char* textureFilepath) : Entity { screenWidth, screenHeight }
{
    mWidth   = width;
    mHeight  = height;
    mSpeed   = speed;
    mAcceleration = { 0.0f, 9.81f };
    mVelocity = { 0.0f, 0.0f };
    mTexture = LoadTexture(textureFilepath);
}

Entity::~Entity() 
{
    UnloadTexture(mTexture);
};

bool const Entity::checkCollision(Entity* other) const
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
        
        if (checkCollision(collidableEntity))
        {
            // STEP 2: Calculate the distance between its centre and our centre
            //         and use that to calculate the amount of overlap between
            //         both bodies.
            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float y_overlap = fabs(yDistance - (mHeight / 2.0f) - (collidableEntity->mHeight / 2.0f));
            
            // STEP 3: "Unclip" ourselves from the other entity, and zero our
            //         vertical velocity.
            if (mVelocity.y > 0) {
                mPosition.y -= y_overlap;
                mVelocity.y  = 0;
            } else if (mVelocity.y < 0) {
                mPosition.y += y_overlap;
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

    // mBody.x = mPosition.x; 
    // mBody.y = mPosition.y;

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
    Rectangle textureRect = { 0.0f, 0.0f, (float) mTexture.width, (float) mTexture.height };

    // Screen rectangle where drawing part of texture
    Rectangle destinationRect = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mWidth),
        static_cast<float>(mHeight)
    };

    // Origin of TEXTURE
    Vector2 textureOrigin = { (float) mTexture.width / 2.0f, (float) mTexture.height / 2.0f };

    DrawTexturePro(mTexture, textureRect, destinationRect, textureOrigin, mAngle, WHITE);
}