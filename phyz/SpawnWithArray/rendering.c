#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <raylib.h>

#include "game.h"
#include "rendering.h"

void RenderObjects(const Objects object);

void RenderGame(const game_t *game){
    for(size_t i = 0; i < game->object_array->size; ++i){
        RenderObjects(game->object_array->objects[i]);
    }
}

void RenderObjects(const Objects object){
    if(object.type == BALL){
        ball_t ball = *(ball_t *)object.extra_data;
        DrawCircleV(ball.center, ball.radius, GRAY);
        if(object.u_components.selected == true){
            DrawCircleLinesV(ball.center, ball.radius, RED);
        }
    }
    else if(object.type == BLOCK){
        block2_t block = *(block2_t *)object.extra_data;
        DrawRectangleRec(block.rect, GRAY);
        if(object.u_components.selected == true){
            DrawRectangleLinesEx(block.rect,5,RED);
        }
    }
}
