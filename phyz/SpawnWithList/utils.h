#ifndef UTILS_H_
#define UTILS_H_

#include "game.h"

void DefaultBlockValues(block_t* block);
block_list_t* CreateBlockList();
void AddBlock(block_list_t* block_list);
void* RemoveFromList(block_list_t* block_list, block_t* block_to_remove);
void FreeList(block_list_t* block_list);

#endif // !UTILS_H_
