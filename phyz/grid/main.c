#include <raylib.h>
#include <string.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "utils.h"


int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "window");
    //InitAudioDevice();
    SetTargetFPS(60);

    game_t game;

    InitGame(&game);

    while(!WindowShouldClose()){
        RunGame(&game);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderGame(&game);
        EndDrawing();
    }

    //StopMusicStream(game.music);

    //CloseAudioDevice();

    CloseWindow();

    return 0;
}
