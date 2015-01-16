#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"

class Intro_Board
{
public:
	Intro_Board(SDL_Setup* pass_sdl);
	~Intro_Board(void);
	void Draw(int i, SDL_Rect pass_wrap);

private:
	Sprite* sp;

	Uint32 time_slice;

	SDL_Rect rect;
	SDL_Rect wrap[10];
	SDL_Setup* sdl_setup;
};

