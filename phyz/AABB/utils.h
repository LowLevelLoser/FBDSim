#ifndef  UTILS_H_
#define UTILS_H_

#include "game.h"
void InitGame(game_t* game);
//ArrayList
void InitArrayList(ArrayList* list);
void AddToArrayList(ArrayList* list, ArrListElement element);
void SetElementInList(ArrayList* list, ArrListElement element, size_t index);
void RemoveFromArrayList(ArrayList* list, size_t index);
void FreeArrayList(ArrayList *list);
void Cleanup_Shape(void* ptr);
Shape InitShape();

#endif
