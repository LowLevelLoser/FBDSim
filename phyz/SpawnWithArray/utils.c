#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "utils.h"

#define INITIAL_CAPACITY 4

size_t SizeOfType(enum Type type){
    switch(type){
        case BALL:
            return sizeof(ball_t);
            break;
        case BLOCK:
            return sizeof(block2_t);
            break;
    }
    return 0;
    fprintf(stderr, "err at Size Of Type\n");
}

void InitObjectArray(ObjectsArray* array){
    printf("1\n");
    array->objects = calloc(INITIAL_CAPACITY, sizeof(Objects));
    if(array->objects == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("2\n");
    array->capacity = INITIAL_CAPACITY;
    array->size = 0;
}

void AddToObjectArray(ObjectsArray* array, Objects element){
    if (array->size == array->capacity) {
        // If the objects is full, double its capacity
        array->capacity *= 2;
        array->objects = (Objects*)realloc(array->objects, array->capacity * sizeof(Objects));
        if (array->objects == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    array->objects[array->size] = element;
    array->size++;
}

void SetElementInList(ObjectsArray* array, Objects element, size_t index){
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    if(array->objects[index].extra_data != NULL){
        free(array->objects[index].extra_data);
    }

    array->objects[index] = element;
}

void RemoveFromArrayList(ObjectsArray* array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    if(array->objects[index].extra_data != NULL){
        free(array->objects[index].extra_data);
    }
    // Shift elements after the removed one
    for (size_t i = index; i < array->size - 1; i++) {
        array->objects[i] = array->objects[i + 1];
    }

    // Decrease the size of the ObjectsArray
    array->size--;

    // If the size is significantly smaller than the capacity, shrink the objects
    if (array->size > 0 && array->size < array->capacity / 2) {
        array->capacity /= 2;
        array->objects = (Objects*)realloc(array->objects, array->capacity * sizeof(Objects));
        if (array->objects == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void FreeArrayList(ObjectsArray *array) {
    for (size_t i = 0; i < array->size; ++i){
        free(array->objects[i].extra_data);
    }
    free(array->objects);
    array->size = 0;
    array->capacity = 0;
}

//====================================================================================================

universal_components DefaultUniversalComponents(){
    universal_components u_components;
    u_components.position.x = GetMouseX();
    u_components.position.y = GetMouseY();
    u_components.bounding_box.width = 40;
    u_components.bounding_box.height = 40;
    u_components.bounding_box.x = u_components.position.x - u_components.bounding_box.width/2;
    u_components.bounding_box.y = u_components.position.y - u_components.bounding_box.height/2;
    u_components.position_buffer.x = u_components.position.x;
    u_components.position_buffer.y = u_components.position.y;
    u_components.velocity.x = 0;
    u_components.velocity.y = 0;
    u_components.acceleration.x = 0;
    u_components.acceleration.y = .17;
    u_components.mass = 1;
    u_components.e_COR = .7;
    u_components.selected = false;
    u_components.net_force.x = 0;
    u_components.net_force.y = 0;

    return u_components;
}

ball_t DefaultBallValues(universal_components components){
    printf("%lf, %lf\n", components.bounding_box.x, components.bounding_box.y);
    ball_t ball = {
        .radius = components.bounding_box.width/2,
        .center.x = components.position.x,
        .center.y = components.position.y,
        .I_coefficent = 1,
    };

    return ball;
}

block2_t DefaultBlockValues2(universal_components components){
    printf("%lf, %lf\n", components.bounding_box.x, components.bounding_box.y);
    block2_t block = {
        .rect = components.bounding_box,
    };
    printf("%lf, %lf\n", block.rect.x, block.rect.y);
    return block;
}

void* BallPointer(ball_t ball){
    ball_t* ball_ptr = (ball_t *)malloc(sizeof(ball_t));
    *ball_ptr = ball;
    return (void*)ball_ptr;
}

void* BlockPointer(block2_t block){
    block2_t* block_ptr = malloc(sizeof(block2_t));
    *block_ptr = block;
    return (void*)block_ptr;
}
