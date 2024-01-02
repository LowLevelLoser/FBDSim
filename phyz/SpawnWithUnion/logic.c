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

void* UpdateObjectList(void* game_ptr){
    game_t* game = (game_t*)game_ptr;
    //block_t* current_block = game->object_array->head; //TODO: use threads to update blocks
    ObjectsArray* object_array = game->object_array;
    while (game->terminate == false){
        for(size_t i = 0; i < object_array->size; i++){
            if(object_array->objects[i].u_components.selected == true){
                continue;
            }
            if (object_array->objects[i].type == BALL) {
                object_array->objects[i].u_components = UpdateObject(object_array->objects[i].u_components);
                //====================================
                object_array->objects[i].ball.center = object_array->objects[i].u_components.position;
                object_array->objects[i].ball.radius = object_array->objects[i].u_components.bounding_box.width/2;
            }
            else if (object_array->objects[i].type == BLOCK) {
                object_array->objects[i].u_components = UpdateObject(object_array->objects[i].u_components);
                object_array->objects[i].block.rect = object_array->objects[i].u_components.bounding_box;
            }
        }
        WaitTime(1.0/120.0);
    }
    return NULL;
}

void RunGame(game_t *game){
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
        element.ball = DefaultBallValues(element.u_components);
        AddToObjectArray(game->object_array, element);
        printf("B click finished\n");
    }

    if(IsKeyPressed(KEY_A)){
        printf("A click\n");
        Objects element;
        element.u_components = DefaultUniversalComponents();
        element.type = BLOCK;
        element.block = DefaultBlockValues(element.u_components);
        AddToObjectArray(game->object_array, element);
        printf("A click finished\n");
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        printf("middle pressed\n");
        if(selected_object != NULL){
            printf("before\n");
            printf("%d\n", (int)selected_object_index);
            RemoveFromArrayList(game->object_array, selected_object_index);
            printf("after\n");
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        update_selected_block = false;
        if(selected_object != NULL){
            selected_object->u_components.position = mouse_position;
            selected_object->u_components.bounding_box.x =
                selected_object->u_components.position.x - selected_object->u_components.bounding_box.width/2;
            selected_object->u_components.bounding_box.y =
                selected_object->u_components.position.y - selected_object->u_components.bounding_box.height/2;
            if (selected_object->type == BALL) {
                selected_object->ball.center = mouse_position;
            }
            else if (selected_object->type == BLOCK) {
                selected_object->block.rect = selected_object->u_components.bounding_box;
            }
            selected_object->u_components.velocity = GetMouseDelta();
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
            if(CheckCollisionPointRec(mouse_position, object_array->objects[i].block.rect)){
                object_array->objects[i].u_components.selected = true;
                *return_index = i;
                return &object_array->objects[i];
            }
            else{
                object_array->objects[i].u_components.selected = false;
            }
        }
        else if(object_array->objects[i].type == BALL){
            if(CheckCollisionPointCircle(mouse_position, object_array->objects[i].ball.center, object_array->objects[i].ball.radius)){
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
