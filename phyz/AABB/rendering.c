#include <stdio.h>
#include <raylib.h>
#include <math.h>

#include "game.h"
#include "utils.h"
#include "rendering.h"

void DrawShape(Shape shape);

void RenderGame(const game_t *game){
    for(int i = 0; i < game->shapes->size; i++){
        DrawShape(game->shapes[i].elements->extra.shape);
    }
}

void DrawShape(Shape shape){
    printf("turtles\n");
        DrawTriangle(shape.vertecies[0].elements->extra.vertex,
                shape.vertecies[1].elements->extra.vertex,
                shape.vertecies[2].elements->extra.vertex, RED);
}
