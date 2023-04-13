#include "raylib.h"
#include "DrawFunctions.h"
#include "structs.h"
#include "InputChecks.h"
#include <stdbool.h>



void DrawSprite(struct Sprite Sprite, Vector2 Position)
{
	DrawTexturePro(*Sprite.SpriteSheet, (Rectangle) { 
		Sprite.CurrentSprite.x * Sprite.SpriteLength,
		Sprite.CurrentSprite.y * Sprite.SpriteHeight,
		Sprite.SpriteLength, Sprite.SpriteHeight },
		(Rectangle) { Position.x, Position.y, 4 * Sprite.SpriteLength, 4 * Sprite.SpriteHeight }, 
			(Vector2) { 0, 0 }, 0, WHITE);
}

void DrawMenu(struct Inventory Inventory, struct Sprite ItemIcons)
{
	int i;
	int j;
	for (i = 0; i < 5; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			ItemIcons.CurrentSprite = Inventory.InventoryItems[i][j].IconID;
			DrawSprite(ItemIcons, (Vector2) { j * 40, i * 40 });
		}
	}
}

void DrawTile(int Tile, Vector2 Position, Texture2D* TileTextures[16], bool IsFloor)
{
	Color TileTint;
	if (IsFloor)
		TileTint = DARKGRAY;
	else
		TileTint = WHITE;
	if (Tile == 0)
		return;

	DrawTextureEx(*TileTextures[Tile - 1], Position, 0, 4, TileTint);
}

void DrawWall(int Wall, Vector2 Position, Texture2D* WallTextures[16])
{
	if (Wall == 0)
		return;

	DrawTextureEx(*WallTextures[Wall - 1], Position, 0, 4, GRAY);
}

void DrawGame(struct Map Area, struct MapTextures AreaTextures, Vector2 PlayerPosition, struct Sprite CharacterSprite, struct Enemy enemies[16], int NumberOfEnemies, struct Item Item, int PlayerHealth, int MaxHealth, Font PixelFont, bool PlayerAttacking)
{
	int WhereToDrawEnemies[16];
	
	for (int i = 0; i < 16; ++i)
	{
		if (i >= NumberOfEnemies || enemies[i].IsDead)
			WhereToDrawEnemies[i] = -1;
		else
			WhereToDrawEnemies[i] = (((int)enemies[i].EnemyPosition.y + 60) - ((int)(enemies[i].EnemyPosition.y + 60) % 40)) / 40 - 1;
	}

	
	int WhereToDrawPlayer = (((int)PlayerPosition.y + 60) - ((int)(PlayerPosition.y + 60) % 40)) / 40 - 1;
	//Draw Floor
	int x, y;
	for (x = 0; x < 20; ++x)
	{
		for (y = 0; y < 20; ++y)
		{
			DrawTile(Area.floor[y][x], (Vector2) { 100 + x * 40, 60 + y * 40 }, AreaTextures.Floors, true);
		}
	}
	
	//Draw Ceiling
	for (y = 0; y < 20; ++y)
	{

		//Check whether or not to draw player
		if (y == WhereToDrawPlayer)
		{
			if (Item.IsOnTop[(int)(CharacterSprite.CurrentSprite.y)])
			{
				//Draw player sprite
				DrawSprite(CharacterSprite, PlayerPosition);
				//Draw item sprite
				
				if (PlayerAttacking == true)
				{

					DrawSprite(Item.ItemSprite, (Vector2) { PlayerPosition.x + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].x, PlayerPosition.y + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].y});

				}
					
				else
					DrawSprite(Item.ItemSprite, (Vector2) { PlayerPosition.x + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].x, PlayerPosition.y + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].y });
			}
			else
			{
				//Draw item sprite
				if (PlayerAttacking == true)
				{

					DrawSprite(Item.ItemSprite, (Vector2) { PlayerPosition.x + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].x, PlayerPosition.y + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].y });

				}

				else
					DrawSprite(Item.ItemSprite, (Vector2) { PlayerPosition.x + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].x, PlayerPosition.y + Item.OffSet[(int)(CharacterSprite.CurrentSprite.y)].y });
				//Draw player sprite
				DrawSprite(CharacterSprite, PlayerPosition);
			}
		};
		//Check whether or not to draw enemies
		for (int j = 0; j < 16; ++j)
		{
			if (WhereToDrawEnemies[j] == y)
			{
				if (enemies[j].EnemyItem.IsOnTop[(int)(enemies[j].EnemySprite.CurrentSprite.y)])
				{
					//Draw enemy sprite
					DrawSprite(enemies[j].EnemySprite, enemies[j].EnemyPosition);
					//Draw item sprite
					DrawSprite(enemies[j].EnemyItem.ItemSprite, (Vector2) { enemies[j].EnemyPosition.x + enemies[j].EnemyItem.OffSet[(int)(enemies[j].EnemySprite.CurrentSprite.y)].x, enemies[j].EnemyPosition.y + enemies[j].EnemyItem.OffSet[(int)(enemies[j].EnemySprite.CurrentSprite.y)].y });
				}
				else
				{
					//Draw item sprite
					DrawSprite(enemies[j].EnemyItem.ItemSprite, (Vector2) { enemies[j].EnemyPosition.x + enemies[j].EnemyItem.OffSet[(int)(enemies[j].EnemySprite.CurrentSprite.y)].x, enemies[j].EnemyPosition.y + enemies[j].EnemyItem.OffSet[(int)(enemies[j].EnemySprite.CurrentSprite.y)].y });
					//Draw enemy sprite
					DrawSprite(enemies[j].EnemySprite, enemies[j].EnemyPosition);
				}
			}
		}


		for (x = 0; x < 20; ++x)
		{
			DrawTile(Area.ceiling[y][x], (Vector2) { 100 + x * 40, 0 + y * 40 }, AreaTextures.Floors, false);
			

			if ((Area.ceiling[y + 1][x] == 0 && Area.ceiling[y][x] != 0))
				DrawWall(Area.ceiling[y][x], (Vector2) { 100 + x * 40, 0 + (y+1) * 40 }, AreaTextures.Walls);
			else if (y == 19)
				DrawWall(Area.ceiling[y][x], (Vector2) { 100 + x * 40, 0 + (y + 1) * 40 }, AreaTextures.Walls);
			if ((PlayerPosition.y + 60 <= 60 + (y - 0) * 40) && (PlayerPosition.y + 60 >= 60 + (y + 1) * 40))
				DrawRectangleV(PlayerPosition, (Vector2) { 40, 60 }, YELLOW);
		}



		//Draw health bar

		DrawRectangle(8, 880 - (MaxHealth * 4) - 8, 24, (MaxHealth * 4) + 8, DARKGRAY);
		DrawRectangle(12, 880 - (MaxHealth * 4) - 4, 16, (MaxHealth * 4), LIGHTGRAY);
		DrawRectangle(12, 880 - (PlayerHealth * 4) - 4, 16, (PlayerHealth * 4), RED);
		
		DrawTextEx(PixelFont, "HP", (Vector2) { 36, 832 }, 48, 0, RED);
	}
}