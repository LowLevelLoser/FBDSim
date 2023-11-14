#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

#include "game.h"
#include "rendering.h"

void RenderRectangles(const block_t* block);

void RenderGame(const game_t *game){
    block_t* current_block = game->block_list->head;
    while (current_block != NULL){
        RenderRectangles(current_block);
        current_block = current_block->previous;
    }
}

void RenderRectangles(const block_t* block){
    DrawRectangleRec(block->rect, GRAY);
    if(block->selected == true){
        DrawRectangleLinesEx(block->rect,5,RED);
    }
}
