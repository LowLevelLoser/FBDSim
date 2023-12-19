#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <dlfcn.h>

#include "game.h"
#include "logic.h"
#include "utils.h"
//#include "rendering.h"
//#include "logic.h"
#include "utils.h"


int main(){

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "window");
    //InitAudioDevice();
    SetTargetFPS(60);

    game_t game;

    //void* libhandle_utils = dlopen("./utils.so", RTLD_LAZY);
    void* libhandle_logic = dlopen("./logic.so", RTLD_LAZY);
    void* libhandle_rendering = dlopen("./rendering.so", RTLD_LAZY);

    if(libhandle_logic == NULL || libhandle_rendering == NULL){
        perror("dlopen");
        exit(1);
    }

    //func_ptr InitGame = dlsym(libhandle_utils, "InitGame");
    func_ptr RunGame = dlsym(libhandle_logic, "RunGame");
    func_ptr RenderGame = dlsym(libhandle_rendering, "RenderGame");

    if (RunGame == NULL || RenderGame == NULL) {
        fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
        dlclose(libhandle_logic);
        dlclose(libhandle_rendering);
        exit(1);
    }

    InitGame(&game);

    while(!WindowShouldClose()){
        RunGame(&game);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderGame(&game);
        EndDrawing();

        if(IsKeyPressed(KEY_H)){
            dlclose(libhandle_logic);
            dlclose(libhandle_rendering);

            //libhandle_utils = dlopen("./utils.so", RTLD_LAZY);
            libhandle_logic = dlopen("./logic.so", RTLD_LAZY);
            libhandle_rendering = dlopen("./rendering.so", RTLD_LAZY);

            if(libhandle_logic == NULL || libhandle_rendering == NULL){
                perror("dlopen");
                exit(1);
            }

            //InitGame = dlsym(libhandle_utils, "InitGame");
            RunGame = dlsym(libhandle_logic, "RunGame");
            RenderGame = dlsym(libhandle_rendering, "RenderGame");

            if (RunGame == NULL || RenderGame == NULL) {
                fprintf(stderr, "Failed to find symbol: %s\n", dlerror());
                //dlclose(libhandle_utils);
                dlclose(libhandle_logic);
                dlclose(libhandle_rendering);
                exit(1);
            }

        }
    }

    //dlclose(libhandle_utils);
    dlclose(libhandle_logic);
    dlclose(libhandle_rendering);
    //StopMusicStream(game.music);

    //CloseAudioDevice();

    CloseWindow();

    return 0;
}
