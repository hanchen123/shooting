#pragma once
class SDL_Setup
{
public:
	SDL_Setup(int screen_w, int screen_h);
	~SDL_Setup(void);
	
	SDL_Renderer* Get_Renderer();
	SDL_Event* Get_Main();

	void Start();
	void End();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainevent;
};

