#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct{
    Vector2 size;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float e_COR;
    Rectangle rect;
} block_t;

typedef struct {
    block_t block;
} game_t;

#endif
