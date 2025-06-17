#include "Entity.h"

Entity::Entity() : mBody { 0.0f, 0.0f, 0.0f, 0.0f }, mPosition { 0.0f, 0.0f }, 
                   mMovement { 0.0f, 0.0f }, mScreenWidth {0}, mScreenHeight {0} {}

Entity::Entity(Rectangle body, Vector2 position) : mBody {body}, 
                                                   mPosition {position}, 
                                                   mMovement { 0.0f, 0.0f },
                                                   mScreenWidth {0}, 
                                                   mScreenHeight {0} {}

Entity::Entity(int screenWidth, int screenHeight) : mMovement { 0.0f, 0.0f }
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

Entity::Entity(int screenWidth, int screenHeight, int height, int width, const char* textureFilepath) : Entity { screenWidth, screenHeight }
{
    mTexture = LoadTexture(textureFilepath);
}

Entity::~Entity() 
{
    UnloadTexture(mTexture);
};

void Entity::frameReset()
{
    mBody.x = 0;
    mBody.y = 0;
    mBody.width = DEFAULT_SIZE;
    mBody.height = DEFAULT_SIZE;
}

void Entity::update()
{
    frameReset();

    mPosition.x += mMovement.x * DEFAULT_SPEED;
    mPosition.y += mMovement.y * DEFAULT_SPEED;

    mBody.x = mPosition.x; 
    mBody.y = mPosition.y;
}

void Entity::render()
{
    // Part of the texture to use for drawing (UV-coordinates)
    Rectangle textureRect = { 0.0f, 0.0f, (float) mTexture.width, (float) mTexture.height };

    // Screen rectangle where drawing part of texture
    Rectangle destinationRect = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mTexture.width),
        static_cast<float>(mTexture.height)
    };

    // Origin of TEXTURE
    Vector2 textureOrigin = { (float) mTexture.width / 2.0f, (float) mTexture.height / 2.0f };

    DrawTexturePro(mTexture, textureRect, destinationRect, textureOrigin, mAngle++, WHITE);

    // DrawTexture(mTexture, mPosition.x - mTexture.width / 2.0f, mPosition.y - mTexture.height / 2.0f, WHITE);
}