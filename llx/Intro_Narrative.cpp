#include "StdAfx.h"
#include "Intro_Narrative.h"

Intro_Narrative::Intro_Narrative(SDL_Renderer* pass_renderer)
{
	renderer = pass_renderer;
	
	spt = new Script(pass_renderer, "font/Cassia Regular.ttf", 30);
	Read_Text();
	narr_idx = 0;
	counter = 0;
	judge_idx = 0;
	start_idx = 0;
}


Intro_Narrative::~Intro_Narrative(void)
{
	delete spt;

	narr.clear();
}

void Intro_Narrative::Read_Text()
{
	std::ifstream in("data/intro.dat");

	if(!in.is_open())
		std::cout<< "file not opened";

	char buf[256];

	while(!in.eof())
	{
		in.getline(buf, 256);
		narr.push_back(std::string(buf));
	}
}

void Intro_Narrative::Write_Text(int index)
{
	if(narr_idx < narr.size() - 1 && judge_idx != index)
	{
		narr_idx++;	//skip 0 size
		start_idx = narr_idx;
		judge_idx = index;
	}
	else
		narr_idx = start_idx;

	SDL_Color color = {255, 255, 255};
	while(narr[narr_idx].size() != 0)
	{
		int oo = narr[narr_idx].size();
		const char *tmp = narr[narr_idx].c_str();

		SDL_Surface* surf = TTF_RenderText_Blended(spt->Get_Font(), tmp, color);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
		;
		int text_w = 0;
		int text_h = 0;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);

		SDL_Rect rec = {40, 600 + 40*counter, text_w, text_h};
		SDL_RenderCopy(renderer, tex, NULL, &rec);

		SDL_FreeSurface(surf);
		SDL_DestroyTexture(tex);

		narr_idx++;
		counter++;
	}
	counter = 0;
}