#include "cs3113.h"

void hello() { printf("Hello!\n"); }

void translate(Entity *player) 
{
    player->mBody.x = player->mPosition.x; 
    player->mBody.y = player->mPosition.y; 
}

void resetEntity(Entity *player)
{
    player->mBody.x = 0;
    player->mBody.y = 0;
    player->mBody.width = SIZE;
    player->mBody.height = SIZE;
}