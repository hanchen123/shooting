#include "StdAfx.h"
#include "Player.h"

const Uint8* keystate = SDL_GetKeyboardState(NULL);

Player::Player(SDL_Setup* pass_sdl)
{
	sdl_setup = pass_sdl;
	sp = new Sprite(sdl_setup->Get_Renderer(), "pic/player.png", 440, 600, 375, 625);

	lives = LIVE;
	hitpoints = ONELIVE;
	status = 2;
	fire_status = 0;
	geass_mana = GEASS;
	shoot = false;
	geass = false;

	rect.x = 0;
	rect.y = 0;
	rect.w = 363;
	rect.h = 455;
}


Player::~Player(void)
{
	delete sp;
}

void Player::Move(void)
{
	if(keystate[SDL_GetScancodeFromKey(SDLK_w)] && sp->Gety() > 0)
		sp->Sety(sp->Gety() - MOVING_SPEED);
	else if(keystate[SDL_GetScancodeFromKey(SDLK_s)] &&  sp->Gety() < 710)
		sp->Sety(sp->Gety() + MOVING_SPEED);
	if(keystate[SDL_GetScancodeFromKey(SDLK_a)] && sp->Getx() > 0)
	{
		if (status < 4)
			status += 1;
	}
	else
		if (status > 2)
			status -= 1;
	else if(keystate[SDL_GetScancodeFromKey(SDLK_d)] && sp->Getx() < 879)
	{
		if (status > 0)
			status -= 1;
	}
	else
		if (status < 2)
			status += 1;

	if (status < 2)
		sp->Setx(sp->Getx() + (MOVING_SPEED + (2*(1 - status))));
	if (status > 2)
		sp->Setx(sp->Getx() - (MOVING_SPEED + (2*(status - 3))));
}

void Player::Attack(void)
{
	if (keystate[SDL_GetScancodeFromKey(SDLK_j)])
	{
		shoot = true;
		if (fire_status == 0)
			fire_status = 2;
	}
	else
		shoot = false;
	if (keystate[SDL_GetScancodeFromKey(SDLK_k)] && geass_mana >= GEASS && !geass)
	{
		geass = true;
		geass_mana -= GEASS;
	}
}

void Player::Draw(SDL_Rect* wrap)
{
    SDL_Rect tmp;
    tmp.x = sp->Getx();
    tmp.y = sp->Gety();
	tmp.w = wrap->w;
	tmp.h = wrap->h;

	SDL_RenderCopy(sdl_setup->Get_Renderer(), sp->Get_Sprite(), wrap, &tmp);
}

int Player::Get_Status(void)
{
	return status;
}

Sprite* Player::Get_Sprite()
{
	return sp;
}

int Player::Get_Firestatus(void)
{
	return fire_status;
}

void Player::Set_Firestatus(int i)
{
	fire_status = i;
}

bool Player::Get_Shoot(void)
{
	return shoot;
}

bool Player::Get_Geass(void)
{
	return geass;
}

void Player::Set_Geass(bool g)
{
	geass = g;
}

int Player::Get_Geassmana(void)
{
	return geass_mana;
}

void  Player::Set_Geassmana(int mana)
{
	geass_mana = mana;
	if(geass_mana > 3*GEASS)
		geass_mana = 3*GEASS;
}

int Player::Get_Lives(void)
{
	return lives;
}

void Player::Set_Lives(int num)
{
	lives = num;
}

int Player::Get_Hits(void)
{
	return hitpoints;
}

void Player::Set_Hits(int num)
{
	hitpoints = num;
	if(hitpoints < 0)
		hitpoints = 0;
}