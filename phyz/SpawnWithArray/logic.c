#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "logic.h"
#include "utils.h"

universal_components UpdateObject(universal_components r_component);
universal_components PositionCap(universal_components r_component);
Objects* SelectedBlock(Vector2 mouse_position, ObjectsArray* object_array, size_t* return_index);
static float frame_time = 0;

void* UpdateObjectList(void* game_ptr){
    game_t* game = (game_t*)game_ptr;
    //block_t* current_block = game->object_array->head; //TODO: use threads to update blocks
    ObjectsArray* object_array = game->object_array;
    while (game->terminate == false){
        for(size_t i = 0; i < object_array->size; i++){
            if(object_array->objects[i].extra_data == NULL || object_array->objects[i].u_components.selected == true){
                continue;
            }
            if (object_array->objects[i].type == BALL) {
                ball_t* ball = (ball_t *)object_array->objects[i].extra_data;
                object_array->objects[i].u_components = UpdateObject(object_array->objects[i].u_components);
                ball->center.x = object_array->objects[i].u_components.position.x;
                ball->center.y = object_array->objects[i].u_components.position.y;
                ball->radius = object_array->objects[i].u_components.bounding_box.width/2;
            }
            else if (object_array->objects[i].type == BLOCK) {
                block2_t* block = (block2_t *)object_array->objects[i].extra_data;
                object_array->objects[i].u_components = UpdateObject(object_array->objects[i].u_components);
                block->rect = object_array->objects[i].u_components.bounding_box;
            }
        }
        WaitTime(1.0/120.0);
    }
    return NULL;
}

void RunGame(game_t *game){
    frame_time += GetFrameTime();
    static Objects* selected_object = NULL;
    static size_t selected_object_index;
    static bool update_selected_block = true;
    Vector2 mouse_position = GetMousePosition();
    if(update_selected_block){
        selected_object = SelectedBlock(mouse_position, game->object_array, &selected_object_index);
    }
    if(IsKeyPressed(KEY_B)){
        printf("B click\n");
        Objects element;
        element.u_components = DefaultUniversalComponents();
        element.type = BALL;
        element.size_of_type = sizeof(ball_t);
        element.extra_data = BallPointer(DefaultBallValues(element.u_components));
        AddToObjectArray(game->object_array, element);
        printf("B click finished\n");
    }
    if(IsKeyPressed(KEY_A)){
        printf("A click\n");
        Objects element;
        element.u_components = DefaultUniversalComponents();
        element.type = BLOCK;
        element.size_of_type = sizeof(block2_t);
        element.extra_data = BlockPointer(DefaultBlockValues2(element.u_components));

        //printf("%lf, %lf\n", (*(block2_t*)element.extra_data).rect.x, (*(block2_t*)element.extra_data).rect.y);
        AddToObjectArray(game->object_array, element);
        printf("A click finished\n");
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        printf("middle pressed\n");
        if(selected_object != NULL){
            printf("before\n");
            //RemoveFromList(game->object_array, selected_object);
            printf("%d\n", (int)selected_object_index);
            RemoveFromArrayList(game->object_array, selected_object_index);
            printf("after\n");
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        //if(selected_object != NULL && selected_object->type == BALL)printf("%lf,\n", (*(ball_t*)selected_object->extra_data).radius);
        update_selected_block = false;
        if(selected_object != NULL){
            selected_object->u_components.position = mouse_position;
            //block2_t* r_component = selected_object->extra_data;
            selected_object->u_components.bounding_box.x =
                selected_object->u_components.position.x - selected_object->u_components.bounding_box.width/2;
            selected_object->u_components.bounding_box.y =
                selected_object->u_components.position.y - selected_object->u_components.bounding_box.height/2;
            if (selected_object->type == BALL) {
                (*(ball_t*)selected_object->extra_data).center = mouse_position;
            }
            else if (selected_object->type == BLOCK) {
                (*(block2_t*)selected_object->extra_data).rect = selected_object->u_components.bounding_box;
            }
        }
        if (frame_time >= .01 && selected_object != NULL){
            selected_object->u_components.velocity.x =
                (selected_object->u_components.position.x - selected_object->u_components.position_buffer.x)/(frame_time*120);
            selected_object->u_components.velocity.y =
                (selected_object->u_components.position.y - selected_object->u_components.position_buffer.y)/(frame_time*120);

            selected_object->u_components.position_buffer.x = selected_object->u_components.position.x;
            selected_object->u_components.position_buffer.y = selected_object->u_components.position.y;
            frame_time = 0.0001;
        }
    }
    else {
        if(selected_object != NULL){
            selected_object->u_components.selected = false;
        }
        update_selected_block = true;
    }
}

Objects* SelectedBlock(Vector2 mouse_position, ObjectsArray* object_array, size_t* return_index){
    for (size_t i = 0; i < object_array->size; ++i){
        if(object_array->objects[i].type == BLOCK){
            block2_t block = *(block2_t *)object_array->objects[i].extra_data;
            if(CheckCollisionPointRec(mouse_position, block.rect)){
                object_array->objects[i].u_components.selected = true;
                *return_index = i;
                return &object_array->objects[i];
            }
            else{
                object_array->objects[i].u_components.selected = false;
            }
        }
        else if(object_array->objects[i].type == BALL){
            ball_t ball = *(ball_t *)object_array->objects[i].extra_data;
            if(CheckCollisionPointCircle(mouse_position, ball.center, ball.radius)){
                object_array->objects[i].u_components.selected = true;
                *return_index = i;
                return &object_array->objects[i];
            }
            else{
                object_array->objects[i].u_components.selected = false;
            }
        }
    }
    return NULL;
    //return selected_object;
}

universal_components UpdateObject(universal_components u_component){
    universal_components r_component = u_component;
    if (r_component.position.x - r_component.bounding_box.width/2 < 0 ||
        r_component.position.x + r_component.bounding_box.height/2 > SCREEN_WIDTH){
        r_component.velocity.x *= -1*r_component.e_COR;
    }
    if(r_component.position.y - r_component.bounding_box.height/2 < 0 ||
            r_component.position.y + r_component.bounding_box.height/2 > SCREEN_HEIGHT){
        r_component.velocity.y *= -1*r_component.e_COR;
    }
    r_component = PositionCap(r_component);
    r_component.velocity.y += r_component.acceleration.y;
    r_component.velocity.x += r_component.acceleration.x;

    r_component.position.x += r_component.velocity.x;
    r_component.position.y += r_component.velocity.y;

    r_component.bounding_box.x = r_component.position.x - r_component.bounding_box.width/2;
    r_component.bounding_box.y = r_component.position.y - r_component.bounding_box.height/2;
    return r_component;
}

universal_components PositionCap(universal_components u_component){
    universal_components r_component = u_component;
    if (r_component.position.x - r_component.bounding_box.width/2 < 0){
        r_component.position.x = r_component.bounding_box.width/2;
    }
    else if (r_component.position.x + r_component.bounding_box.width/2 > SCREEN_WIDTH) {
        r_component.position.x = SCREEN_WIDTH - r_component.bounding_box.width/2;
    }

    if(r_component.position.y - r_component.bounding_box.height/2< 0){
        r_component.position.y = r_component.bounding_box.height/2;
        r_component.acceleration.x = 0;
    }
    else if (r_component.position.y + r_component.bounding_box.height/2 > SCREEN_HEIGHT) {
        r_component.position.y = SCREEN_HEIGHT - r_component.bounding_box.height/2;
        if(r_component.velocity.x > 0){
            r_component.acceleration.x = -.07;
            if(r_component.velocity.x < .07){
                r_component.velocity.x = 0;
            }
        }
        else if(r_component.velocity.x < 0){
            r_component.acceleration.x = .07;
            if(r_component.velocity.x > -.07){
                r_component.velocity.x = 0;
            }
        }
        else{
            r_component.acceleration.x = 0;
        }
    }
    else{
        r_component.acceleration.x = 0;
    }
    return r_component;
}
