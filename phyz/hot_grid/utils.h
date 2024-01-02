#ifndef  UTILS_H_
#define UTILS_H_

#include "game.h"
// Macro for scalar multiplication
#define VECTOR2_SCALAR_MUL(v, k) \
    (Vector2){ (v).x * (k), (v).y * (k) }

#define VECTOR2_SCALAR_DIV(v, k) \
    (Vector2){ (v).x / (k), (v).y / (k) }
// Macro for vector addition
#define VECTOR2_ADD(v1, v2) \
    (Vector2){ (v1).x + (v2).x, (v1).y + (v2).y }

#define VECTOR2_SUB(v1, v2) \
    (Vector2){ (v1).x - (v2).x, (v1).y - (v2).y }

void InitGame(game_t* game);
Vector2 ScreenToWorldVec(const Camera2D camera, Vector2 vec);
Vector2 WorldToScreenVec(const Camera2D camera, Vector2 vec);
float RoundToPowerOfFour(float num);

#endif
