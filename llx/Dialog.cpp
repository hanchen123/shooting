#include "StdAfx.h"
#include "Dialog.h"


Dialog::Dialog(SDL_Renderer* pass_renderer)
{
	renderer = pass_renderer;
	
	spt = new Script(pass_renderer, "font/Cassia Regular.ttf", 25);
	Read_Text();
	dial_idx = 0;
	counter = 0;
	judge_idx = 0;
	start_idx = 0;
	check_idx = 0;
}


Dialog::~Dialog(void)
{
	delete spt;

	dial.clear();
}

void Dialog::Read_Text()
{
	std::ifstream in("data/dialog.dat");

	if(!in.is_open())
		std::cout<< "file not opened";

	char buf[256];

	while(!in.eof())
	{
		in.getline(buf, 256);
		dial.push_back(std::string(buf));
	}
}

int Dialog::Check_Startidx(const char* flag)
{
	while(strcmp(dial[check_idx].c_str(), flag))
		check_idx++;
	return ++check_idx;
}

void Dialog::Set_Startidx(int index)
{
	start_idx = index;
}

void Dialog::Write_Text(const char* flag, int index)
{
	if(dial_idx < dial.size() - 1 && judge_idx != index)
	{
		dial_idx++;	//skip 0 size
		start_idx = dial_idx;
		judge_idx = index;
	}
	else
		dial_idx = start_idx;

	SDL_Color color = {0, 0, 0};
	while(dial[dial_idx].size() != 0 && strcmp(dial[dial_idx].c_str(), flag))
	{
		const char* tmp = dial[dial_idx].c_str();
		int oo = dial[dial_idx].size();

		SDL_Surface* surf = TTF_RenderText_Blended(spt->Get_Font(), tmp, color);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
		;
		int text_w = 0;
		int text_h = 0;
		SDL_QueryTexture(tex, NULL, NULL, &text_w, &text_h);

		SDL_Rect rec = {460, 150 + 35*counter, text_w, text_h};
		SDL_RenderCopy(renderer, tex, NULL, &rec);

		SDL_FreeSurface(surf);
		SDL_DestroyTexture(tex);

		dial_idx++;
		counter++;
	}
	counter = 0;
}