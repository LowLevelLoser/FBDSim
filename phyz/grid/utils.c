#include <raylib.h>
#include <string.h>

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
}

Vector2 ScreenToWorldVec(const game_t* game, Vector2 vec){
    return VECTOR2_SUB(game->camera.target,
            VECTOR2_SCALAR_DIV(
                VECTOR2_SUB(game->camera.offset, vec), game->camera.zoom));
}

Vector2 WorldToScreenVec(const game_t* game, Vector2 vec){
    return VECTOR2_SUB(game->camera.offset,
            VECTOR2_SCALAR_MUL(
                VECTOR2_SUB(game->camera.target, vec), game->camera.zoom));
}
