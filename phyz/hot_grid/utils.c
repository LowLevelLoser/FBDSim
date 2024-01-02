#include <raylib.h>
#include <string.h>
#include <math.h>

#include "game.h"
#include "utils.h"

void InitGame(game_t* game){
    //game->camera = {{0}};
    memset(&game->camera, 0, sizeof(game->camera));
    game->camera.target = (Vector2){0,0};
    //game->camera.target = (Vector2){ GetScreenWidth()/-2.0f, GetScreenHeight()/-2.0f };
    game->camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    //game->camera.offset = (Vector2){0,0};
    game->camera.rotation = 0.0f;
    game->camera.zoom = 1.0f;

    game->system_font = LoadFont("../../fonts/OpenSans-Bold.ttf");
}

Vector2 ScreenToWorldVec(const Camera2D camera, Vector2 vec){
    return VECTOR2_SUB(camera.target,
            VECTOR2_SCALAR_DIV(
                VECTOR2_SUB(camera.offset, vec), camera.zoom));
}

Vector2 WorldToScreenVec(const Camera2D camera, Vector2 vec){
    return VECTOR2_SUB(camera.offset,
            VECTOR2_SCALAR_MUL(
                VECTOR2_SUB(camera.target, vec), camera.zoom));
}

float RoundToPowerOfFour(float num){
    if(num <= 0){
        return 0;
    }
    //return powf(2, floorf(log2f(num)));
    return powf(4, floorf(log2f(num)/2));
}
