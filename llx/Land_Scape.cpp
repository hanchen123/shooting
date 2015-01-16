#include "StdAfx.h"
#include "Land_Scape.h"


Land_Scape::Land_Scape(SDL_Setup* pass_sdl, std::string FilePath, int rect_w, int rect_h)
{
	sdl_setup = pass_sdl;
	sp = new Sprite(sdl_setup->Get_Renderer(), FilePath.c_str(), 0, 0, rect_w, rect_h);

	rect.x = 0;
	rect.y = 0;
	rect.w = rect_w;
	rect.h = rect_h;
}


Land_Scape::~Land_Scape(void)
{
	delete sp;
}

void Land_Scape::Draw(int disp_x, int disp_y, SDL_Rect* wrap)
{
    SDL_Rect tmp;
    tmp.x = disp_x;
    tmp.y = disp_y;
	if(wrap == NULL)
	{
		tmp.w = rect.w;
		tmp.h = rect.h;
	}
	else
	{
		tmp.w = wrap->w;
		tmp.h = wrap->h;
	}

	SDL_RenderCopy(sdl_setup->Get_Renderer(), sp->Get_Sprite(), wrap, &tmp);
}