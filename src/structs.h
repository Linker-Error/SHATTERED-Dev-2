#include "raylib.h"

#ifndef STRUCTS
#define STRUCTS


enum EnemyControl { GoForward = 0, GoLeft = 1, GoRight = 2, GoBackward = 3, LookAround = 4 };
enum ItemType { Resource = 0, Tool = 1, Weapon = 2 };
enum WeaponType { NotaWeapon = 0, MeleeOneHand = 1, MeleeTwoHand = 2, RangedBow = 3, RangedDroppable = 4, RangedThrowable = 5, Sampo = 6 };


struct Map
{
	int floor[20][20];
	int ceiling[20][20];
};

struct MapTextures
{
	Texture2D* Floors[16];
	Texture2D* Walls[16];
};

struct Sprite
{
	Texture2D * SpriteSheet;
	int SpriteLength;
	int SpriteHeight;
	Vector2 CurrentSprite;
};

struct Item
{
	
	enum ItemType ItemType;
	enum WeaponType WeaponType;

	struct Sprite ItemSprite;

	Vector2 OffSet[4];
	Vector2 IconID;

	bool IsOnTop[4];
};

struct Inventory
{
	struct Item InventoryItems[5][5];
};

struct Enemy
{
	bool AttackingPlayer;
	bool IsDead;

	int CurrentInstruction;
	int InstructionStartTick;
	int EnemyHealth;

	double AttackRange;

	Vector2 EnemyPosition;
	Vector2 LastPosition;

	struct Sprite EnemySprite;
	struct Item EnemyItem;

	enum EnemyControl Routine[256];
};


#endif