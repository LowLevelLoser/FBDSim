#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <raylib.h>

#include "game.h"
#include "rendering.h"

void RenderObjects(const Objects object);

void RenderGame(const game_t *game){
    for(size_t i = 0; i < game->object_array->size; ++i){
        //RenderObjects(game->object_array->objects[i]);
        RenderObjects(game->object_array->objects[i]);
    }
}

void RenderObjects(const Objects object){
    if(object.type == BALL){
        DrawCircleV(object.ball.center, object.ball.radius, GRAY);
        if(object.u_components.selected == true){
            DrawCircleLinesV(object.ball.center, object.ball.radius, RED);
        }
    }
    else if(object.type == BLOCK){
        DrawRectangleRec(object.block.rect, GRAY);
        if(object.u_components.selected == true){
            DrawRectangleLinesEx(object.block.rect,5,RED);
        }
    }
}


