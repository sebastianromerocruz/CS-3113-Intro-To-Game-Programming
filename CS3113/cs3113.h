#ifndef CS3113_H
#define CS3113_H

#include "Entity.h"
#include <stdio.h>

enum AppStatus { TERMINATED, RUNNING };
const int SIZE = 40;

void hello();
void resetEntity(Entity *player);
void translate(Entity *player);

#endif // CS3113_H