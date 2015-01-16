#include "StdAfx.h"
#include "Intro_Board.h"


Intro_Board::Intro_Board(SDL_Setup* pass_sdl)
{
	sdl_setup = pass_sdl;
	sp = new Sprite(sdl_setup->Get_Renderer(), "pic/story.jpg", 0, 0, 1000, 630);

	rect.x = 0;
	rect.y = 0;
	rect.w = 1000;
	rect.h = 557;

	for (int i = 0; i <= 9; i++)
	{
		wrap[i].x = 0;
		wrap[i].y = (557 * i);
		wrap[i].w = 1000;
		wrap[i].h = 557;
	}
}


Intro_Board::~Intro_Board(void)
{
	delete sp;
}

void Intro_Board::Draw(int i, SDL_Rect pass_rect)
{
	if(i >= 0)
		SDL_RenderCopy(sdl_setup->Get_Renderer(), sp->Get_Sprite(), &wrap[i], &rect); 
	else
	{
		SDL_Rect tmp1 = {pass_rect.x, 0, pass_rect.w, 557};
		SDL_Rect tmp2 = {0, pass_rect.y, pass_rect.w, 557};
		SDL_RenderCopy(sdl_setup->Get_Renderer(), sp->Get_Sprite(), &tmp2, &tmp1);
	}
}