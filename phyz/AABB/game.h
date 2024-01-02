#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <stdlib.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 800

//struct Shape;
//typedef struct Shape Shape;
struct ArrayList;
typedef struct ArrayList ArrayList;
typedef void (*cleanup_func) (void *);

typedef struct{
    cleanup_func cleanup;
    ArrayList* vertecies;
    Color color;
} Shape;

union Extra{
    Vector2 vertex;
    Shape shape;
};

enum Type{
    VECTOR2,
    SHAPE
};

typedef struct{
    //cleanup_func cleanup;
    enum Type type;
    union Extra extra;
} ArrListElement;

struct ArrayList{
    ArrListElement* elements;
    size_t size;
    size_t capacity;
};


//typedef struct Node{
//    struct Node* previous;
//    struct Node* next;
//} node_t;
//
//typedef struct{
//    int size;
//    node_t* head;
//} linked_list_t;

typedef struct {
    ArrayList* shapes;
    bool shape_mode;
} game_t;

typedef void (*func_ptr)(game_t *) ;

#endif
