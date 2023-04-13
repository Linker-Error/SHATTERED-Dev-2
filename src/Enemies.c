#include "raylib.h"
#include <stdbool.h>
#include "Enemies.h"
#include "structs.h"
#include "general.h"
#include "raymath.h"

void UpdateEnemy(struct Enemy* Enemy, int Tick, struct Map* Area, Vector2 PlayerPosition, int *PlayerHealth, bool PlayerAttacking, int PlayerFacing)
{
	bool moving = false;
	Vector2 EnemyMovement = { 0, 0 };
	if (PlayerAttacking)
	{
		if ((((PlayerFacing == 0 && Enemy->EnemyPosition.y > PlayerPosition.y) || (PlayerFacing == 3 && Enemy->EnemyPosition.y < PlayerPosition.y))
			||
			((PlayerFacing == 1 && Enemy->EnemyPosition.x < PlayerPosition.x) || (PlayerFacing == 2 && Enemy->EnemyPosition.x > PlayerPosition.x)))
			&&
			(sqrt(
				(abs(PlayerPosition.x - Enemy->EnemyPosition.x) * abs(PlayerPosition.x - Enemy->EnemyPosition.x)) +
				(abs(PlayerPosition.y - Enemy->EnemyPosition.y) * abs(PlayerPosition.y - Enemy->EnemyPosition.y))) <= 40))
		{
			Enemy->EnemyHealth -= 1;
		}
	}
	if (Enemy->AttackingPlayer)
	{
		if (Tick%2 == 0)
		{
			if (sqrt(
				(abs(PlayerPosition.x - Enemy->EnemyPosition.x) * abs(PlayerPosition.x - Enemy->EnemyPosition.x)) +
				(abs(PlayerPosition.y - Enemy->EnemyPosition.y) * abs(PlayerPosition.y - Enemy->EnemyPosition.y))) <= Enemy->AttackRange)
			{
				if (Tick % 4 == 0)
					*PlayerHealth -= 1;
			}
			else
			{
				if (Enemy->EnemyPosition.x > PlayerPosition.x)
					EnemyMovement.x = -4;
				else if (Enemy->EnemyPosition.x < PlayerPosition.x)
					EnemyMovement.x = 4;
				if (Enemy->EnemyPosition.y > PlayerPosition.y)
					EnemyMovement.y = -4;
				else if (Enemy->EnemyPosition.y < PlayerPosition.y)
					EnemyMovement.y = 4;
			}

			
			
				if (abs(Enemy->EnemyPosition.y - PlayerPosition.y) <= abs(Enemy->EnemyPosition.x - PlayerPosition.x))
				{
					if (EnemyMovement.x == -4)
						Enemy->EnemySprite.CurrentSprite.y = 1;
					if (EnemyMovement.x == 4)
						Enemy->EnemySprite.CurrentSprite.y = 2;
				}
				if (abs(Enemy->EnemyPosition.y - PlayerPosition.y) >= abs(Enemy->EnemyPosition.x - PlayerPosition.x))
				{
					if (EnemyMovement.y == -4)
						Enemy->EnemySprite.CurrentSprite.y = 3;
					if (EnemyMovement.y == 4)
						Enemy->EnemySprite.CurrentSprite.y = 0;
				}
			
		}
		moving = true;
	}
	else
	{
		switch (Enemy->Routine[Enemy->CurrentInstruction])
		{
		case GoForward:
			EnemyMovement.y = -4;
			Enemy->EnemySprite.CurrentSprite.y = 3;
			moving = true;
			break;
		case GoLeft:
			EnemyMovement.x = -4;
			Enemy->EnemySprite.CurrentSprite.y = Enemy->Routine[Enemy->CurrentInstruction];
			moving = true;
			break;
		case GoRight:
			EnemyMovement.x = 4;
			Enemy->EnemySprite.CurrentSprite.y = Enemy->Routine[Enemy->CurrentInstruction];
			moving = true;
			break;
		case GoBackward:
			EnemyMovement.y = 4;
			Enemy->EnemySprite.CurrentSprite.y = 0;

			moving = true;
			break;
		case LookAround:
			if (sqrt(
				(abs(PlayerPosition.x - Enemy->EnemyPosition.x) * abs(PlayerPosition.x - Enemy->EnemyPosition.x)) +
				(abs(PlayerPosition.y - Enemy->EnemyPosition.y) * abs(PlayerPosition.y - Enemy->EnemyPosition.y))) <= 60)
			{
				Enemy->AttackingPlayer = true;
				TraceLog(5, "Come here you little poophead");
			}
			/*TraceLog(5, TextFormat("%lf", sqrt(
				(abs(PlayerPosition.x - Enemy->EnemyPosition.x) * abs(PlayerPosition.x - Enemy->EnemyPosition.x)) +
				(abs(PlayerPosition.y - Enemy->EnemyPosition.y) * abs(PlayerPosition.y - Enemy->EnemyPosition.y)))));*/

			if (Tick - Enemy->CurrentInstruction == 1)
				Enemy->EnemySprite.CurrentSprite.y = 3;
			if ((Tick - Enemy->CurrentInstruction) % 30 == 1)
			{
				if (Enemy->EnemySprite.CurrentSprite.y == 2) { Enemy->EnemySprite.CurrentSprite.y = 1; }
				else if (Enemy->EnemySprite.CurrentSprite.y == 0) { Enemy->EnemySprite.CurrentSprite.y = 4; }
				else if (Enemy->EnemySprite.CurrentSprite.y == 3) { Enemy->EnemySprite.CurrentSprite.y = 2; }
				else if (Enemy->EnemySprite.CurrentSprite.y == 1) { Enemy->EnemySprite.CurrentSprite.y = 3; }
			}

			if (Tick - Enemy->InstructionStartTick > 120)
				Enemy->InstructionStartTick = Tick;

		default:
			//TraceLog(5, TextFormat("No instructions executed.\n%d, %d", Enemy->Routine[Enemy->CurrentInstruction], Enemy->CurrentInstruction));
			break;

		}
	}
	Enemy->LastPosition = Enemy->EnemyPosition;
	Enemy->EnemyPosition.x += EnemyMovement.x;

	if ((Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundDown(Enemy->EnemyPosition.x - 100, 40) / 40] > 0) ||
		(Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundUp(Enemy->EnemyPosition.x - 100, 40) / 40] > 0))
	{
		Enemy->EnemyPosition.x = Enemy->LastPosition.x;
	}

	Enemy->EnemyPosition.y += EnemyMovement.y;

	if ((Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundDown(Enemy->EnemyPosition.x - 100, 40) / 40] > 0) ||
		(Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundUp(Enemy->EnemyPosition.x - 100, 40) / 40] > 0))
	{
		Enemy->EnemyPosition.y = Enemy->LastPosition.y;
	}

	if ((Tick % 15 == 0) && (moving == true))
	{
		if (Enemy->EnemySprite.CurrentSprite.x == 0)
			Enemy->EnemySprite.CurrentSprite.x = 1;
		else
			Enemy->EnemySprite.CurrentSprite.x = 0;
	}

	else if (!moving)
	{
		Enemy->EnemySprite.CurrentSprite.x = 2;
	}

	if ((Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundDown(Enemy->EnemyPosition.x - 100, 40) / 40] > 0) ||
		(Area->ceiling[RoundDown(Enemy->EnemyPosition.y, 40) / 40][RoundUp(Enemy->EnemyPosition.x - 100, 40) / 40] > 0))
	{
		Enemy->EnemyPosition = Enemy->LastPosition;
	}


	if (Enemy->CurrentInstruction == 255)
	{
		Enemy->CurrentInstruction = 0;
		//TraceLog(5, "Reset Enemy Instruction. ");
	}
	else if ((Enemy->Routine[Enemy->CurrentInstruction] != LookAround) || Tick - Enemy->InstructionStartTick == 120)
		Enemy->CurrentInstruction += 1;

	Enemy->EnemyItem.ItemSprite.CurrentSprite.y = Enemy->EnemySprite.CurrentSprite.y;
	//TraceLog(5, TextFormat("%d", Enemy->CurrentInstruction), ((Tick % 255) - 1));


}