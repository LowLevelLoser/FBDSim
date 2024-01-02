#include <stdio.h>
#include <raylib.h>
#include <math.h>

#include "game.h"
#include "utils.h"
#include "rendering.h"

void GridRenderer(const game_t *game);
void WorldRenders(const game_t *game);
void ScreenRenders(const game_t *game);

void RenderGame(const game_t *game){
    //Grid has to be rendered under everything else
    GridRenderer(game);
    WorldRenders(game);
    ScreenRenders(game); //UI stuff etc.
}

void SubLineDrawer(Camera2D camera, Vector2 start_w, Vector2 end_w, float gaps){
    float traveler, length;
    Vector2 start_w_b = start_w;
    Vector2 end_w_b = end_w;
    Vector2 start = WorldToScreenVec(camera, start_w);
    Vector2 end = WorldToScreenVec(camera, end_w);
    traveler = start_w.y - fmodf(start_w.y, gaps) - gaps;
    length = end_w.y + gaps;

    while(traveler <= length){
        start_w.y = traveler;
        end_w.y = traveler;
        start = WorldToScreenVec(camera, start_w);
        end = WorldToScreenVec(camera, end_w);
        DrawLineV(start, end, LIGHTGRAY);
        traveler += gaps/4;
    }

    start_w = start_w_b;
    end_w = end_w_b;
    start = WorldToScreenVec(camera, start_w);
    end = WorldToScreenVec(camera, end_w);
    traveler = start_w.x - fmodf(start_w.x, gaps) - gaps;
    length = end_w.x + gaps;

    while(traveler <= length){
        start_w.x = traveler;
        end_w.x = traveler;
        start = WorldToScreenVec(camera, start_w);
        end = WorldToScreenVec(camera, end_w);
        DrawLineV(start, end, LIGHTGRAY);
        traveler += gaps/4;
    }
}

void LineDrawer(Camera2D camera, Vector2 start_w, Vector2 end_w, float gaps, Font font){
    //TODO decouple line drawing and numbers
    float traveler, length;
    Vector2 start_w_b = start_w;
    Vector2 end_w_b = end_w;
    Vector2 start = WorldToScreenVec(camera, start_w);
    Vector2 end = WorldToScreenVec(camera, end_w);
    traveler = start_w.y - fmodf(start_w.y, gaps) - gaps;
    length = end_w.y + gaps;

    while(traveler <= length){
        start_w.y = traveler;
        end_w.y = traveler;
        start = WorldToScreenVec(camera, start_w);
        end = WorldToScreenVec(camera, end_w);
        DrawLineEx(start, end, 2, GRAY);
        traveler += gaps;
    }

    start_w = start_w_b;
    end_w = end_w_b;
    start = WorldToScreenVec(camera, start_w);
    end = WorldToScreenVec(camera, end_w);
    traveler = start_w.x - fmodf(start_w.x, gaps) - gaps;
    length = end_w.x + gaps;

    while(traveler <= length){
        start_w.x = traveler;
        end_w.x = traveler;
        start = WorldToScreenVec(camera, start_w);
        end = WorldToScreenVec(camera, end_w);
        DrawLineEx(start, end, 2, GRAY);
        traveler += gaps;
    }
}

void DrawGridText(Camera2D camera, Vector2 start_w, Vector2 end_w, float gaps, Font font){
    //TODO decouple line drawing and numbers
    float traveler, length;
    Vector2 start_w_b = start_w;
    Vector2 end_w_b = end_w;
    Vector2 start = WorldToScreenVec(camera, start_w);
    traveler = start_w.y - fmodf(start_w.y, gaps) - gaps;
    length = end_w.y + gaps;
    Vector2 origin = WorldToScreenVec(camera, (Vector2){0,0});

    while(traveler <= length){
        float x;
        start_w.y = traveler;
        start = WorldToScreenVec(camera, start_w);

        char measurement[12];
        snprintf(measurement, 12, "%.2em", (-1*start_w.y/DISTANCE_BETWEEN_LINES));
        Vector2 text = MeasureTextEx(font, measurement, 17, 1);
        if(origin.x+text.x > (float)GetScreenWidth()){
            x = GetScreenWidth()-text.x-4;
        }
        else if (origin.x < 0) {
            x = 0;
        }
        else{
            x = origin.x;
        }
        if(start_w.y !=0 ){
            DrawTextEx(font, measurement, (Vector2){x + 4, start.y}, 17, 1, BLACK);
            //DrawRectangleV((Vector2){x, start.y}, (Vector2){8,8} , RED);
        }
        traveler += gaps;
    }

    start_w = start_w_b;
    end_w = end_w_b;
    start = WorldToScreenVec(camera, start_w);
    traveler = start_w.x - fmodf(start_w.x, gaps) - gaps;
    length = end_w.x + gaps;

    while(traveler <= length){
        float y;
        start_w.x = traveler;
        start = WorldToScreenVec(camera, start_w);

        char measurement[12];
        snprintf(measurement, 12, "%.2em", (start_w.x/DISTANCE_BETWEEN_LINES));
        Vector2 text = MeasureTextEx(font, measurement, 17, 1);

        if(origin.y+text.y > (float)GetScreenHeight()){
            y = GetScreenHeight()-text.y;
        }
        else if (origin.y < 0) {
            y = 0;
        }
        else{
            y = origin.y;
        }
        if(start_w.x != 0){
            DrawTextEx(font, measurement, (Vector2){start.x, y}, 17, 1, BLACK);
        }
        traveler += gaps;
    }
    DrawTextEx(font, "0m", WorldToScreenVec(camera, (Vector2){4/camera.zoom, 0}), 17, 1, BLACK);
}

void GridRenderer(const game_t *game){
    Vector2 top_left_point = ScreenToWorldVec(game->camera, (Vector2){0,0});
    Vector2 bottom_right_point = ScreenToWorldVec(game->camera, (Vector2){GetScreenWidth(),GetScreenHeight()});
    float gaps = DISTANCE_BETWEEN_LINES/RoundToPowerOfFour(game->camera.zoom);

    SubLineDrawer(game->camera, top_left_point,bottom_right_point, gaps);
    LineDrawer(game->camera, top_left_point, bottom_right_point, gaps, game->system_font);

    DrawLineEx((Vector2){(float)GetScreenWidth()/2.0 - game->camera.target.x*game->camera.zoom, GetScreenHeight()},
            (Vector2){(float)GetScreenWidth()/2.0 - game->camera.target.x*game->camera.zoom, 0},
            4,
            DARKGRAY);

    DrawLineEx((Vector2){(float)GetScreenWidth(), GetScreenHeight()/2.0 - game->camera.target.y*game->camera.zoom},
            (Vector2){0, GetScreenHeight()/2.0 - game->camera.target.y*game->camera.zoom},
            4,
            DARKGRAY);

}

void WorldRenders(const game_t *game){
    BeginMode2D(game->camera);

    Vector2 mouse_world_pos = ScreenToWorldVec(game->camera, GetMousePosition());

    DrawRectangle(50, 50, 200, 200, YELLOW);

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

    EndMode2D();
}

void ScreenRenders(const game_t *game){
    Vector2 vec1 = (Vector2){-200,-100};
    Vector2 vec2 = (Vector2){100,200};

    DrawLineV((Vector2){GetScreenWidth()/2.0, GetScreenHeight()/2.0}, GetMousePosition(), PURPLE);

    DrawLineV(WorldToScreenVec(game->camera, vec1),
            WorldToScreenVec(game->camera, vec2),
            BLUE);

    Vector2 top_left_point = ScreenToWorldVec(game->camera, (Vector2){0,0});
    Vector2 bottom_right_point = ScreenToWorldVec(game->camera, (Vector2){GetScreenWidth(),GetScreenHeight()});
    float gaps = DISTANCE_BETWEEN_LINES/RoundToPowerOfFour(game->camera.zoom);
    DrawGridText(game->camera, top_left_point, bottom_right_point, gaps, game->system_font);
}
