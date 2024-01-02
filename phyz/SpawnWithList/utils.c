#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "utils.h"

void DefaultBlockValues(block_t* block){
    //block_t block;
    Vector2 mouse_position = GetMousePosition();
    block->rect.width = 40;
    block->rect.height = 40;
    block->size.x = block->rect.width;
    block->size.y = block->rect.height;
    block->position.x = mouse_position.x;
    block->position.y = mouse_position.y;
    block->rect.x = block->position.x - block->size.x/2;
    block->rect.y = block->position.y - block->size.y/2;
    block->acceleration.y = .17;
    block->acceleration.x = 0;
    block->mass = 1;
    block->e_COR = .7;
    block->selected = false;
}

block_list_t* CreateBlockList(){
    block_list_t* new_block_list = (block_list_t*)malloc(sizeof(block_list_t));
    new_block_list->size = 0;
    new_block_list->head = NULL;
    return new_block_list;
}

void AddBlock(block_list_t* block_list){
    block_t* new_block = (block_t*)malloc(sizeof(block_t));
    DefaultBlockValues(new_block);
    new_block->previous = block_list->head;
    if (new_block->previous != NULL) {
        new_block->previous->next = new_block;
    }
    new_block->next = NULL;
    block_list->head = new_block;
    block_list->size++;
}

void* RemoveFromList(block_list_t* block_list, block_t* block_to_remove){
    if(block_list->size == 0 || block_to_remove == NULL){
        printf("0\n");
        return NULL;
    }
    if(block_to_remove == block_list->head){
        printf("1\n");
        block_list->head = block_to_remove->previous;
    }
    else{
        printf("2\n");
        if (block_to_remove->next != NULL){
            block_to_remove->next->previous = block_to_remove->previous;
        }
    }
    if(block_to_remove->previous != NULL){
        printf("3\n");
        block_to_remove->previous->next = block_to_remove->next;
    }
    free(block_to_remove);
    block_list->size--;
    printf("successful removal\n");
    return 0;
}

void FreeList(block_list_t* block_list){
    block_t* current_block = block_list->head;
    while (current_block != NULL){
        block_t* previous_block = current_block->previous;
        RemoveFromList(block_list, current_block);
        current_block = previous_block;
    }
    free(block_list);
}
