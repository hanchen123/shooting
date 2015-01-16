#pragma once
#include "Script.h"
#include <fstream>
#include <vector>

class Intro_Narrative
{
public:
	Intro_Narrative(SDL_Renderer* pass_renderer);
	~Intro_Narrative(void);
	void Read_Text();
	void Write_Text(int index);

private:
	int narr_idx;	//vector narr index
	int	counter;	//y position counter
	int judge_idx;	// store last index from Write_Text() function.
	int start_idx;

	Script* spt;
	SDL_Renderer* renderer;

	std::vector<std::string> narr;
};

