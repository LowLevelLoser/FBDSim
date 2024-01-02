#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
//#include <math.h>
//#include <float.h>

#include "game.h"
#include "utils.h"
#include "logic.h"

ArrListElement current_shape;
void ShapeCreatorMode(game_t* game, ArrListElement ret_shape);

void RunGame(game_t *game){
    if(game->shape_mode == true){
        ShapeCreatorMode(game, current_shape);
    }
    if(IsKeyPressed(KEY_A)){
        game->shape_mode = true;
        //current_shape->extra.shape = InitShape();
        ArrayList vertecies;
        InitArrayList(&vertecies);
        printf("debs\n");
        current_shape.type = SHAPE;

        current_shape.extra.shape.cleanup = &Cleanup_Shape;
        current_shape.extra.shape.vertecies = &vertecies;
        current_shape.extra.shape.color = RED;
    }
}

void ShapeCreatorMode(game_t* game, ArrListElement ret_shape){
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        printf("ppp\n");
        ArrListElement vertex;
        vertex.extra.vertex = GetMousePosition();
        AddToArrayList(ret_shape.extra.shape.vertecies, vertex);
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        RemoveFromArrayList(ret_shape.extra.shape.vertecies, ret_shape.extra.shape.vertecies->size - 1);
    }
    if(IsKeyPressed(KEY_B)){
        printf("nanan\n");
        if(ret_shape.extra.shape.vertecies->size == 3){
            AddToArrayList(game->shapes, ret_shape);
        }
        game->shape_mode = false;
    }
}
