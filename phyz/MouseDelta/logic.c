#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "logic.h"

block_t UpdateBlock(block_t block);
block_t PositionCap(block_t block);
static float frame_time = 0;

void RunGame(game_t *game){
    frame_time += GetFrameTime();
    bool do_the_thing = true;
    Vector2 mouse_position = GetMousePosition();
    //Vector2 position_buffer = game->block.position;
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        game->block.position = mouse_position;
        game->block.rect.x = game->block.position.x - game->block.size.x/2;
        game->block.rect.y = game->block.position.y - game->block.size.y/2;
        if (frame_time >= .01){
            game->block.velocity = GetMouseDelta();
            frame_time = 0.0001;
        }
        do_the_thing = false;
    }
    if (do_the_thing){
        game->block = UpdateBlock(game->block);
    }
    //printf("%lf, %lf",game->block.velocity.x,game->block.velocity.y);
}

block_t UpdateBlock(block_t block){
    static int collisions = 0;
    if (block.position.x - block.size.x/2 < 0 || block.position.x + block.size.x/2 > SCREEN_WIDTH){
        block.velocity.x *= -1*block.e_COR;
        collisions++;
    }
    if(block.position.y - block.size.y/2< 0 || block.position.y + block.size.y/2 > SCREEN_HEIGHT){
        block.velocity.y *= -1*block.e_COR;
        collisions++;
    }
    block = PositionCap(block);
    block.velocity.y += block.acceleration.y;
    block.velocity.x += block.acceleration.x;

    block.position.x += block.velocity.x;
    block.position.y += block.velocity.y;

    block.rect.x = block.position.x - block.size.x/2;
    block.rect.y = block.position.y - block.size.y/2;

    //printf("vx = %lf vy = %lf\n",block.velocity.x,block.velocity.y);
    return block;
}

block_t PositionCap(block_t block){
    if (block.position.x - block.size.x/2 < 0){
        block.position.x = block.size.x/2;
    }
    else if (block.position.x + block.size.x/2 > SCREEN_WIDTH) {
        block.position.x = SCREEN_WIDTH - block.size.x/2;
    }

    if(block.position.y - block.size.y/2< 0){
        block.position.y = block.size.y/2;
        block.acceleration.x = 0;
    }
    else if (block.position.y + block.size.y/2 > SCREEN_HEIGHT) {
        block.position.y = SCREEN_HEIGHT - block.size.y/2;
        if(block.velocity.x > 0){
            block.acceleration.x = -.07;
            if(block.velocity.x < .07){
                block.acceleration.x = -1*block.velocity.x;
            }
        }
        else if(block.velocity.x < 0){
            block.acceleration.x = .07;
            if(block.velocity.x > -.07){
                block.acceleration.x = -1*block.velocity.x;
            }
        }
        else{
            block.acceleration.x = 0;
        }
    }
    else{
        block.acceleration.x = 0;
    }
    return block;
}

