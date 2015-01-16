#include "StdAfx.h"
#include "Script.h"


Script::Script(SDL_Renderer* pass_renderer, std::string FilePath, int font_size)
{
	renderer = pass_renderer;

	TTF_Init();
	font = NULL;
	font = TTF_OpenFont(FilePath.c_str(), font_size);
	if(font == NULL) 
		std::cout << "Font load errer" << std::endl;
}


Script::~Script(void)
{
	TTF_CloseFont(font);
}

TTF_Font* Script::Get_Font()
{
	return font;
}

