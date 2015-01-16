#pragma once
#include "Sprite.h"
#include "SDL_Setup.h"

class Land_Scape
{
public:
	Land_Scape(SDL_Setup* pass_sdl, std::string FilePath, int rect_w, int rect_h);
	~Land_Scape(void);
	void Draw(int disp_x, int disp_y, SDL_Rect* wrap = NULL);

private:
	Sprite* sp;

	SDL_Rect rect;
	SDL_Setup* sdl_setup;
};

