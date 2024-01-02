#include <raylib.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

int main(){
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");
    //InitAudioDevice();
    SetTargetFPS(120);

    game_t game;
    game.block.rect.width = 40;
    game.block.rect.height = 40;
    game.block.rect.x = SCREEN_WIDTH/2.0;
    game.block.rect.y = SCREEN_HEIGHT/2.0;
    game.block.position.x = game.block.rect.x;
    game.block.position.y = game.block.rect.y;
    game.block.acceleration.y = .17;
    game.block.acceleration.x = 0;
    game.block.size.x = game.block.rect.width;
    game.block.size.y = game.block.rect.height;
    game.block.mass = 1;
    game.block.e_COR = .9;


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
