#include "raylib.h"
#include "structs.h"
#include "InputChecks.h"
#include <stdbool.h>



Vector2 Movement_Checks()
{
	Vector2 MovementDirection = { 0, 0 };
	if (IsKeyDown(KEY_W)) { MovementDirection.y -= 4; }
	if (IsKeyDown(KEY_A)) { MovementDirection.x -= 4; }
	if (IsKeyDown(KEY_S)) { MovementDirection.y += 4; }
	if (IsKeyDown(KEY_D)) { MovementDirection.x += 4; }

	//TraceLog(5, TextFormat("%d", MovementDirection));
	
	return MovementDirection;
}

int ButtonChecks()
{
	int Input = 0;
	int KeyPressed = GetKeyPressed();
	if (KeyPressed == KEY_UP) { Input = 1; }
	if (KeyPressed == KEY_M) { Input = 2; }
	return Input;
}
