#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "logic.h"
#include "utils.h"

void UpdateBlock(block_t* block);
void PositionCap(block_t* block);
block_t* SelectedBlock(Vector2 mouse_position, block_list_t* block_list);
static float frame_time = 0;

void *UpdateBlockList(void* void_block_list){
    game_t* game = (game_t*)void_block_list;
    block_t* current_block = game->block_list->head; //TODO: use threads to update blocks
    while (game->terminate == false){
        while(current_block != NULL){
            if(current_block->selected == false){
                UpdateBlock(current_block);
            }
            current_block = current_block->previous;
        }
        if(current_block == NULL){
            current_block = game->block_list->head;
        }
        WaitTime(1.0/120.0);
    }
    //sleep
}

void RunGame(game_t *game){
    frame_time += GetFrameTime();
    static block_t* selected_block = NULL;
    static bool update_selected_block = true;
    Vector2 mouse_position = GetMousePosition();
    if(update_selected_block){
        selected_block = SelectedBlock(mouse_position, game->block_list);
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        printf("right click\n");
        AddBlock(game->block_list);
        printf("right click finished\n");
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        printf("middle pressed\n");
        if(selected_block != NULL){
            printf("before\n");
            RemoveFromList(game->block_list, selected_block);
            printf("after\n");
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        update_selected_block = false;
        if(selected_block != NULL){
            selected_block->position.x = mouse_position.x;
            selected_block->position.y = mouse_position.y;
            selected_block->rect.x = selected_block->position.x - selected_block->size.x/2;
            selected_block->rect.y = selected_block->position.y - selected_block->size.y/2;
        }
        if (frame_time >= .01 && selected_block != NULL){
            selected_block->velocity.x = (selected_block->position.x - selected_block->position_buffer.x)/(frame_time*120);
            selected_block->velocity.y = (selected_block->position.y - selected_block->position_buffer.y)/(frame_time*120);
            selected_block->position_buffer.x = selected_block->position.x;
            selected_block->position_buffer.y = selected_block->position.y;
            frame_time = 0.0001;
        }
    }
    else {
        if(selected_block != NULL){
            selected_block->selected = false;
        }
        update_selected_block = true;
    }
}

block_t* SelectedBlock(Vector2 mouse_position, block_list_t* block_list){
    block_t* current_block = block_list->head;
    block_t* selected_block = NULL;
    while (current_block != NULL){
        if (CheckCollisionPointRec(mouse_position, current_block->rect)) {
            selected_block = current_block;
            selected_block->selected = true;
        }
        else {
            current_block->selected = false;
        }
        current_block = current_block->previous;
    }
    return selected_block;
}

void UpdateBlock(block_t* block){
    if (block->position.x - block->size.x/2 < 0 || block->position.x + block->size.x/2 > SCREEN_WIDTH){
        block->velocity.x *= -1*block->e_COR;
    }
    if(block->position.y - block->size.y/2< 0 || block->position.y + block->size.y/2 > SCREEN_HEIGHT){
        block->velocity.y *= -1*block->e_COR;
    }
    PositionCap(block);
    block->velocity.y += block->acceleration.y;
    block->velocity.x += block->acceleration.x;

    block->position.x += block->velocity.x;
    block->position.y += block->velocity.y;

    block->rect.x = block->position.x - block->size.x/2;
    block->rect.y = block->position.y - block->size.y/2;
}

void PositionCap(block_t* block){
    if (block->position.x - block->size.x/2 < 0){
        block->position.x = block->size.x/2;
    }
    else if (block->position.x + block->size.x/2 > SCREEN_WIDTH) {
        block->position.x = SCREEN_WIDTH - block->size.x/2;
    }

    if(block->position.y - block->size.y/2< 0){
        block->position.y = block->size.y/2;
        block->acceleration.x = 0;
    }
    else if (block->position.y + block->size.y/2 > SCREEN_HEIGHT) {
        block->position.y = SCREEN_HEIGHT - block->size.y/2;
        if(block->velocity.x > 0){
            block->acceleration.x = -.07;
            if(block->velocity.x < .07){
                block->acceleration.x = -1*block->velocity.x;
            }
        }
        else if(block->velocity.x < 0){
            block->acceleration.x = .07;
            if(block->velocity.x > -.07){
                block->acceleration.x = block->velocity.x;
            }
        }
        else{
            block->acceleration.x = 0;
        }
    }
    else{
        block->acceleration.x = 0;
    }
}

