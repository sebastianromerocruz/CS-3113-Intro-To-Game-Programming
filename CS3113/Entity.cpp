#include "Entity.h"

Entity::Entity() : mBody { 0.0f, 0.0f, 0.0f, 0.0f }, mPosition { 0.0f, 0.0f }, mMovement { 0.0f, 0.0f } {}

Entity::Entity(Rectangle body, Vector2 position) : mBody {body}, mPosition {position}, mMovement { 0.0f, 0.0f } {}

Entity::~Entity() {};