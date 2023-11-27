#ifndef UTILS_H_
#define UTILS_H_

#include "game.h"
size_t SizeOfType(enum Type type);
void InitObjectArray(ObjectsArray* list);
void AddToObjectArray(ObjectsArray* list, Objects element);
void SetElementInList(ObjectsArray* list, Objects element, size_t index);
void RemoveFromArrayList(ObjectsArray* list, size_t index);
void FreeArrayList(ObjectsArray *list);
ball_t DefaultBallValues(universal_components components);
block_t DefaultBlockValues(universal_components components);
universal_components DefaultUniversalComponents();
#endif // !UTILS_H_
