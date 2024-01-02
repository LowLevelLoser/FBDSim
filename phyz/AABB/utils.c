#include <raylib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "game.h"
#include "utils.h"

void InitArrayList(ArrayList* list);
void AddToObjectArray(ArrayList* list, ArrListElement element);
void SetElementInList(ArrayList* list, ArrListElement element, size_t index);
void RemoveFromArrayList(ArrayList* list, size_t index);
void FreeArrayList(ArrayList *list);
void Cleanup_Element(ArrListElement element);

void InitGame(game_t* game){
    game->shape_mode = false;
}

//=======================================================================
// Array List Implementation

#define INITIAL_CAPACITY 4

void InitArrayList(ArrayList* array){
    printf("1\n");
    array->elements = calloc(INITIAL_CAPACITY, sizeof(ArrListElement));
    if(array->elements == NULL){
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("2\n");
    array->capacity = INITIAL_CAPACITY;
    array->size = 0;
}

void AddToArrayList(ArrayList* array, ArrListElement element){
    if (array->size == array->capacity) {
        // If the elements is full, double its capacity
        array->capacity *= 2;
        array->elements = (ArrListElement*)realloc(array->elements, array->capacity * sizeof(ArrListElement));
        if (array->elements == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    array->elements[array->size] = element;
    array->size++;
}

void SetElementInList(ArrayList* array, ArrListElement element, size_t index){
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    array->elements[index] = element;
}

void RemoveFromArrayList(ArrayList* array, size_t index) {
    if (index >= array->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    Cleanup_Element(array->elements[index]);
    // Shift elements after the removed one
    for (size_t i = index; i < array->size - 1; i++) {
        array->elements[i] = array->elements[i + 1];
    }

    // Decrease the size of the ArrayList
    array->size--;

    // If the size is significantly smaller than the capacity, shrink the elements
    if (array->size > 0 && array->size < array->capacity / 2) {
        array->capacity /= 2;
        array->elements = (ArrListElement*)realloc(array->elements, array->capacity * sizeof(ArrListElement));
        if (array->elements == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void FreeArrayList(ArrayList *array) {
    for (int i = 0; i < array->size; i++) {
        RemoveFromArrayList(array, 0);
    }
    array->size = 0;
    array->capacity = 0;
    free(array);
}

// cleanup functions
void Cleanup_Element(ArrListElement element){
    //ArrListElement* element = (ArrListElement*)ptr;
    switch(element.type){
        case VECTOR2:
            // do nothing;
            break;
        case SHAPE:
            element.extra.shape.cleanup(&element.extra.shape);
            break;
    }
}

void Cleanup_Shape(void* ptr){
    FreeArrayList((ArrayList*)ptr);
    free(ptr);
}

Shape InitShape(){
    ArrayList vertecies;
    InitArrayList(&vertecies);
    Shape ret_shape;// = malloc(sizeof(Shape));
    //Shape shape = {
    ret_shape.cleanup = &Cleanup_Shape;
    ret_shape.vertecies = &vertecies;
    ret_shape.color = RED;
    //};
    printf("debugs\n");
    return ret_shape;
}

