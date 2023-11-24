#include <raylib.h>
#include <pthread.h>
#include <stdio.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"
#include "utils.h"

int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window");
    //InitAudioDevice();
    SetTargetFPS(120);

    game_t game;

    game.block_list = CreateBlockList();
    pthread_t thread_id;
    if(pthread_create(&thread_id, NULL, UpdateBlockList,&game)) return 1;

    while(!WindowShouldClose()){
        RunGame(&game);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderGame(&game);
        EndDrawing();
    }
     game.terminate = true;

    //StopMusicStream(game.music);

    //CloseAudioDevice();
    if (pthread_join(thread_id, NULL) != 0) {
        printf("failed to hoin thread\n");
        //FreeList(game.block_list);
        //CloseWindow();
        return 2;
    }
    FreeList(game.block_list);
    CloseWindow();

    return 0;
}
