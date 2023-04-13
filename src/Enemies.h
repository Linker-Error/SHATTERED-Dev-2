#include "raylib.h"
#include "structs.h"
#include <stdbool.h>


#ifndef ENEMIES
#define ENEMIES

void UpdateEnemy(struct Enemy * Enemy, int Tick, struct Map * Area, Vector2 PlayerPosition, int* PlayerHealth, bool PlayerAttacking, int PlayerFacing);

#endif