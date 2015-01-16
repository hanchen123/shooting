#pragma once
#include "Script.h"
#include <fstream>
#include <vector>

class Dialog
{
public:
	Dialog(SDL_Renderer* pass_renderer);
	~Dialog(void);
	void Read_Text();
	int Check_Startidx(const char* flag);
	void Set_Startidx(int index);
	void Write_Text(const char* flag, int index);
	
private:
	int dial_idx;	//vector dialog index
	int	counter;	//y position counter
	int judge_idx;	// store last index from Write_Text() function.
	int check_idx;
	int start_idx;

	Script* spt;
	SDL_Renderer* renderer;

	std::vector<std::string> dial;
};

