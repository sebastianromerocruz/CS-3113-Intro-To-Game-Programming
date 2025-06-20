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

void Entity::frameReset()
{
    mBody.x = 0;
    mBody.y = 0;
    mBody.width = DEFAULT_SIZE;
    mBody.height = DEFAULT_SIZE;
}

void Entity::update(float deltaTime)
{
    frameReset();

    mPosition.x += mMovement.x * mSpeed * deltaTime;
    mPosition.y += mMovement.y * mSpeed * deltaTime;

    mBody.x = mPosition.x; 
    mBody.y = mPosition.y;
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