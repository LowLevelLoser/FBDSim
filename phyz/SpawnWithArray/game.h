#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

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

typedef struct{
    Rectangle rect;
} block2_t;

typedef struct{
    float radius;
    float I_coefficent;
    Vector2 center;
} ball_t;

typedef struct{
    universal_components u_components;
    enum Type type;
    size_t size_of_type;
    void* extra_data;
} Objects;

typedef struct{
    Objects* objects;
    size_t size;
    size_t capacity;
} ObjectsArray;

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
    bool terminate;
    block_list_t* block_list;
    ObjectsArray* object_array;
} game_t;

#endif
