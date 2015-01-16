#include "StdAfx.h"
#include "SDL_Setup.h"


SDL_Setup::SDL_Setup(int pass_w, int pass_h)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = NULL;
	window = SDL_CreateWindow("Code Geass", 100, 100, pass_w, pass_h, SDL_WINDOW_SHOWN);
	if(window == NULL) 
		std::cout << "Window load error" << std::endl;

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL) 
		std::cout << "Renderer load error" << std::endl;

	mainevent = new SDL_Event();
}


SDL_Setup::~SDL_Setup(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainevent;	
}

SDL_Renderer* SDL_Setup::Get_Renderer()
{
	return renderer;
}

SDL_Event* SDL_Setup::Get_Main()
{
	return mainevent;	
}

void SDL_Setup::Start()
{
	SDL_PollEvent(mainevent);
	SDL_RenderClear(renderer);
}

void SDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}
