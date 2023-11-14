#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

typedef struct Block{
    Vector2 size;
    Vector2 position;
    Vector2 position_buffer;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float e_COR;
    Rectangle rect;
    bool selected;
    struct Block* previous;
    struct Block* next;
} block_t;

typedef struct{
    int size;
    block_t* head;
} block_list_t;

typedef struct {
    block_t block;
    block_list_t* block_list;
} game_t;

#endif
