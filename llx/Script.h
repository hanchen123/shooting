#pragma once

class Script
{
public:
	Script(SDL_Renderer* pass_renderer, std::string FilePath, int font_size);
	~Script(void);
	TTF_Font* Get_Font();

private:
	TTF_Font* font;
	SDL_Renderer* renderer;
};

