#include <raylib.h>

#include "game.h"
#include "rendering.h"

void RenderGame(const game_t *game){
    Vector2 pos;
    pos.x = game->block.rect.x;
    pos.y = game->block.rect.y;
    DrawRectangleV(pos, game->block.size, GRAY);
}

