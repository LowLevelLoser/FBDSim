#include <raylib.h>

#include "game.h"
#include "utils.h"
#include "rendering.h"

void RenderGame(const game_t *game){
    ClearBackground(RAYWHITE);

    DrawLineEx( (Vector2){(float)GetScreenWidth(), GetScreenHeight()/2.0 - game->camera.target.y*game->camera.zoom},
            (Vector2){0, GetScreenHeight()/2.0 - game->camera.target.y*game->camera.zoom},
            4,
            DARKGRAY);

    DrawLineEx( (Vector2){(float)GetScreenWidth()/2.0 - game->camera.target.x*game->camera.zoom, GetScreenHeight()},
            (Vector2){(float)GetScreenWidth()/2.0 - game->camera.target.x*game->camera.zoom, 0},
            4,
            DARKGRAY);

    BeginMode2D(game->camera);
        Vector2 mouse_world_pos = ScreenToWorldVec(game, GetMousePosition());


        //DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
        DrawRectangle(-100, -100, 200, 200, RED);


        DrawLineV((Vector2){0,0},
                mouse_world_pos,
                BLUE);

        DrawLineV((Vector2){0,0},
                VECTOR2_SCALAR_DIV(VECTOR2_SUB(game->camera.offset,GetMousePosition()), (-1*game->camera.zoom)),
                RED);

        DrawLineV(game->camera.target,
                VECTOR2_ADD(VECTOR2_SCALAR_DIV(VECTOR2_SUB(game->camera.offset,GetMousePosition()), (-1*game->camera.zoom)), game->camera.target),
                PURPLE);

        DrawLineV((Vector2){0,0},
                game->camera.target,
                GREEN);

        Vector2 vec1 = (Vector2){-200,-100};
        Vector2 vec2 = (Vector2){100,200};

        //DrawLineV(vec1,
        //        vec2,
        //        DARKGRAY);
        //for (int i = 0; i < MAX_BUILDINGS; i++) DrawRectangleRec(game->buildings[i], game->buildColors[i]);

        //DrawRectangleRec(game->player, RED);

        //DrawLine((int)game->camera.target.x, - GetScreenHeight()*10, (int)game->camera.target.x, GetScreenHeight()*10, GREEN);
        //DrawLine(-GetScreenWidth()*10, (int)game->camera.target.y, GetScreenWidth()*10, (int)game->camera.target.y, GREEN);

    EndMode2D();


    DrawLine(0, GetScreenHeight()/2, GetScreenWidth(), GetScreenHeight()/2, RED);
    DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), RED);

    //DrawLine(GetScreenWidth()/2, GetScreenHeight()/2, GetMouseX(), GetMouseY(), DARKGRAY);
    DrawLineV((Vector2){GetScreenWidth()/2.0, GetScreenHeight()/2.0}, GetMousePosition(), PURPLE);

    DrawLineV(WorldToScreenVec(game, vec1),
            WorldToScreenVec(game, vec2),
            BLUE);
    //DrawText("SCREEN AREA", 640, 10, 20, RED);

    //DrawRectangle(0, 0, GetScreenWidth(), 5, RED);
    //DrawRectangle(0, 5, 5, GetScreenHeight() - 10, RED);
    //DrawRectangle(GetScreenWidth() - 5, 5, 5, GetScreenHeight() - 10, RED);
    //DrawRectangle(0, GetScreenHeight() - 5, GetScreenWidth(), 5, RED);

    //DrawRectangle( 10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
    //DrawRectangleLines( 10, 10, 250, 113, BLUE);

    //DrawText("Free 2d game->camera controls:", 20, 20, 10, BLACK);
    //DrawText("- Right/Left to move Offset", 40, 40, 10, DARKGRAY);
    //DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
    //DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
    //DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);
}

