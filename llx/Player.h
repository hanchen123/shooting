#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"

enum
{
	Up,
	Down,
	Left,
	Right,
};

const int MOVING_SPEED = 4;
const int LIVE = 3;
const int ONELIVE = 10;
const int GEASS = 50;

class Player
{
public:
	Player(SDL_Setup* pass_sdl);
	~Player(void);
	void Move(void);
	void Attack(void);
	void Draw(SDL_Rect* wrap = NULL);

	int Get_Status(void);
	int Get_Firestatus(void);
	void Set_Firestatus(int i);
	bool Get_Shoot(void);
	bool Get_Geass(void);
	void Set_Geass(bool g);
	int Get_Geassmana(void);
	void Set_Geassmana(int mana);
	int Get_Lives(void);
	void Set_Lives(int num);
	int Get_Hits(void);
	void Set_Hits(int num);
	Sprite* Get_Sprite();

private:	
	int status;
	bool shoot;
	bool geass;
	int fire_status;
	int lives;
	int geass_mana;
	int hitpoints;

	Sprite* sp;

	SDL_Rect rect;
	SDL_Rect wrap;
	SDL_Setup* sdl_setup;
};

