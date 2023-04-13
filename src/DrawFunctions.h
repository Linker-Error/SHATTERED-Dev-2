#include "raylib.h"


#ifndef DRAWFUNCTIONS
#define DRAWFUNCTIONS

void DrawTile(int Tile, Vector2 Position, Texture2D* TileTextures[16], bool isFloor);
void DrawGame(struct Map Area, struct MapTextures AreaTextures, Vector2 PlayerPosition, struct Sprite CharacterSprite, struct Enemy enemies[16], int NumberOfEnemies, struct Item Item, int PlayerHealth, int MaxHealth, Font PixelFont, bool PlayerAttacking);
void DrawWall(int Wall, Vector2 Position, Texture2D* WallTextures[16]);
void DrawSprite(struct Sprite Sprite, Vector2 Position);
void DrawMenu(struct Inventory Inventory, struct Sprite ItemIcons);

#endif
