#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 800
#define DISTANCE_BETWEEN_LINES 80
#define GRID_SUBDIVISIONS 4
typedef struct {
    Camera2D camera;
    Font system_font;
} game_t;

typedef void (*func_ptr)(game_t *) ;

#endif
