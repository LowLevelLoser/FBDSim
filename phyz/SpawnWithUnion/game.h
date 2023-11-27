#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
//could be useful if I don't want to put it in object
#define Extra_M union {block_t block; ball_t ball;};

enum Type{
    BALL,
    BLOCK,
};

typedef struct{
    Vector2* forces;
    size_t size;
    size_t capacity;
} ForcesArray;

typedef struct{
    Rectangle bounding_box;
    Vector2 position;
    Vector2 position_buffer;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
    float e_COR;
    bool selected;
    Vector2 net_force;
} universal_components;

typedef struct Block{
    Rectangle rect;
} block_t;

typedef struct{
    float radius;
    float I_coefficent;
    Vector2 center;
} ball_t;

typedef struct{
    universal_components u_components;
    enum Type type;
    //union extra;
    union {
        block_t block;
        ball_t ball;
    };
    size_t size_of_type;
} Objects;

typedef struct{
    Objects* objects;
    size_t size;
    size_t capacity;
} ObjectsArray;

typedef struct {
    bool terminate;
    ObjectsArray* object_array;
} game_t;

#endif
