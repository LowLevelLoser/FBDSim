#include <stdio.h>
#include <raylib.h>
//#include <math.h>
//#include <float.h>

#include "game.h"
#include "utils.h"
#include "logic.h"

void RunGame(game_t *game){
    if(IsWindowResized()){
        game->camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    }

    static Vector2 mouse_buffer;
    static Vector2 drag_camera_target_buffer;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        game->camera.target =
            VECTOR2_ADD(drag_camera_target_buffer, VECTOR2_SCALAR_DIV(VECTOR2_SUB(mouse_buffer, GetMousePosition()), game->camera.zoom));
    }

    else {
        drag_camera_target_buffer = game->camera.target;
        mouse_buffer = GetMousePosition();
    }

    if (IsKeyDown(KEY_P)){
        printf("zoom: %lf\n", game->camera.zoom);
    }

    // Camera target follows game->player
    //game->camera.target = (Vector2){ game->player.x + 20, game->player.y + 20 };

    // Camera rotation controls
    //if (IsKeyDown(KEY_A)) game->camera.rotation--;
    //else if (IsKeyDown(KEY_S)) game->camera.rotation++;

    // Limit game->camera rotation to 80 degrees (-40 to 40)
    //if (game->camera.rotation > 40) game->camera.rotation = 40;
    //else if (game->camera.rotation < -40) game->camera.rotation = -40;

    // Camera zoom controls
    // We want when it zooms the place where the mouse is zooming stays the same relative to the screen
    Vector2 prescroll_target_vec = ScreenToWorldVec(game, GetMousePosition());
#if 0
    //linear zoom
    game->camera.zoom +=
        ((float)GetMouseWheelMove()*0.05f*game->camera.zoom);
#elif 1
    //exponential zoom
    game->camera.zoom *= 1.0f + GetMouseWheelMove() * 0.1f;

#endif

    Vector2 delta_pos = VECTOR2_SUB((ScreenToWorldVec(game, GetMousePosition())),prescroll_target_vec);
    game->camera.target = VECTOR2_SUB(game->camera.target, delta_pos);

    // zoom caps
    if (game->camera.zoom > 4000.0) {
        game->camera.zoom = 4000.0;
    }
    else if (game->camera.zoom < .00025) {
        game->camera.zoom = .00025;
    }

    if (IsKeyPressed(KEY_R)){
        InitGame(game);
    }
}
