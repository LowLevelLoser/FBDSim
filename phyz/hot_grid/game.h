#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 800
#define MAX_BUILDINGS 100


typedef struct {
    Camera2D camera;
} game_t;

typedef void (*func_ptr)(game_t *) ;

#endif
