#include "StdAfx.h"
#include "Game.h"

int menu_bframe[2] = {0, 2132};	//menu board x 
int score[8] = {0,0,0,0,0,0,0,0};
const Uint8* keystate2 = SDL_GetKeyboardState(NULL);

Game::Game(int pass_w, int pass_h)
{
	screen_w = pass_w;
	screen_h = pass_h;

	sdl_setup = new SDL_Setup(screen_w, screen_h);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

	delay = 100;
	srand(time(0));
	quit = false;
//	introduction init
	introduction = true;
	intro_idx = 0;
	intro_lastime = 0;
	intro_done = false;
	story_board = new Intro_Board(sdl_setup);

	intro_narr_idx = 0;
	story_words = new Intro_Narrative(sdl_setup->Get_Renderer());
// mainmenu init
	mainmenu = true;
	menu_gameover = false;
	menu_board = new Sprite(sdl_setup->Get_Renderer(), "pic/streaks.jpg", 0, 0, 2132, 800);	
	menu_options = new Sprite(sdl_setup->Get_Renderer(),"pic/menops.png", 50, 550, 319, 246);	//menu options
	menu_logo = new Sprite(sdl_setup->Get_Renderer(),"pic/menboard.png", 0, 0, 1000, 800);
//game over init
	ov = false;
	pripro = 5;
	procounter = 0;
//map init
	current_level = 0;	//game level
	scape_count = 0;	
	sec_scapect = 0;	
	onetime = false;
	numdrums = 0;
	Read_Map();
//game global init
	unicounter = 0;	//global counter
	transtatus = 0;
	transposit = 1000;
	continued = 0;
	contcounter = 0;
//waks wrap counter init
	wf = 0;
	rdir = 0;
	rframe = 0;
//ground army init
	grq = 0;
	numgr = 0;
	groundact = 0;
	Read_Groundarmy();
//gunboat init
	btcue = 0;
	quantgbt = 0;
	benct = 0;
//air army init
	numhells = 0;
	cuer = 0;
	cl2q = 0;
	alienqun = 0;
	numal2 = 0;
	Read_Airarmy();
//gfire init
	hgunct = 0;
//lightning init
	numlight = 0;
	numspk = 0;
//lazer init
	quantlz = 0;
	quanhz = 0;
//turrret init
	tur_counter = 0;
	qutur = 0;
	qumzfl = 0;
//pellets init
	quanpel = 0;
	pfr = 0;
//player init
	player_active = 1;
	player_control = 1;
	player_dir = 0;
	pe = 0;
	explopr = 0;
//geass init
	geass_counter = 0;
	icon_counter = 0;
	icon_dir = 0;
//gun fire init
	gun_attack = 0;
	bullnum = 0;
//warning init
	warnstatus = 0;
	warnfr = 0;
//boss2 init
	charge = 0;
	charge_x = 0;
	charge_y = 0;
	charge_r = CHARGE_SPEED;
	ready = 0;
//boss init
	boss_active = 0;
//boss weapon init
	prspg = 0;	
	laseron = 0;
	spghit = 0;
	spghitloc = 0;
	quanp = 0;
	qunplspl = 0;
//strikes init
	numstrikes = 0;
	tagger = 0;
//explosion init
	nmexpsec = 0;
	numexp = 0;
//boss explosion init
	explocounter = 0;
//being hit init
	schmhit = 0;
	invm = 0;
	respawncounter = 0;
	invulnerability = 0;
	quanspt = 0;
//dialog init
	guide = true;
	dialog_lastime = 0;
	dial_idx = 0;
	dial = new Dialog(sdl_setup->Get_Renderer());
}


Game::~Game(void)
{
	Mix_CloseAudio();

	delete sdl_setup;
	SDL_Quit();
}

void Game::Read_Map(void)
{
	std::ifstream in("data/map.dat");	//read from this file	
	int num = 0;
	std::vector<int> tmp;
	while(!in.eof())	
	{
		for(int i = 0; i < 10; i++)
		{
			in >> level[num][i];	//read the 10 integers
			if(level[num][i] == 8)
			{							
				tmp.push_back(num);	//init turret
				tmp.push_back(i);
				turcue.push_back(tmp);
				tmp.clear();
			}
		}
		num++;	
	}
	in.close();
}

void Game::Read_Groundarmy(void)
{
	std::ifstream in("data/groundarmy.dat");	//read from this file	
	int num = 0;
	while(!in.eof())	
	{
		for(int i = 0; i < 4; i++)
		{
			in >> grncue[num][i];	//read the 4 integers
		}
		num++;	
	}
	in.close();
}

void Game::Read_Airarmy(void)
{
	std::ifstream in1("data/airpattern.dat");	//read from this file	
	int num = 0;
	while(!in1.eof())	
	{
		for(int i = 0; i < 20; i++)
		{
			in1 >> atpattern[num][i];	//read the 20 integers
		}
		num++;	
	}
	in1.close();

	std::ifstream in2("data/airarmy.dat");	//read from this file	
	num = 0;
	while(!in2.eof())	
	{
		for(int i = 0; i < 5; i++)
		{
			in2 >> aliencues[num][i];	//read the 5 integers
		}
		num++;	
	}
	in2.close();

	std::ifstream in3("data/airarmy2.dat");	//read from this file	
	num = 0;
	while(!in3.eof())	
	{
		for(int i = 0; i < 5; i++)
		{
			in3 >> cl2alcue[num][i];	//read the 5 integers
		}
		num++;	
	}
	in3.close();
}

void Game::Draw_Storyboard(void)
{
	SDL_Rect tmp = {0, 0, 0, 0};
	story_board->Draw((scoll_frame[intro_idx][1]), tmp);
	
	if (scoll_frame[intro_idx][0] == 2)
	{
		tmp.x = (1000 - (intro_lastime * 10));
		tmp.y = (557 * (scoll_frame[intro_idx][2]));
		tmp.w = (10 * intro_lastime);
		tmp.h = 557;
		story_board->Draw(-1, tmp);
	}
	intro_lastime++;

	if (intro_lastime > (scoll_frame[intro_idx][3]))
	{
		intro_idx++;
		intro_lastime = 0;
		if(scoll_frame[intro_idx][0] == 1 && intro_idx > 2)
			intro_narr_idx++;
	}
	if (intro_idx > 19)
	{
		intro_done = true;
		introduction = false;
	}		
}	

void Game::Draw_Dialog1(void)
{
	if(dialog_lastime <= 80)
		dialog1->Draw((1000 - (dialog_lastime * 10)), 100);

	if (dialog_lastime > 80)
	{
		dialog1->Draw(200, 100);
		dial->Write_Text("1", dial_idx);
	}
	dialog_lastime++;
	if (dialog_lastime == 200)
		dial_idx++;
	if (dialog_lastime > 350)
	{
		guide = false;	
		dialog_lastime = 0;
		dial_idx++;
	}	
}	

void Game::Draw_Dialog2(void)
{
	if(dialog_lastime <= 80)
		dialog2->Draw((1000 - (dialog_lastime * 10)), 100);

	if (dialog_lastime > 80)
	{
		dialog2->Draw(200, 100);
		dial->Write_Text("2", dial_idx);
	}
	dialog_lastime++;
	if (dialog_lastime == 200)
		dial_idx++;
	if (dialog_lastime > 350)
	{
		guide = false;	
		dialog_lastime = 0;
		dial_idx++;
	}
}	

void Game::Draw_Dialog3(void)
{
	if(dialog_lastime <= 80)
		dialog1->Draw((1000 - (dialog_lastime * 10)), 100);

	if (dialog_lastime > 80)
	{
		dialog1->Draw(200, 100);
		dial->Write_Text("3", dial_idx);
	}
	dialog_lastime++;
	if (dialog_lastime == 200)
		dial_idx++;
	if (dialog_lastime > 350)
	{
		guide = false;	
		dialog_lastime = 0;
		dial_idx++;
	}
}

void Game::Draw_Dialog4(void)
{
	if(dialog_lastime <= 80)
		dialog3->Draw((1000 - (dialog_lastime * 10)), 100);

	if (dialog_lastime > 80)
	{
		dialog3->Draw(200, 100);
		dial->Write_Text("4", dial_idx);
	}
	dialog_lastime++;
	if (dialog_lastime == 200)
		dial_idx++;
	if (dialog_lastime > 350)
	{
		guide = false;	
		dialog_lastime = 0;
		dial_idx++;
	}
}

void Game::Draw_Dialog(void)
{
	if(guide && unicounter == 0)
	{
		Draw_Dialog1();
		if(keystate2[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
		{
			guide = false;
			dialog_lastime = 0;
			dial->Set_Startidx(dial->Check_Startidx("1"));
		}
	}

	if(unicounter == 5450)
		guide = true;
	if(guide && unicounter == 5450)
	{
		Draw_Dialog2();
		if(keystate2[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
		{
			guide = false;
			dialog_lastime = 0;
			dial->Set_Startidx(dial->Check_Startidx("2"));
		}
	}

	if(unicounter == 6050)
		guide = true;
	if(guide && unicounter == 6050)
	{
		Draw_Dialog3();
		if(keystate2[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
		{
			guide = false;
			dialog_lastime = 0;
			dial->Set_Startidx(dial->Check_Startidx("3"));
		}
	}

	if(unicounter == 11200)
		guide = true;
	if(guide && unicounter == 11200)
	{
		Draw_Dialog4();
		if(keystate2[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
		{
			guide = false;
			dialog_lastime = 0;
			dial->Set_Startidx(dial->Check_Startidx("4"));
		}
	}
}

void Game::Intro_Getinput(void)
{
	if(keystate2[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
	{
		intro_done = true;
		introduction = false;
	}
}

void Game::Draw_Menuboard(void)
{
	menu_board->Setx(menu_bframe[0]);
	menu_board->Draw(0, 0, 2132, 800);
	menu_board->Setx(menu_bframe[1]);
	menu_board->Draw(0, 0, 2132, 800);

	menu_bframe[0] -= 15;
	menu_bframe[1] -= 15;

	if (menu_bframe[0] < (-2500))
		menu_bframe[0] = menu_bframe[1] + 2132;
	if (menu_bframe[1] < (-2500))
		menu_bframe[1] = menu_bframe[0] + 2132;	
}

void Game::Menu_Getinput(void)
{
	if (keystate2[SDL_GetScancodeFromKey(SDLK_UP)])
		menu_gameover = false;
	if (keystate2[SDL_GetScancodeFromKey(SDLK_DOWN)])
		menu_gameover = true;
	if (keystate2[SDL_GetScancodeFromKey(SDLK_RETURN)])
		mainmenu = false;
}

void Game::Get_Loss(void)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_GetScancodeFromKey(SDLK_y)])
		{
			player->Set_Lives(LIVE);
			ov = 0;
			player_active = 1;
			player_control = 1;
			player->Set_Geassmana(GEASS);
			player->Set_Hits(ONELIVE);
			invulnerability = VOLNERBLE_TIME;
	}
	if (keystate[SDL_GetScancodeFromKey(SDLK_n)])
	{
		menu_gameover = true;
		ov = 0;
	}
}

void Game::Draw_Landscape(void)
{
	for (int window_y = 0; window_y <= 9 ; window_y++)
	{
		for (int window_x = 0; window_x <= 9; window_x++)
		{
			int y_index = (scape_count + (9 - window_y));

			if (y_index > 120 && current_level == 0)
				y_index = ((y_index - 119) + 108);
			if (y_index > 223 && current_level == 0)
				y_index = ((y_index - 223) + 211);
			land->Draw((window_x*100), (((window_y - 1)*100) + sec_scapect), &land_scape[(level[y_index])[window_x]]);
		}
	}
	if(!guide)
		sec_scapect += GAME_SPEED;
	if (sec_scapect > 99)
	{
		sec_scapect = 0;
		scape_count += 1;

		if (scape_count > 120 && current_level == 0)
			scape_count = 110;
		if (scape_count > 223 && current_level == 1)
			scape_count = 213;
		onetime = true;
	}
}

void Increment_Points(int pt1, int pos)
{
	score[(7 - pos)] = score[(7 - pos)] + pt1;
	if (score[(7 - pos)] > 9)
	{
		score[(7 - pos)] -= 10;
		score[(6 - pos)] += 1;
	}
	int cwd = pos;
	while (cwd < 7)
	{
		if (score[(6 - cwd)] > 9)
		{
			score[(6 - cwd)] -= 10;
			score[(5 - cwd)] += 1;
		}
		cwd += 1;
	}
}

void Game::Init_Ground(int xg, int yg, int tg)	//{target, x, y, target_status, target_type, life, shadow_type, pellet time, pellet status, target_type}
{
	int line_idx = 0;
	bool expl_counter = false;
	while (!expl_counter)
	{
		if (groundtar[line_idx][0] == 0)
		{
			groundtar[line_idx][0] = tg;
			groundtar[line_idx][1] = xg;
			groundtar[line_idx][2] = yg;
			if (tg == 2)
			{
				groundtar[line_idx][3] = 3;
			}
			else
				groundtar[line_idx][3] = 0;
			groundtar[line_idx][4] = 0;
			groundtar[line_idx][5] = 40;
			groundtar[line_idx][6] = (2*(tg - 1));
			groundtar[line_idx][7] = 0;
			groundtar[line_idx][8] = 0;
			groundtar[line_idx][9] = tg;
			groundact += 1;
			numgr += 1;		//ground army plus
			expl_counter = true;
		}
		line_idx += 1;
		if (line_idx > 9)
			expl_counter = true;
	}
}

void Game::Draw_Ground(void)
{
	bool boat_flag = false;
	int brgrrr = 0;
	int qugrrr = 0;
	SDL_Rect warp;
	while (qugrrr< numgr)
	{
		if (groundtar[brgrrr][0]>0)
		{
			if (groundtar[brgrrr][0] > 3)
			{
				groundtar[brgrrr][3] = (2 + (groundtar[brgrrr][0] - 4));
				groundtar[brgrrr][6] = (1 + (groundtar[brgrrr][0] - 4));
			}
			if (groundtar[brgrrr][9] == 2)
			{
				boat_flag = true;
			}

			if (groundtar[brgrrr][9] == 1)
				boat_flag = false;
			if (boat_flag)
			{
				warp.h = 166;
				if (groundtar[brgrrr][1]<(-10))
					warp.w = 1;
				else
					warp.w = (groundtar[brgrrr][1]+15);
				warp.x = 0;
				warp.y = 0;
		//mark by boat
				wake->Draw(0, (groundtar[brgrrr][2] - 45), &warp);
				mwake->Draw((groundtar[brgrrr][1] + 10), (groundtar[brgrrr][2] - 45));
				wak->Draw((groundtar[brgrrr][1] - 15), (groundtar[brgrrr][2] - 26), &waks[wf]);
			}
			grshadow->Draw((groundtar[brgrrr][1] + (4 - ((groundtar[brgrrr][9] - 1)*3))), (groundtar[brgrrr][2] + (3 - ((groundtar[brgrrr][9] - 1)*3))), 
				&shadg[(groundtar[brgrrr][6])]);
			tank->Draw(groundtar[brgrrr][1], groundtar[brgrrr][2], &tafr[(groundtar[brgrrr][4])][(groundtar[brgrrr][3])]);

			if (groundtar[brgrrr][8] > 0)
			{
				if (groundtar[brgrrr][8] != 2)
					circ->Draw((groundtar[brgrrr][1] + 100 + (20*(groundtar[brgrrr][9] - 1))), ((groundtar[brgrrr][2] + 30) - (10*(groundtar[brgrrr][9] - 1))), 
						&circc[0 + (2*(groundtar[brgrrr][9] - 1))]);
				else
				{
					Mix_PlayChannel(-1,fifthe,0);
					circ->Draw((groundtar[brgrrr][1] + 100), ((groundtar[brgrrr][2] + 30) - (20*(groundtar[brgrrr][9] - 1))), &circc[1 + (2*(groundtar[brgrrr][9] - 1))]);
					Init_Pellets(((groundtar[brgrrr][1] + 100) + (20*(groundtar[brgrrr][9] - 1))), (groundtar[brgrrr][2] + 30), 2);
				}
				groundtar[brgrrr][8] = groundtar[brgrrr][8] - 1;
			}

			boat_flag = false;
			groundtar[brgrrr][2] += GAME_SPEED;
			groundtar[brgrrr][7] += 1;	// pellets
			if (groundtar[brgrrr][4] == 1)
				groundtar[brgrrr][4] = 0;
			if (groundtar[brgrrr][3] == 0 && groundtar[brgrrr][0] < 4)		//change moving status
				groundtar[brgrrr][3] = 1;
			else
				if (groundtar[brgrrr][3] == 1 && groundtar[brgrrr][0] < 4)
					groundtar[brgrrr][3] = 0;
				else
					groundtar[brgrrr][3] = groundtar[brgrrr][3];

			if ((groundtar[brgrrr][5] < 0 && groundtar[brgrrr][0] < 4) || (geass && geass_counter >= 75 && groundtar[brgrrr][0] < 4))
			{
				if (groundtar[brgrrr][9] == 1)
				{
					Increment_Points(5, 2);
				}
				else
					Increment_Points(6, 2);

				Init_Expl((groundtar[brgrrr][1] - 30),(groundtar[brgrrr][2] - 50));
				if (groundtar[brgrrr][0] == 1)
					groundtar[brgrrr][0] = 4;
				else
					groundtar[brgrrr][0] = 6;
				groundtar[brgrrr][3] = 2;
				groundtar[brgrrr][4] = 0;
				groundact -= 1;
			}	
			if (groundtar[brgrrr][7] == GROUND_PELLET_SHOOTING_SPEED && groundtar[brgrrr][0] < 4)	//init pellets
			{	
				if(player_active == 1)
					groundtar[brgrrr][8] = 3;
				groundtar[brgrrr][7] = 0;				
			}
			if (groundtar[brgrrr][2] > 800)		//disappear time
			{
				if (groundtar[brgrrr][0] < 4)
					groundact -= 1;
				numgr -= 1;
				groundtar[brgrrr][0] = 0;
			}
			if (groundtar[brgrrr][0] < 4)	//x move speed
				groundtar[brgrrr][1] += GAME_SPEED;
			qugrrr += 1;
		}
		brgrrr += 1;
	}
}

void Game::One_Time(void)
{
	for (int scanne = 0; scanne <= 9; scanne++)
	{
		if (level[(scape_count + 9)][scanne] == 6)
		{
			Init_Drum(scanne);
		}
	}
	if (numdrums > 0)
		Check_Drum();	//if disappear
	onetime = 0;
}

void Game::Init_Drum(int that)
{
	int drum_index = 0;
	bool expl_counter = false;
	while (!expl_counter)
	{
		if (drums[drum_index][0] == 0)	//{flag, x, y, life}
		{
			drums[drum_index][0] = 1;
			drums[drum_index][1] = that;
			drums[drum_index][2] = scape_count + 9;
			drums[drum_index][3] = 12;
			numdrums += 1;
			expl_counter = true;
		}
		drum_index += 1;
		if (drum_index > DRUM_CAP - 1)
			expl_counter = true;
	}
}

void Game::Check_Drum(void)
{
	int drum_index = 0;
	int drum_counter = 0;
	while (drum_counter < numdrums)
	{
		if (drums[drum_index][0] == 1)
		{
			if (drums[drum_index][2] < scape_count)
			{
				drums[drum_index][0] = 0;
				numdrums -= 1;
			}
			drum_counter += 1;
		}
		drum_index += 1;
	}
}

void Game::Init_Gunboat(int xbot)
{
	int boat_index = 0;
	bool finished = false;
	while(!finished)
	{
		if (gunb[boat_index][0] == 0)
		{
			gunb[boat_index][0] = 1;
			gunb[boat_index][1] = xbot;
			gunb[boat_index][2] = (-980);
			gunb[boat_index][3] = 0;
			finished = true;
			quantgbt += 1;
			Init_GunboatT((gunb[boat_index][1] + 130), (gunb[boat_index][2] + 570));
			Init_GunboatT((gunb[boat_index][1] + 210), (gunb[boat_index][2] + 570));
			Init_GunboatT((gunb[boat_index][1] + 120), (gunb[boat_index][2] + 480));
			Init_GunboatT((gunb[boat_index][1] + 220), (gunb[boat_index][2] + 480));
			Init_GunboatT((gunb[boat_index][1] + 120), (gunb[boat_index][2] + 380));
			Init_GunboatT((gunb[boat_index][1] + 220), (gunb[boat_index][2] + 380));
			Init_GunboatT((gunb[boat_index][1] + 160), (gunb[boat_index][2] + 250));
		}
		boat_index += 1;
		if (boat_index > 3)
			finished = true;
	}
}

void Game::Init_GunboatT(int tux, int tuy)
{
	int boatt_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (turr[boatt_index][0] == 0)
		{
			turr[boatt_index][0] = 1;
			turr[boatt_index][1] = tux;
			turr[boatt_index][2] = tuy;
			turr[boatt_index][3] = 0;
			turr[boatt_index][4] = 0;
			turr[boatt_index][5] = 0;
			turr[boatt_index][6] = 25;
			turr[boatt_index][7] = 0;
			turr[boatt_index][8] = 1;
			finished = true;
			qutur += 1;
		}
		boatt_index += 1;
		if (boatt_index > TURRET_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Gunboat(void)
{
	int boatt_index = 0;
	int boatt_counter = 0;
	while (boatt_counter < quantgbt)
	{
		if (gunb[boatt_index][0] == 1)
		{
			gboat->Draw(gunb[boatt_index][1], gunb[boatt_index][2]);
			scba->Draw((gunb[boatt_index][1] + 40), (gunb[boatt_index][2] + 720), &qpl[(gunb[boatt_index][3])]);
			if (gunb[boatt_index][3] == 0)
				gunb[boatt_index][3] = 1;
			else
				gunb[boatt_index][3] = 0;
			gunb[boatt_index][2] += 1;
			if (gunb[boatt_index][2] > 820)
			{
				gunb[boatt_index][0] = 0;
				quantgbt -= 1;
			}
			boatt_counter += 1;
		}
		boatt_index += 1;
	}
}

void Game::Init_Air(int ax, int ay, int tar, int pt)
{
	bool finished = false;
	int air_index =0;
	while (!finished)
	{
		if (alienstats[air_index][0] == 0)
		{
			alienstats[air_index][0] = tar;	//type
			alienstats[air_index][1] = ax;	//x
			alienstats[air_index][2] = ay;	//y
			alienstats[air_index][3] = 0;	//counter
			alienstats[air_index][4] = atpattern[0][3];
			alienstats[air_index][5] = 3;
			alienstats[air_index][7] = 0;	//moving counter
			alienstats[air_index][8] = atpattern[0][4];
			alienstats[air_index][9] = 0;	//shooting counter
			alienstats[air_index][11] = 60;
			if (tar == 1)
			{
				alienstats[air_index][14] = 0;	//wrap start
				alienstats[air_index][15] = 3;	//wrap end
				alienstats[air_index][13] = 20;	//life
				alienstats[air_index][10] = 110;	//x dir check(length of x - 15)
				alienstats[air_index][17] = 66;	//x plus
				alienstats[air_index][18] = 66;	//y plus
				alienstats[air_index][19] = 66;	//radius
			}
			else
			{
				if (tar == 2)
				{
					alienstats[air_index][14] = 4;
					alienstats[air_index][15] = 4;
					alienstats[air_index][13] = 15;
					alienstats[air_index][10] = 100;
					alienstats[air_index][17] = 66;
					alienstats[air_index][18] = 36;
					alienstats[air_index][19] = 54;
				}
				else
				{
					alienstats[air_index][14] = 5;
					alienstats[air_index][15] = 8;
					alienstats[air_index][13] = 10;
					alienstats[air_index][10] = 70;
					alienstats[air_index][17] = 40;
					alienstats[air_index][18] = 40;
					alienstats[air_index][19] = 40;
				}
			}
			alienstats[air_index][6] = alienstats[air_index][14];	//wrap counter
			alienstats[air_index][16] = pt;	//moving type

			alienqun += 1;
			finished = true;
		}
		air_index += 1;
		if (air_index > AIR_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Air(void)
{
	int air_counter = 0;
	int air_index = 0;
	while (air_counter < alienqun)
	{
		if (alienstats[air_index][0] != 0)
		{
			alienstuff->Draw(alienstats[air_index][1], alienstats[air_index][2], &aliens[(alienstats[air_index][12])][(alienstats[air_index][6])]);
			if (alienstats[air_index][15] > alienstats[air_index][14])
				alienstats[air_index][6] += 1;
			alienstats[air_index][1] += ((atpattern[(alienstats[air_index][16])][((alienstats[air_index][7]*5) + 1)]));
			alienstats[air_index][2] += ((atpattern[(alienstats[air_index][16])][((alienstats[air_index][7]*5) + 2)]));
			alienstats[air_index][3] += 1;
			if (alienstats[air_index][12] == 1)	
				alienstats[air_index][12] = 0;
			if (alienstats[air_index][13] < 0 || (geass && geass_counter >= 75))
			{
				if (alienstats[air_index][0] == 1)
					Increment_Points(3, 2);
				if (alienstats[air_index][0] == 2)
					Increment_Points(3, 2);
				if (alienstats[air_index][0] == 3)
					Increment_Points(2, 2);
				Init_Expl((alienstats[air_index][1] - 50 - ((alienstats[air_index][0] - 1)*20)), ((alienstats[air_index][2] - 50) - ((alienstats[air_index][0] - 1)*30)));
				alienstats[air_index][0] = 0;
				alienqun -= 1;
			}
			if (alienstats[air_index][0] != 0 && player_active == 1 && invulnerability == 0)
			{
				bool coll = Collide((alienstats[air_index][1] + alienstats[air_index][17]), (alienstats[air_index][2] + alienstats[air_index][18]), 
					alienstats[air_index][19]);
				if (coll == true)
				{
					player->Set_Hits(player->Get_Hits() - PELLET_DAMAGE);
					alienstats[air_index][12] = 1;	//being hit
					alienstats[air_index][13] -= 1;
				}
			}
			if (alienstats[air_index][3] == atpattern[(alienstats[air_index][16] + 1)][((alienstats[air_index][7]*5) + alienstats[air_index][9])])
			{
				Mix_PlayChannel(1, bitbos, 0);
				Mix_Volume(1, 80);
				Init_Pellets((alienstats[air_index][1] + 40), (alienstats[air_index][2] + 40), 0);
				alienstats[air_index][9] += 1;
			} 

			if (alienstats[air_index][3] > (atpattern[(alienstats[air_index][16])][(alienstats[air_index][7]*5)]))
			{
				alienstats[air_index][3] = 0;
				alienstats[air_index][7] += 1;
				alienstats[air_index][9] = 0;
			}
			if (alienstats[air_index][6] > alienstats[air_index][15])
				alienstats[air_index][6] = alienstats[air_index][14];
			if (alienstats[air_index][7] > 3)	
			{
				for (int kw = 0; kw <= 19; kw++)
				{
					alienstats[air_index][kw] = 0;
				}
				alienqun -= 1;
			}
			air_counter += 1;
		}
		air_index += 1;
	}
}

void Game::Init_Air2(int ax, int ay, int ty, int pa)
{
	int air_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (aliencl[air_index][0] == 0)
		{
			aliencl[air_index][0] = ty;	//type
			aliencl[air_index][1] = ax;	//x
			aliencl[air_index][2] = ay;	//y
			aliencl[air_index][3] = 0;	//counter
			aliencl[air_index][4] = 0;	//moving counter
			aliencl[air_index][5] = pa;	//moving type
			aliencl[air_index][8] = 0;	//wrap counter
			aliencl[air_index][12] = 0;	//being hit
			aliencl[air_index][13] = 0;	//shoot flag
			aliencl[air_index][20] = 0;	//shooting counter
			aliencl[air_index][21] = 0;	//if shoot
			if (ty == 1)
			{
				aliencl[air_index][6] = 0;	//wrap start
				aliencl[air_index][7] = 3;	//wrap end
				aliencl[air_index][9] = 100;
				aliencl[air_index][10] = 90;
				aliencl[air_index][11] = 15;	//life
				aliencl[air_index][14] = 1;	//gfire wrap end
				aliencl[air_index][15] = 0;	//gfire counter
				aliencl[air_index][16] = 62;	//gfire x wrap
				aliencl[air_index][17] = 17;	//gfire x wrap
				aliencl[air_index][18] = 82;	//gfire y wrap
				aliencl[air_index][19] = 0;	//gfire wrap start
				aliencl[air_index][22] = 67;	//x plus
				aliencl[air_index][23] = 63;	//y plus
				aliencl[air_index][24] = 65;	//radius
				numhells += 1;
			}
			if (ty == 2)
			{
				aliencl[air_index][6] = 4;
				aliencl[air_index][7] = 4;
				aliencl[air_index][8] = 4;
				aliencl[air_index][9] = 120;
				aliencl[air_index][10] = 95;
				aliencl[air_index][11] = 25;
				aliencl[air_index][14] = 8;
				aliencl[air_index][15] = 5;
				aliencl[air_index][16] = 28;
				aliencl[air_index][17] = 0;
				aliencl[air_index][18] = 90;
				aliencl[air_index][19] = 5;
				aliencl[air_index][22] = 56;
				aliencl[air_index][23] = 66;
				aliencl[air_index][24] = 59;
			}
			if (ty == 3)
			{
				aliencl[air_index][6] = 5;
				aliencl[air_index][7] = 7;
				aliencl[air_index][9] = 200;
				aliencl[air_index][10] = 140;
				aliencl[air_index][11] = 45;
				aliencl[air_index][14] = 4;
				aliencl[air_index][15] = 2;
				aliencl[air_index][16] = 59;
				aliencl[air_index][17] = 23;
				aliencl[air_index][18] = 190;
				aliencl[air_index][19] = 2;
				aliencl[air_index][22] = 89;
				aliencl[air_index][23] = 110;
				aliencl[air_index][24] = 90;
			}

			finished = true;
			numal2 += 1;
		}
		air_index += 1;
		if (air_index > 23)
			finished = true;
	}

}

void Game::Draw_Air2(void)
{
	int air_counter = 0;
	int air_index = 0;
	while (air_counter < numal2)
	{
		if (aliencl[air_index][0] > 0)
		{
			if (aliencl[air_index][13] != 0)
			{
				gfire->Draw((aliencl[air_index][1] + aliencl[air_index][16] + aliencl[air_index][17]), ((aliencl[air_index][2] + aliencl[air_index][18] - 5)), 
					&gff[aliencl[air_index][15]]);
				gfire->Draw((aliencl[air_index][1] + (aliencl[air_index][16] - aliencl[air_index][17])), ((aliencl[air_index][2] + aliencl[air_index][18] - 5)), 
					&gff[aliencl[air_index][15]]);
				if (aliencl[air_index][15] == aliencl[air_index][14] && aliencl[air_index][0] != 2)
				{
					Init_Lazer((aliencl[air_index][1] + aliencl[air_index][16] + aliencl[air_index][17]), ((aliencl[air_index][2] + (aliencl[air_index][18]))), 
						aliencl[air_index][0] - 1);
					Init_Lazer((aliencl[air_index][1] + (aliencl[air_index][16] - aliencl[air_index][17])), ((aliencl[air_index][2] + (aliencl[air_index][18]))), 
						aliencl[air_index][0] - 1);
					aliencl[air_index][15] -= 1;
					aliencl[air_index][21] = 1;
				}
				if (aliencl[air_index][15] == aliencl[air_index][14] && aliencl[air_index][0] == 2 && aliencl[air_index][21] == 0)
				{
					Init_Lightning((aliencl[air_index][1] + aliencl[air_index][16]), (aliencl[air_index][2] + aliencl[air_index][18]));
					aliencl[air_index][15] -= 1;
					aliencl[air_index][21] = 1;
				}
				if (aliencl[air_index][15] < aliencl[air_index][14] && aliencl[air_index][21] == 0)
					aliencl[air_index][15] += 1;
				if (aliencl[air_index][21] == 1)
					aliencl[air_index][15] -= 1;
				if (aliencl[air_index][15] < aliencl[air_index][19] && aliencl[air_index][21] == 1)	//reset gfire
				{
					aliencl[air_index][15] += 1;
					aliencl[air_index][13] = 0;
					aliencl[air_index][21] = 0;
				}
			}
			int juws = 0;
			aliencl2->Draw(aliencl[air_index][1], aliencl[air_index][2], &clalfr[(aliencl[air_index][12])][(aliencl[air_index][8])]);
			if (aliencl[air_index][0] != 2)
				aliencl[air_index][8] += 1;
			aliencl[air_index][1] += (atpattern[(aliencl[air_index][5])][((aliencl[air_index][4]*5) + 1)]);
			aliencl[air_index][2] += (atpattern[(aliencl[air_index][5])][((aliencl[air_index][4]*5) + 2)]);
			aliencl[air_index][3] += 1;
			if (aliencl[air_index][12] == 1)
				aliencl[air_index][12] = 0;
			if (aliencl[air_index][3] == (atpattern[(aliencl[air_index][5] + 1)][(((aliencl[air_index][4])*5) + aliencl[air_index][20])]))
			{
				if (aliencl[air_index][0] == 2)
					Mix_PlayChannel(-1, zap, 0);
				if (aliencl[air_index][0] == 3)
				{
					Mix_PlayChannel(3, biglazer, 0);
					Mix_PlayChannel(2, biglazer, 0);
					Mix_Volume(2,128);
					Mix_Volume(3,128);
				}
				if (aliencl[air_index][0] == 1 && hgunct < 1)
				{
					Mix_PlayChannel(-1, heligun, 0);
					hgunct = 10;
				}
				aliencl[air_index][13] = 1;
				aliencl[air_index][20] += 1;
			}
			if (player_active == 1 && invulnerability == 0)
			{
				bool coll = Collide((aliencl[air_index][1] + aliencl[air_index][22]), (aliencl[air_index][2] + aliencl[air_index][23]), aliencl[air_index][24]);
				if (coll == true)
				{
					player->Set_Hits(player->Get_Hits() - PELLET_DAMAGE);
					aliencl[air_index][12] = 1;
					aliencl[air_index][11] -= 1;
				}
			}
	
			if (aliencl[air_index][3] > (atpattern[(aliencl[air_index][5])][((aliencl[air_index][4])*5)]))
			{
				aliencl[air_index][3] = 0;
				aliencl[air_index][4] += 1;
				aliencl[air_index][20] = 0;
			}
			if (aliencl[air_index][8] > aliencl[air_index][7])
				aliencl[air_index][8] = aliencl[air_index][6];
			if (aliencl[air_index][4] > 3)
			{
				if (aliencl[air_index][0] == 1)
					numhells -= 1;
				for (int kw2 = 0; kw2 <= 12; kw2++)
				{
					aliencl[air_index][kw2] = 0;
				}
				numal2 -= 1;
				juws = 1;
			}
			if ((aliencl[air_index][11] < 0 && juws == 0) || (geass && geass_counter >= 75  && juws == 0))
			{
				if 	(aliencl[air_index][0] < 3)
					Init_Expl((aliencl[air_index][1] - 30), (aliencl[air_index][2] - 30));
				else
					Init_Expl(aliencl[air_index][1], aliencl[air_index][2]);
				if (aliencl[air_index][0] == 1)
					Increment_Points(5, 2);
				if (aliencl[air_index][0] == 2)
					Increment_Points(7, 2);
				if (aliencl[air_index][0] == 3)
					Increment_Points(1, 3);
				for (int kw2 = 0; kw2 <= 24; kw2++)
				{
					aliencl[air_index][kw2] = 0;
				}
				if (aliencl[air_index][0] == 1)
					numhells -= 1;
				numal2 -= 1;
			}
			air_counter += 1;
		}
		air_index += 1;
	}
}

void Game::Init_Lazer(int lzzx, int lzzy, int lzzt)
{
	int lazer_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (allz[lazer_index][0] == 0)
		{
			allz[lazer_index][0] = 1;
			allz[lazer_index][1] = lzzx;
			allz[lazer_index][2] = lzzy;
			allz[lazer_index][3] = lzzt;
			allz[lazer_index][4] = 0;
			quantlz += 1;
			finished = true;
		}
		lazer_index += 1;
		if (lazer_index > LAZER_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Lazer(void)
{
	int lazer_index = 0;
	int lazer_counter = 0;
	while (lazer_counter < quantlz)
	{
		if (allz[lazer_index][0] == 1)
		{
			alienla->Draw(allz[lazer_index][1], allz[lazer_index][2], &lazz[(allz[lazer_index][3])]);
			allz[lazer_index][2] += LAZER_SPEED;
			bool ret = false;
			if (allz[lazer_index][4] == 0 && player_active == 1 && invulnerability == 0)
			{
				ret = Checklz(allz[lazer_index][1], allz[lazer_index][2], allz[lazer_index][3]);
			}
			if (ret == true)
			{
				allz[lazer_index][4] = 1;
				allz[lazer_index][0] = 0;
				quantlz -= 1;
			}
			if (allz[lazer_index][2] > 805)
			{
				allz[lazer_index][0] = 0;
				quantlz -= 1;
			}
			lazer_counter += 1;
		}
		lazer_index += 1;
	}
}

bool Game::Checklz(int stmx, int stmy, int stty)
{
	bool chkbck = false;
	int piedl = stty;
	int x = player->Get_Sprite()->Getx();
	if (stmx > (player->Get_Sprite()->Getx() + 10) && stmx < (player->Get_Sprite()->Getx() + 100))
	{
		if ((stmy + (50 + (piedl*25))) > player->Get_Sprite()->Gety() && (stmy - (60 + (10*piedl))) < player->Get_Sprite()->Gety())
		{
			chkbck = true;
			player->Set_Hits(player->Get_Hits() - (piedl + 1));
			Initlzhit((stmx - 20), ((player->Get_Sprite()->Gety() + 20) - (10*piedl)), piedl);
		}
	}
	return chkbck;
}

void Game::Initlzhit(int lzhx, int lzhy, int lzht)
{
	int lsp_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (bloss[lsp_index][0] == 0)
		{
			bloss[lsp_index][0] = 1;
			bloss[lsp_index][1] = lzhx;
			bloss[lsp_index][2] = lzhy;
			if (lzht == 2)
				bloss[lsp_index][3] = 0;
			else
				bloss[lsp_index][3] = 6;
			bloss[lsp_index][4] = bloss[lsp_index][3];
			finished = true;
			quanhz += 1;
		}
		lsp_index += 1;
		if (lsp_index > 9)
			finished = true;
	}
}

void Game::Drawlzhit(void)
{
	int lsp_index =0;
	int lsp_counter = 0;
	while (lsp_counter < quanhz)
	{
		if (bloss[lsp_index][0] == 1)
		{
			blos->Draw(bloss[lsp_index][1], bloss[lsp_index][2], &hfr[(bloss[lsp_index][4])]);

			bloss[lsp_index][4] += 1;
			if (bloss[lsp_index][4] > (bloss[lsp_index][3] + 5))
			{
				bloss[lsp_index][0] = 0;
				quanhz -= 1;
			}
			lsp_counter += 1;
		}
		lsp_index += 1;
	}
}

void Game::Init_Lightning(int ligx, int ligy)
{
	int ln_index = 0;
	bool finished = false;
	while(!finished)
	{
		if (bolt[ln_index][0] == 0)
		{
			bolt[ln_index][0] = 1;
			bolt[ln_index][1] = (ligx - 20);
			bolt[ln_index][2] = ligy;
			bolt[ln_index][3] = 0;
			bolt[ln_index][4] = 0;
			finished = true;
			numlight += 1;
		}
		ln_index += 1;
		if (ln_index > LIGHTNING_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Lightning(void)
{
	int ln_counter = 0;
	int ln_index = 0;
	while (ln_counter < numlight)
	{
		if (bolt[ln_index][0] == 1)
		{
			SDL_Rect portll;
			portll.x = 0;
			portll.y = bolt[ln_index][3];
			portll.h = 120;
			portll.w = 100;
			electricity->Draw(bolt[ln_index][1], (bolt[ln_index][2] + bolt[ln_index][3]), &portll);
			bool blht = false;
			if (bolt[ln_index][4] == 0)
			{
				blht = Checkln(bolt[ln_index][1], (bolt[ln_index][2] + bolt[ln_index][3]));
			}
			if (blht == true)
			{
				bolt[ln_index][4] = 1;
				bolt[ln_index][0] = 0;
				numlight -= 1;
			}
			bolt[ln_index][3] += LIGHTNING_SPEED;
			
			if ((bolt[ln_index][3] + bolt[ln_index][2]) > 800)
			{
				bolt[ln_index][0] = 0;
				numlight -= 1;
			}
			ln_counter += 1;
		}
		ln_index += 1;
	}
}

bool Game::Checkln(int chcxx, int chcyy)
{
	bool ret = false;

	if (chcxx > (player->Get_Sprite()->Getx() - 40) && chcxx < (player->Get_Sprite()->Getx() + 85))
	{
		if ((chcyy + 200) > (player->Get_Sprite()->Gety() - 20) && (chcyy - 20) < (player->Get_Sprite()->Gety() + 110))
		{
			schmhit = 2;
			player->Set_Hits(player->Get_Hits() - LIGHTNING_DAMAGE);
			ret = true;
			Init_Sp((chcxx - 10), player->Get_Sprite()->Gety());
		}
	}
	return ret;
}

void Game::Init_Sp(int xspq, int yspq)
{
	int lsp_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (sprk[lsp_index][0] == 0)
		{
			sprk[lsp_index][0] = 1;
			sprk[lsp_index][1] = xspq;
			sprk[lsp_index][2] = yspq;
			sprk[lsp_index][3] = 0;
			numspk += 1;
			finished = true;
		}
		lsp_index += 1;
		if (lsp_index > LIGHTNING_SPLIT_CAP - 1)
			finished = true;
	}
}


void Game::Draw_Sp(void)
{
	int lsp_index = 0;
	int lsp_counter = 0;
	while (lsp_counter < numspk)
	{
		if (sprk[lsp_index][0] == 1)
		{
			hitter->Draw(sprk[lsp_index][1], sprk[lsp_index][2], &spkl[(sprk[lsp_index][3])]);
			sprk[lsp_index][3] += 1;
			if (sprk[lsp_index][3] > 5)
			{
				sprk[lsp_index][0] = 0;
				numspk -= 1;
			}
			lsp_counter += 1;
		}
		lsp_index += 1;
	}
}

void Game::Init_Turret(int tux, int tuy)
{
	bool expl_counter = false;
	int tur_index = 0;
	while (!expl_counter)
	{
		if (turr[tur_index][0] == 0)	//{flag, x, y, change dir time, during wrap status, expl_counter wrap status, life, if being hit, disappear}
		{
			turr[tur_index][0] = 1;
			turr[tur_index][1] = (tux*100);
			turr[tur_index][2] = (-100);
			turr[tur_index][3] = 0;
			turr[tur_index][4] = 0;
			turr[tur_index][5] = 0;
			turr[tur_index][6] = 25;
			turr[tur_index][7] = 0;
			turr[tur_index][8] = 0;
			expl_counter = true;
			qutur += 1;
		}
		tur_index += 1;
		if (tur_index > TURRET_CAP - 1)
			expl_counter = true;
	}
}

void Game::Draw_Turret(void)
{
	int tur_index = 0;
	int tur_counter = 0;
	while (tur_counter < qutur)
	{
		if (turr[tur_index][0] == 1)
		{
			if (turr[tur_index][3] == TURRET_PELLET_SHOOTING_SPEED && turr[tur_index][2] < 800 && turr[tur_index][2] > (-100))
			{
				if (player_active == 1)
				{
					Mix_PlayChannel(6, artil, 0);
					Mix_Volume(6, 70);
					Turret_Shoot((turr[tur_index][1] + 50), (turr[tur_index][2] + 50), (turr[tur_index][4]));
				}

				turr[tur_index][3] = 0;
			}
			turret->Draw(turr[tur_index][1], turr[tur_index][2], &turretfr[(turr[tur_index][7])][((turr[tur_index][4]))]);
			if (turr[tur_index][7] == 1)
				turr[tur_index][7] = 0;
			if(turr[tur_index][3] >= TURRET_PELLET_SHOOTING_SPEED)
				turr[tur_index][3] = 0;
			turr[tur_index][3] += 1;
			if ((turr[tur_index][6] < 0) || (geass && geass_counter >= 75 && turr[tur_index][2] > -100))
			{
				turr[tur_index][0] = 0;
				Increment_Points(3, 2);
				Init_Expl((turr[tur_index][1] - 70), (turr[tur_index][2] - 70));
				qutur -= 1;
			}

			double mpwo = (player->Get_Sprite()->Getx() - turr[tur_index][1]);
			double mpww = (player->Get_Sprite()->Gety() - turr[tur_index][2]);
			if (mpwo < 0)
				mpwo = mpwo*(-1);
			if (mpww < 0)
				mpww = mpww*(-1);
			if (mpwo == 0)
				mpwo = 0.01;
			double tuww = (mpww/mpwo);
			double uipe = atan(tuww);
			uipe = uipe * 12;
			uipe = uipe /(3.14159);
			if (player->Get_Sprite()->Getx() < turr[tur_index][1] && player->Get_Sprite()->Gety() < turr[tur_index][2])
				turr[tur_index][5] = (6 + uipe);
			if (player->Get_Sprite()->Getx() < turr[tur_index][1] && player->Get_Sprite()->Gety() > turr[tur_index][2])
				turr[tur_index][5] = (6 - uipe);
			if (player->Get_Sprite()->Getx() > turr[tur_index][1] && player->Get_Sprite()->Gety() > turr[tur_index][2])
				turr[tur_index][5] = (18 + uipe);
			if (player->Get_Sprite()->Getx() > turr[tur_index][1] && player->Get_Sprite()->Gety() < turr[tur_index][2])
				turr[tur_index][5] = (18 - uipe);
			if (turr[tur_index][4] != turr[tur_index][5])
			{				
				if (turr[tur_index][5] > turr[tur_index][4] && (turr[tur_index][5] - turr[tur_index][4]) < 12)
					turr[tur_index][4] += 1;
				if (turr[tur_index][5] > turr[tur_index][4] && (turr[tur_index][5] - turr[tur_index][4]) > 12)
					turr[tur_index][4] -= 1;
				if (turr[tur_index][5] < turr[tur_index][4] && (turr[tur_index][4] - turr[tur_index][5]) < 12)
					turr[tur_index][4] -= 1;
				if (turr[tur_index][5] < turr[tur_index][4] && (turr[tur_index][4] - turr[tur_index][5]) > 12)
					turr[tur_index][4] += 1;
			}
			if (turr[tur_index][4] < 0)
				turr[tur_index][4] = 23;
			if (turr[tur_index][4] > 23)
				turr[tur_index][4] = 0;
			if (turr[tur_index][2] > 800)
			{
				turr[tur_index][0] = 0;
				qutur -= 1;
			}
			turr[tur_index][2] = turr[tur_index][2] + (2 - (turr[tur_index][8]));	//y move
			tur_counter += 1;
		}
		tur_index += 1;
	}
}

void Game::Turret_Shoot(int tur_x, int tur_y, int angle)
{
	double dis = 0;
	int angle_dis = 0;
	int tur_status = 0;
	if (angle >= 0 && angle < 6)
	{
		angle_dis = 6 - angle;
		tur_status = 1;
	}
	if (angle >= 6 && angle < 12)
	{
		angle_dis = angle - 6;
		tur_status = 2;
	}
	if (angle >= 12 && angle < 18)
	{
		angle_dis = 18 - angle;
		tur_status = 3;
	}
	if (angle >= 18)
	{
		angle_dis = angle - 18;
		tur_status = 4;
	}
	dis = angle_dis*(3.14159);
	dis = dis/12;
	int mcwx = 0;
	int mxwy = 0;
	int dddx = (60*cos(dis));
	int dddy = (60*sin(dis));
	if (dddx < 0)
		dddx = dddx*(-1);
	if (dddy < 0)
		dddy = dddy*(-1);
	int uix = (dddx/10);
	int uiy = (dddy/10);
	if (tur_status == 1)
	{
		mcwx = tur_x - dddx;
		mxwy = tur_y + dddy;
		uix = uix*(-1);
	}
	if (tur_status == 2)
	{
		mcwx = tur_x - dddx;
		mxwy = tur_y - dddy;
		uix = uix*(-1);
		uiy = uiy*(-1);
	}
	if (tur_status == 3)
	{
		mcwx = tur_x + dddx;
		mxwy = tur_y - dddy;
		uiy = uiy*(-1);
	}
	if (tur_status == 4)
	{
		mcwx = tur_x + dddx;
		mxwy = tur_y + dddy;
	}
	Init_Muzflash((mcwx-30), (mxwy-30));
	Beg_Shell((mcwx-15), (mxwy-15), uix, uiy);
}

void Game::Init_Muzflash(int mfx, int mfy)
{
	int fl_index = 0;
	bool expl_counter = false;
	while (!expl_counter)
	{
		if (muf[fl_index][0] == 0)
		{
			muf[fl_index][0] = 1;
			muf[fl_index][1] = mfx;
			muf[fl_index][2] = mfy;
			muf[fl_index][3] = 0;
			expl_counter = true;
			qumzfl += 1;

		}
		fl_index += 1;
		if (fl_index > 9)
			expl_counter = true;
	}
}

void Game::Beg_Shell(int begs, int begy, int dhsx, int dhsy)
{
	int brsh_index = 0;
	bool expl_counter = false;
	while (!expl_counter)
	{
		if (pellets[brsh_index][0] == 0)
		{
			pellets[brsh_index][0] = 1;
			pellets[brsh_index][1] = begs;
			pellets[brsh_index][2] = begy;
			pellets[brsh_index][3] = 1;
			pellets[brsh_index][4] = dhsx;
			pellets[brsh_index][5] = dhsy;
			expl_counter = true;
			quanpel += 1;
		}
		brsh_index += 1;
		if (brsh_index > PELLET_CAP - 1)
			expl_counter = true;
	}
}

void Game::Init_Pellets(int px, int py, int pt)
{
	bool expl_counter = false;
	int plbr = 0;
	int quad = 0;
	int p_x = player->Get_Sprite()->Getx() + 40;
	int p_y = player->Get_Sprite()->Gety() + 20;
	double pir = 3.14159;
	while (!expl_counter)
	{
		if (pellets[plbr][0] == 0)
		{
			pellets[plbr][0] = 1;
			pellets[plbr][1] = px;
			pellets[plbr][2] = py;
			pellets[plbr][3] = pt;
			double dpx = 0;
			double dpy = 0;
			dpx = px - p_x;
			if (dpx < 0)
				dpx = dpx*(-1);
			dpy = py - p_y;
			if (dpy < 0)
				dpy = dpy*(-1);
			double tan = atan(dpy/dpx);
			double tann = (tan*180);
			double tannn = (tann/3.14159);
			double dipp = (tannn*3.14159);
			dipp = dipp/180;
			if (pt == 3)
			{
				pellets[plbr][4] = ((PELLET_SPEED+2)*(cos(dipp)));
				pellets[plbr][5] = ((PELLET_SPEED+2)*(sin(dipp)));
			}
			else
			{
				pellets[plbr][4]= (PELLET_SPEED*(cos(dipp)));
				pellets[plbr][5]= (PELLET_SPEED*(sin(dipp)));
			}
			if (px > p_x && pellets[plbr][4] >= 0)
				pellets[plbr][4] = pellets[plbr][4] * (-1);
			if (px < p_x && pellets[plbr][4] < 0)
				pellets[plbr][4] = pellets[plbr][4] * (-1);
			if (py < p_y && pellets[plbr][5] < 0)
				pellets[plbr][5] = pellets[plbr][5] * (-1);
			if (py > p_y && pellets[plbr][5] >= 0)
				pellets[plbr][5] = pellets[plbr][5] * (-1);
			expl_counter = true;
			quanpel += 1;
		}
		plbr += 1;
		if (plbr > PELLET_CAP - 1)
			expl_counter = true;
	}
}

void Game::Draw_Muzflash(void)
{
	int mz_index = 0;
	int mz_counter = 0;
	while (mz_counter < qumzfl)
	{
		if (muf[mz_index][0] == 1)
		{
			muflash->Draw(muf[mz_index][1], muf[mz_index][2], &mffr[(muf[mz_index][3])]);
				muf[mz_index][3] += 1;
			if (muf[mz_index][3] > 2)
			{
				muf[mz_index][0] = 0;
				muf[mz_index][1] = 0;
				muf[mz_index][2] = 0;
				muf[mz_index][3] = 0;
				qumzfl -= 1;
			}
			mz_counter += 1;
		}
		mz_index += 1;
	}
}

void Game::Draw_Pellets(void)
{
	int pelb = 0;
	int pelq = 0;
	int pire = 3.14159;
	bool expl_counter = false;

	while (!expl_counter)
	{
		if (pellets[pelb][0] == 1)
		{
			pellet->Draw(pellets[pelb][1], pellets[pelb][2], &pelltt[(pellets[pelb][3])]);
			if (pfr == 0)
				pfr = 1;
			else 
				pfr = 0;
			if (pellets[pelb][3] == 2)
				pellets[pelb][3] = 3;
			else
				if (pellets[pelb][3] == 3)
					pellets[pelb][3] = 2;
				else
					pellets[pelb][3] = pellets[pelb][3];
			pellets[pelb][1] = pellets[pelb][1] + pellets[pelb][4];
			pellets[pelb][2] = pellets[pelb][2] + pellets[pelb][5];

			int term = 0;
			if (pellets[pelb][1] > 1020)
				term = 1;
			if (pellets[pelb][1] < (-20))
				term = 1;
			if (pellets[pelb][2] > 810)
				term = 1;
			if (pellets[pelb][2] < (-30))
				term = 1;
			if (player_active == 1 && invulnerability == 0)
			{
				bool tiwn = (Hit_Player((pellets[pelb][1] + 9), (pellets[pelb][2] + 9), 9));
				if (tiwn)
				{
					pellets[pelb][0] = 0;	//set disappear
					if (pellets[pelb][3] == 3)
						pellets[pelb][3] -= 1; 
					Init_Split(pellets[pelb][1], pellets[pelb][2], pellets[pelb][3]);
					schmhit = 2;
					player->Set_Hits(player->Get_Hits() - (pellets[pelb][3] + 1));;
				}
			}	
			if (term == 1)
			{
				pellets[pelb][0] = 0;
				quanpel -= 1;
			}
			pelq += 1;
		}
		if (pelq >= quanpel)
			expl_counter = true;
		pelb += 1;
		if (pelb > PELLET_CAP - 1)
			expl_counter = true;
	}
}

void Game::Draw_Player(void)
{
	player->Draw(&schmetfr[(schmhit + invm)][player->Get_Status()]);
	tail->Draw(player->Get_Sprite()->Getx() + 41, player->Get_Sprite()->Gety() + 65, &pipe[pe]);

	if (schmhit > 0)
		schmhit -= 1;
	if (player->Get_Hits() == 0)
	{
		Init_Playerexpl((player->Get_Sprite()->Getx() - 10), (player->Get_Sprite()->Gety() - 20));
		player_active = 0;
		player->Set_Firestatus(0);
		if (player->Get_Lives() > 0)
			respawncounter = RENEW_TIME;
	}
	if (pe >= 2)
		player_dir = 1;
	if (pe <= 0)
		player_dir = 0;
	if (player_dir == 0)
		pe = pe + 1;
	else
		pe = pe - 1;
}

void Game::Attack(void)
{
	gunf->Draw((player->Get_Sprite()->Getx() + 35), (player->Get_Sprite()->Gety()), &fg[(player->Get_Firestatus() - 1)]);
	gunf->Draw((player->Get_Sprite()->Getx() + 70), (player->Get_Sprite()->Gety()), &fg[(player->Get_Firestatus() - 1)]);

	if (gun_attack < 1)
	{
		Mix_PlayChannel(-1, machinegun, 0);
		gun_attack = 6;
	}
	if (player->Get_Firestatus() == 2)
	{
		Init_Streak((player->Get_Sprite()->Getx() + 32), player->Get_Sprite()->Gety());
		Init_Streak((player->Get_Sprite()->Getx() + 65), player->Get_Sprite()->Gety());
	}

	player->Set_Firestatus(player->Get_Firestatus() - 1);
	if (player->Get_Firestatus() == 0 && player->Get_Shoot() == 1)
		player->Set_Firestatus(2);
}

void Game::Geass(void)
{
	if(geass_counter <= 55)
	{
		invulnerability = VOLNERBLE_TIME;
		geass->Draw(250, 150, &geas[geass_counter/3]);
	}
	else if(geass_counter > 80)
	{
		player->Set_Geass(false);
		geass_counter = 0;
	}
	else
	{
		geass_icon->Draw(200, 100, &geasi[icon_counter/2]);
		if(icon_counter > 5)
			icon_dir = 1;
		if(icon_counter < 0)
			icon_dir = 0;
		if(icon_dir)
			icon_counter--;
		if(!icon_dir)
			icon_counter++;
	}

	geass_counter++;
}

void Game::Draw_HM(void)
{
	slot->Draw(10, 10);
	hpmp->Draw(168, 80, &mp[player->Get_Geassmana()]);
	hpmp->Draw(168, 37, &hp[player->Get_Hits()]);
}

void Game::Draw_Lives(void)
{
	heart->Draw(20, 730, &hrt[player->Get_Lives() - 1]);
}

void Game::Draw_Points(void)
{
	for (int i = 0; i <= 7; i++)
		points->Draw((650 + (i*40)), 730, &pts[(score[i])]);
}

bool Game::Hit_Player (int hitpx, int hitpy, int prox)
{
	int xchp = (player->Get_Sprite()->Getx() + 62);
	int ychp = (player->Get_Sprite()->Gety() + 50);
	double tmp = (hitpx - xchp);
	tmp = tmp*tmp;
	double tmp2 = (hitpy - ychp);
	tmp2 = tmp2*tmp2;
	double tmp3 = (sqrt(tmp + tmp2));
	return (tmp3 < (prox + HIT_RANGE));
}

void Game::Init_Playerexpl(int pexx, int pexy)
{
	Mix_PlayChannel(7, playerblow, 0);
	Mix_Volume(7, 50);
	pexp[0] = 0;
	pexp[1] = pexx;
	pexp[2] = pexy;
	explopr = 1;
}

void Game::Draw_Playerexpl(void)
{
	pexplo->Draw(pexp[1], pexp[2], &pex[(pexp[0])]);
	pexp[0] += 1;
	if (pexp[0] > 12)
	{
		explopr = 0;
		player->Set_Lives(player->Get_Lives() - 1); 
		if (player->Get_Lives() == 0)
		{
			ov = 1;
			respawncounter = 0;
			pripro = 5;
			procounter = 10;
		}
	}
}

void Game::Init_Split(int splx, int sply, int splt)
{
	bool finished = false;
	int split_index = 0;
	while (!finished)
	{
		if (splitct[split_index][0] == 0)	//{flag, x, y, wrap, type}
		{
			splitct[split_index][0] = 1;
			splitct[split_index][1] = splx;
			splitct[split_index][2] = sply;
			if (splt == 2)
				splitct[split_index][3] = ((splt - 1)*8);
			else
				splitct[split_index][3] = (splt*8);
			if (splt == 4)
				splitct[split_index][3] = 0;
			splitct[split_index][4] = splt;
			finished = true;
			quanspt += 1;
		}
		split_index += 1;
		if (split_index > SPLIT_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Split(void)
{
	int split_counter = 0;
	int split_index = 0;
	while (split_counter < quanspt)
	{
		if (splitct[split_index][0] == 1)
		{
			int ccw = 0;
			if (splitct[split_index][4] < 4)
				scatter->Draw(splitct[split_index][1], splitct[split_index][2], &scat[(splitct[split_index][3])]);
			else
				scatterf->Draw(splitct[split_index][1], splitct[split_index][2], &scatf[(splitct[split_index][3])]);
			splitct[split_index][3] += 1;
			if (splitct[split_index][4] < 4)
			{
				if (splitct[split_index][3] > ((splitct[split_index][4]*8) + 7))
				{
					splitct[split_index][0] = 0;
					quanspt -= 1;
				}
			}
			else
			{
				if (splitct[split_index][3] > 9)
				{
					splitct[split_index][0] = 0;
					quanspt -= 1;
				}
			}

			split_counter += 1;
		}
		split_index += 1;
	}
}


void Game::Init_Streak(int bx, int by)
{
	int bul_index = 0;
	bool expl_counter = false;
	while(!expl_counter)
	{
		if (bulx[bul_index][0] == 0)
		{
			bulx[bul_index][0] = 1;
			bulx[bul_index][1] = (bx + 2);
			bulx[bul_index][2] = (by - 100);
			bullnum += 1;
			expl_counter = true;
		}
		bul_index += 1;
		if (bul_index > BULLET_CAP - 1)
			expl_counter = true;
	}
}

void Game::Draw_Streak(void)
{
	int bul_counter = 0;
	int bul_index = 0;
	SDL_Rect bul_wrap;
	while (bul_counter < bullnum)
	{
		if (bulx[bul_index][0] == 1)
		{
			int bulc = 0;
			if (boss_active < 1)
			{
				int c1 = Check_Hit(bulx[bul_index][1],bulx[bul_index][2]);
				bulc = c1;
			}
			if (boss_active == 1)
			{
				int c2 = Check_Bosshit(bulx[bul_index][1],bulx[bul_index][2]);
				bulc = c2;
			}
			if (boss_active == 4)
			{
				int c3 = Check_Bosshit2(bulx[bul_index][1], bulx[bul_index][2]);
				bulc = c3;
			}
			if (bulc != 0)
			{
				bul_wrap.w = 25;
				bul_wrap.y = bulc;
				bul_wrap.h = (144 - bulc);
				bul_wrap.x = 0;
				strek->Draw(bulx[bul_index][1], bulx[bul_index][2], &bul_wrap);
			}
			else
				strek->Draw(bulx[bul_index][1], bulx[bul_index][2]);
			bulx[bul_index][2] -= BULLET_SPEED;	
			if (bulc != 0)
			{
				bulx[bul_index][0] = 0;
				bulx[bul_index][1] = 0;
				bulx[bul_index][2] = 0;
				bullnum -= 1;
			}
			if (bulx[bul_index][2] < (-80))
			{
				bulx[bul_index][0] = 0;
				bulx[bul_index][1] = 0;
				bulx[bul_index][2] = 0;
				bullnum -= 1;
			}
			bul_counter += 1;
		}
		bul_index += 1;
	}
}

int Game::Check_Hit(int chkx, int chky)
{
	int air_index = 0;
	int returv = 0;
	bool finished = false;

	while (!finished)
	{
		if (alienstats[air_index][0] > 0)
		{
			if ((alienstats[air_index][1] + 10) > (chkx - (alienstats[air_index][10])) && (alienstats[air_index][1] - 5) < chkx)
			{
				if ((alienstats[air_index][2] + 100) > chky && alienstats[air_index][2] < (chky + 70))
				{
					alienstats[air_index][12] = 1;
					alienstats[air_index][13] -= 1;
					finished = true;
					returv = ((alienstats[air_index][2] + 70) - chky);
					Init_Strike(chkx - 15, (chky + (returv - 20)));
				}
			}
		}
		air_index += 1;
		if (air_index > AIR_CAP - 1)
			finished = true;
	}

	if (returv == 0 && numal2 > 0)
	{
		int air2_index = 0;
		int air2_counter = 0;
		bool finish = false;
		while (!finish)
		{
			if (aliencl[air2_index][0] > 0)
			{
				if ((aliencl[air2_index][1] + 2)>(chkx-aliencl[air2_index][9]) && (aliencl[air2_index][1] - 5) < chkx)
				{
					if ((aliencl[air2_index][2] + aliencl[air2_index][10]) > chky && aliencl[air2_index][2] < (chky + 70))
					{
						aliencl[air2_index][12] = 1;
						aliencl[air2_index][11] -= 1;
						finish = true;
						if (aliencl[air2_index][0] == 3)
							returv = ((aliencl[air2_index][2] + 120) - chky);
						else
							returv = ((aliencl[air2_index][2] + 70) - chky);
						Init_Strike(chkx - 15, (chky + (returv- 20)));
					}
				}
				air2_counter += 1;
			}
			air2_index += 1;
			if (air2_index > AIR2_CAP - 1)
				finish = true;
			if (air2_counter > numal2)
				finish = true;
		}
	}
	if (returv == 0 && numgr > 0 && groundact > 0)
	{
		bool grd_expl_counter = false;
		int grd_index = 0;
		int grd_counter = 0;
		while (!grd_expl_counter)
		{
			if (groundtar[grd_index][0] > 0 && groundtar[grd_index][0] < 4)
			{
				if ((groundtar[grd_index][1] + 2 ) > (chkx - 140) && (groundtar[grd_index][1] - 4) < chkx)
				{
					if ((groundtar[grd_index][2] + 95) > chky && (groundtar[grd_index][2] < chky + 70))
					{
						groundtar[grd_index][4] = 1;
						groundtar[grd_index][5] = groundtar[grd_index][5] - PLAYER_DAMAGE;
						grd_expl_counter = true;
						returv = ((groundtar[grd_index][2] + 60) - chky);
						Init_Strike((chkx - 15), (chky + (returv - 20)));
					}
				}
				grd_counter += 1;
			}
			grd_index += 1;
			if (grd_index > 9)
				grd_expl_counter = true;;
			if (grd_counter > numgr)
				grd_expl_counter = true;;
		}
	}

	if (returv == 0 && qutur > 0)
	{
		int qut_expl_counter = false;
		int qut_counter = 0;
		int qut_index = 0;
		while (!qut_expl_counter)
		{
			if (turr[qut_index][0] == 1)
			{
				if ((turr[qut_index][1] + 10) > (chkx - 60) && turr[qut_index][1] < (chkx + 10))
				{
					if (turr[qut_index][2] > (chky - 70) && turr[qut_index][2] < (chky + 50))
					{
						qut_expl_counter = true;
						returv = ((turr[qut_index][2] + 40) - chky);
						Init_Strike((chkx - 15), (chky + (returv - 20)));
						turr[qut_index][6] -= PLAYER_DAMAGE;
						turr[qut_index][7] = 1;
					}
				}
				qut_counter += 1;
			}
			if (qut_counter > qutur)
				qut_expl_counter = true;
			qut_index += 1;
			if (qut_index > DRUM_CAP - 1)
				qut_expl_counter = true;
		}
	}

	if (returv == 0 && numdrums > 0)
	{
		int drum_expl_counter = false;
		int drum_counter = 0;
		int drum_index = 0;
		while (!drum_expl_counter)
		{
			if (drums[drum_index][0] == 1)
			{
				if (((drums[drum_index][1]*100) + 8) > (chkx-70) && (drums[drum_index][1]*100) < chkx)
				{
					if ((((800 - (drums[drum_index][2] - scape_count)*100)) + sec_scapect) > (chky - 70) 
						&& ((800 - ((drums[drum_index][2] - scape_count)*100)) + sec_scapect) < (chky + 50))
					{
						drum_expl_counter = 1;
						returv = ((((800 - (drums[drum_index][2] - scape_count)*100) + sec_scapect) + 40) - chky);
						Init_Strike((chkx - 15), (chky + (returv - 20)));
						drums[drum_index][3] = drums[drum_index][3] - PLAYER_DAMAGE;
						if (drums[drum_index][3] < 0)
						{
							Init_Drumexpl(((drums[drum_index][1]*100) - 60), (((800 - ((drums[drum_index][2] - scape_count)*100)) + sec_scapect) - 40));
							Increment_Points(1, 2);
							player->Set_Geassmana(player->Get_Geassmana() + 5);
							level[(drums[drum_index][2])][(drums[drum_index][1])] = 7;
							drums[drum_index][0] = 0;
							numdrums -= 1;
						}
					}
				}
				drum_counter += 1;
			}
			drum_index += 1;
			if (drum_counter > numdrums)
				drum_expl_counter = true;
			if (drum_index > DRUM_CAP - 1)
				drum_expl_counter = true;
		}
	}			
	if (returv > 144)
		returv = 144;
	return returv;
}

int Game::Check_Bosshit(int bshitx, int bshity)
{

	int hdis = 0;
	if (bosscha[0] < (bshitx - 220) && (bosscha[0] + 600) > (bshitx + 185))
	{
		if ((bosscha[1] + 200) > bshity && (bosscha[1] + 140) < bshity + 70)
		{
			bosscha[10] = 1;
			bosscha[9] -= PLAYER_DAMAGE;
			hdis = ((bosscha[1] + 150) - bshity);
			Init_Strike(bshitx - 15, (bshity + (hdis)));
		}
	}
	if (hdis > 144)
		hdis = 144;
	return hdis;
}

int Game::Check_Bosshit2(int bs2hx, int bs2hy)
{
	int bhit2 = 0;
	if (bosscha[0] < (bs2hx - 190) && (bosscha[0] + 600) > (bs2hx + 165))
	{
		if ((bosscha[1] + 250) > bs2hy && (bosscha[1] + 140) < (bs2hy + 70))
		{
			bosscha[10] = 1;
			bosscha[9] -= PLAYER_DAMAGE;
			bhit2 = ((bosscha[1] + 200) - bs2hy);
			Init_Strike((bs2hx - 15), (bs2hy + bhit2));
		}
	}
	if (bhit2 > 144)
		bhit2 = 144;
	return bhit2;
}

void Game::Init_Strike(int strx, int stry)
{
	bool expl_counter = false;
	int str_index = 0;
	while (!expl_counter)
	{
		if (strikes[str_index][0] == 0)
		{
			if (tagger < 1)
			{
				Mix_PlayChannel(5, tag, 0);
				Mix_Volume(5, 50);
				tagger = 10;
			}
			strikes[str_index][0] = 1;
			strikes[str_index][1] = strx;
			strikes[str_index][2] = stry;
			strikes[str_index][3] = 0;
			expl_counter = true;
			numstrikes += 1;
		}
		str_index = str_index + 1;
		if (str_index > STRIKE_CAP - 1)
			expl_counter = true;
	}
}

void Game::Draw_Strikes(void)
{
	int str_index = 0;
	int str_counter = 0;
	while (str_counter < numstrikes)
	{
		if (strikes[str_index][0] > 0)
		{
			splat->Draw(strikes[str_index][1], strikes[str_index][2], &strikefr[(strikes[str_index][3])]);
			strikes[str_index][3] += 1;
			if (strikes[str_index][3] > 3)
			{
				strikes[str_index][0] = 0;
				strikes[str_index][1] = 0;
				strikes[str_index][2] = 0;
				strikes[str_index][3] = 0;
				numstrikes -= 1;			
			}
			str_counter += 1;
		}
		str_index += 1;
	}
}

void Game::Init_Drumexpl(int dx, int dy)
{
	int expl_index = 0;
	int expl_counter = 0;
	while (!expl_counter)
	{
		if (secondexx[expl_index][0] == 0)	//{flag, x, y, wrap}
		{
			Mix_PlayChannel(-1, seconde, 0);
			secondexx[expl_index][0] = 1;
			secondexx[expl_index][1] = dx;
			secondexx[expl_index][2] = dy;
			secondexx[expl_index][3] = 0;
			expl_counter = true;
			nmexpsec += 1;
		}
		expl_index += 1;
		if (expl_index > 7)
			expl_counter = true;
	}
}

void Game::Draw_Drumexpl(void)
{
	int expl_index = 0;
	int expl_counter = 0;
	while(expl_counter < nmexpsec)
	{
		if (secondexx[expl_index][0] > 0)
		{
			secondex->Draw(secondexx[expl_index][1], secondexx[expl_index][2], &exploss[(secondexx[expl_index][3])]);
			secondexx[expl_index][3] += 1;
			if (secondexx[expl_index][3] > 13)
			{
				secondexx[expl_index][0] = 0;
				nmexpsec -= 1;
			}
			expl_counter += 1;
		}
		expl_index += 1;
	}
}

void Game::Init_Expl(int ex, int ey)
{
	int expl_index = 0;
	bool finished = false;
	while (!finished)
	{
		if (explosions[expl_index][0] == 0)
		{
			Mix_PlayChannel(-1, boom, 0);
			explosions[expl_index][0] = 1;
			explosions[expl_index][1] = ex;
			explosions[expl_index][2] = ey;
			explosions[expl_index][3] = 0;
			numexp += 1;
			finished = true;
		}
		expl_index += 1;
		if (expl_index > EXPL_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Expl(void)
{
	int expl_index = 0;
	int expl_counter = 0;
	while (expl_counter < numexp)
	{
		if (explosions[expl_index][0] > 0)
		{
			explo->Draw(explosions[expl_index][1], explosions[expl_index][2], &explofr[(explosions[expl_index][3])]);
			explosions[expl_index][3] += 1;
			if (explosions[expl_index][3] > 13)
			{
				explosions[expl_index][0] = 0;
				numexp -= 1;
			}
			expl_counter += 1;
		}
		expl_index += 1;
	}
}

void Game::Draw_Warning(void)
{
	warning->Draw(180, 300, &wrn[warnfr]);
	warnfr += 1;
	if (warnfr > 4)
		warnfr = 0;
}

void Game::Init_Boss(void)	
{	
	if (current_level == 0)
	{
		bosscha[0] = 150;	//x
		bosscha[1] = (-320);	//y
		bosscha[9] = 1000;	//life
		bosscha[15] = 0;
		boss_active = 1;

	}
	else
	{
		bosscha[0] = 200;
		bosscha[1] = (-380);
		bosscha[9] = 900;
		boss_active = 4;
		bosscha[15] = 38;
	}

	bosscha[2] = 0;
	bosscha[3] = 0;	//shooting status counter
	bosscha[4] = 0;	//boss moving status
	bosscha[5] = 0;
	bosscha[6] = 0;	//moving time
	bosscha[7] = 0;	//shooting speed
	bosscha[8] = 0;	//pellet type
	bosscha[10] = 0;	//if boss being hit
	bosscha[11] = 0;	//boss wrap
	bosscha[12] = 0;	//laser	shoot wrap
	bosscha[13] = 0;	//beam wrap
	bosscha[14] = 0;
	bosscha[16] = 0;
}

void Game::Draw_Boss(void)
{
	boss->Draw(bosscha[0], bosscha[1], &bss[(bosscha[10])][(bosscha[11])]);
	if (bosscha[10] == 1)
		bosscha[10] = 0;
	if (bosscha[8] == 12)
	{
		if (Mix_Playing(2) == 0)
			Mix_PlayChannel(2, cutt, 0);
		if (Mix_Playing(3) == 0)
			Mix_PlayChannel(3, cutt, 0);
		Mix_Volume(2, 128);
		laseron = 1;
		beam->Draw((bosscha[0] + 290),(bosscha[1] + 200), &beamf[(bosscha[13])]);
		if (player->Get_Sprite()->Getx() > (bosscha[0] + 210) && player->Get_Sprite()->Getx() < (bosscha[0] + 370) && spghit == 0 
			&& player->Get_Sprite()->Gety() > (bosscha[1] + 150) && player_active == 1 && invulnerability == 0)
		{
			spghit = 1;
			Init_Playerexpl((player->Get_Sprite()->Getx() - 20),(player->Get_Sprite()->Gety() - 10));
			spghitloc = (bosscha[0] + 265);
			respawncounter = 80;
			player_active = 0;
			player->Set_Firestatus(0);
		}
		if (bosscha[13] == 0)
			bosscha[13] = 1;
		else
			bosscha[13] = 0;
	}
	if (bosscha[8] != 12 && laseron == 1)
	{
		Mix_HaltChannel(2);
		Mix_HaltChannel(3);
		laseron = 0;
	}
	if (bosscha[8] > 10)
	{
		pulse->Draw((bosscha[0] + 210), (bosscha[1] + 70), &puf[(bosscha[12])]);
		if (bosscha[8] == 12 && bosscha[12] == 0)
		{
			bosscha[8] = 0;
		}
		if (bosscha[12] < 3 && bosscha[8] == 11)	//start shoot lazer
			bosscha[12] += 1;
		if (bosscha[12] > 0 && bosscha[8] == 13)	//stop shoot lazer
			bosscha[12] -= 1;
	}
	if (player_active == 1 && invulnerability == 0)
	{
		bool hit_player = false;
		hit_player = Collide((bosscha[0] + 330), (bosscha[1] + 185), 125);
		if (hit_player == true)
		{
			bosscha[10] = 1;
			bosscha[9] -= 1;
			schmhit = 1;
			player->Set_Hits(player->Get_Hits() - PELLET_DAMAGE);
		}
	}
	if (bosscha[9] < 0)
	{
		boss_active = 2;
		Increment_Points(6, 3);
	}
	bosscha[7] += 1;
	bosscha[6] += 1;
	bosscha[0] += (bosspattern[(bosscha[4])][1]);
	bosscha[1] += (bosspattern[(bosscha[4])][2]);
	if (bosscha[7] == bossatpattern[0][(bosscha[3])])
	{
		bosscha[8] = (bossatpattern[1][(bosscha[3])]);
		if (bosscha[8] == 1)	//little pellets
		{
			Mix_PlayChannel(1, thirde, 0);
			Mix_Volume(1, 80);
		}
		bosscha[7] = 0;
		bosscha[3] += 1;
	}
	if (bosscha[8] == 1)
	{
		bosscha[11] += 1;
		if (bosscha[11] == 2)	//start shoot little pellets
		{
			bosscha[8] = 2;
			Init_Pellets((bosscha[0] + 333), (bosscha[1] + 100), 0);
		}
	}
	if (bosscha[8] == 2)	//stop shoot little pellets
	{
		bosscha[11] -= 1;
		if (bosscha[11] == 0)
			bosscha[8] = 0;			
	}
	if (bosscha[8] == 4 && bosscha[11] < 4)
	{
		bosscha[11] = 4;
	}
	if (bosscha[8] == 8)
	{
		if (bosscha[11] > 3)
			bosscha[11] -= 1;
		else
			bosscha[11] = 0;
	}
	if (bosscha[8] == 3)
	{
		bosscha[11] = 3;
		bosscha[8] = 4;
	}
	if (bosscha[8] == 6)	//shoot plasma
	{
		Mix_PlayChannel(-1, bosspl, 0);
		Init_Plasma(bosscha[0] + 120, bosscha[1] + 350);
		Init_Plasma(bosscha[0] + 490, bosscha[1] + 320);
		bosscha[8] += 1;
	}


	if (bosscha[6] > (bosspattern[(bosscha[4])])[0])
	{
		bosscha[4] += 1;
		if (bosscha[4] > 11)	//12 moving status
		{
			bosscha[4] = 1;
			bosscha[3] = 0;
			bosscha[7] = 0;
		}
		bosscha[6] = 0;
	}
}

void Game::Draw_Boss2(void)
{	//{x,y,,,,moving status,,shooting wrap counter,moving counter,,being hit,wrap}
	sscorpion->Draw(bosscha[0], bosscha[1], &scfmm[(bosscha[10])][(bosscha[11])]);
	if (bosscha[10] == 1)
		bosscha[10] = 0;
	if(charge == 0)
	{
		bosscha[1] += (bosspatt2[bosscha[5]][2]);
		bosscha[0] += (bosspatt2[bosscha[5]][1]);
		bosscha[8] += 1;
	}
	else 
	{
		if (charge == 1)
		{
			bosscha[11] = 3;
			charge_x = ((player->Get_Sprite()->Getx() + 60) - (bosscha[0] + 215))/CHARGE_SPEED;
			charge_y = ((player->Get_Sprite()->Gety() + 45) - (bosscha[1] + 100))/CHARGE_SPEED;
			ready = 20;
			charge = 2;
		}
		if(ready < 3)
			bosscha[11] = 4;
		if(charge == 2 && ready == 0)
		{
			bosscha[0] += charge_x;
			bosscha[1] += charge_y;
			charge_r--;
		}
		if(charge == 3)
		{
			bosscha[0] -= charge_x;
			bosscha[1] -= charge_y;
			charge_r--;
		}
		if(charge_r == 0 && charge == 3)
		{
			bosscha[11] = 0;
			charge = 4;
			charge_r = CHARGE_SPEED;
		}
		if(charge_r == 0 && charge == 2)
		{
			charge = 3;
			charge_r = CHARGE_SPEED;
		}
		if (ready > 0)
			ready--;
	}
	if (bosscha[8] > (bosspatt2[bosscha[5]][0]))
	{
		bosscha[8] = 0;
		bosscha[5] += 1;
	}
	if (bosscha[5] > 10)
		bosscha[5] = 1;
	if (player_active == 1 && invulnerability == 0)
	{
		bool hit_player = false;
		hit_player = Collide((bosscha[0] + 300), (bosscha[1] + 225), 125);
		if(bosscha[11] != 4)
		{
			if (hit_player == false)
				hit_player = Collide((bosscha[0] + 150), (bosscha[1] + 275), 40);
			if (hit_player == false)
				hit_player = Collide((bosscha[0] + 65), (bosscha[1] + 320), 25);
		}
		else
		{
			if (hit_player == false)
				hit_player = Collide((bosscha[0] + 215), (bosscha[1] + 330), 55);
			if (hit_player == false)
				hit_player = Collide((bosscha[0] + 210), (bosscha[1] + 450), 40);
		}
		if (hit_player == true)
		{
			bosscha[10] = 1;
			bosscha[9] -= 1;
			schmhit = 1;
			player->Set_Hits(player->Get_Hits() - PELLET_DAMAGE);
		}
	}
	if (bosscha[5] > 0 && bosscha[13] > 5)	//for first, 60 - 36 = 24 not shoot, 36/counter = 6 pellets num
	{
		if (bosscha[7] > 2)
			bosscha[11] = (4 - bosscha[7]);
		else
			bosscha[11] = bosscha[7];
		bosscha[7] -= 1;
		bosscha[15] -= 1;
	}
	if (bosscha[7] < 0 && charge == 0)	//not shoot
		bosscha[11] = 0;
	if (bosscha[15] < 0)	//change shoot status
	{
		bosscha[15] = 60;	//shooting piece
		bosscha[16] += 1;
	}
	if (bosscha[16] > 9)
		bosscha[16] = 0;
	if (firingbo[(bosscha[16])] == 1 && charge == 0)
	{
		bosscha[13] = 0;
		charge = 1;
	}
	if(charge == 4)
	{
		charge = 0;
		bosscha[15] = 60;
		bosscha[16] += 1;
	}
	if (charge == 0 && bosscha[7] < 0 && bosscha[15] < (firingbo[(bosscha[16])]))	//shoot
	{
		bosscha[7] = 4;	//counter = 6, {4,3,2,1,0} + shoot sound
		bosscha[13] = 0;
	}
	if (bosscha[14] == 0)
		bosscha[12] += 1;
	else
		bosscha[12] -= 1;
	if (bosscha[12] == 2)
	{
		bosscha[14] = 1;
	}
	if (bosscha[12] == 0)
		bosscha[14] = 0;
	if(charge == 0)
		bosscha[13] += 1;
	if (bosscha[11] == 2)
	{
		if (player_active == 1)
		{
			Mix_PlayChannel(4, fourth, 0);
			Mix_Volume(4,100);
			Init_Pellets((bosscha[0] + 255), (bosscha[1] + 105), 4);
			Init_Pellets((bosscha[0] + 290), (bosscha[1] + 105), 4);
		}
		bosscha[15] -= 1;
	}
	if (bosscha[9] < 0)
	{
		boss_active = 5;
		Increment_Points(5,3);
	}
}

void Game::Draw_Spghit(void)
{
	sprug->Draw(spghitloc, (player->Get_Sprite()->Gety() - 30), &spgct[prspg]);
	prspg += 1;
	if (prspg > 5)
	{
		spghit  = 0;
		prspg = 0;
	}
}

void Game::Init_Plasma(int pmx, int pmy)
{
	int pl_counter = 0;
	int pl_index = 0;
	while(pl_counter != 3)
	{
		if (passm[pl_index][0] == 0)	//{flag, x, y, which one, if hit}
		{
			passm[pl_index][0] = 1;
			passm[pl_index][1] = pmx + (pl_counter*3);
			passm[pl_index][2] = pmy;
			passm[pl_index][3] = pl_counter;
			passm[pl_index][4] = 0;
			quanp += 1;
			pl_counter += 1;
		}
		pl_index += 1;
		if (pl_index > PLASMA_CAP - 1)
			pl_counter = 3;
	}
}

void Game::Draw_Plasma(void)
{
	int pl_index = 0;
	int pl_counter = 0;
	while (pl_counter < quanp)
	{
		if (passm[pl_index][0] == 1)
		{
			plas->Draw(passm[pl_index][1], passm[pl_index][2], &plasm[(passm[pl_index][3])][(passm[pl_index][4])]);
			passm[pl_index][1] = passm[pl_index][1] + ((-9)+ (9*passm[pl_index][3]));
			passm[pl_index][2] = passm[pl_index][2] + PLASMA_SPEED;
			if (passm[pl_index][4] == 1)
			{
				passm[pl_index][4] = 0;
				Init_Plasmahit(passm[pl_index][1], passm[pl_index][2]);
				passm[pl_index][0] = 0;
				passm[pl_index][1] = 0;
				passm[pl_index][2] = 0;
				passm[pl_index][3] = 0;
				quanp -= 1;
			}
				
			bool hitp = false;
			if (player_active == 1 && passm[pl_index][4] == 0 && invulnerability == 0)
				hitp = Hit_Player((passm[pl_index][1] + 23), (passm[pl_index][2] + 30), 30);
			if (hitp)
			{
				player->Set_Hits(player->Get_Hits() - PLASMA_DAMAGE);
				passm[pl_index][4] = 1;
			}
			if (passm[pl_index][2] > 800)
			{
				passm[pl_index][0] = 0;
				quanp -= 1;
			}
			pl_counter += 1;
		}
		pl_index += 1;
	}
}

void Game::Init_Plasmahit(int plx, int ply)
{
	bool finished = false;
	int plh_index = 0;
	while (!finished)
	{
		if (plasp[plh_index][0] == 0)
		{
			plasp[plh_index][0] = 1;
			plasp[plh_index][1] = plx;
			plasp[plh_index][2] = ply;
			plasp[plh_index][3] = 0;
			finished = true;
			qunplspl += 1;
		}
		plh_index += 1;
		if (plh_index > PLASMA_SPLIT_CAP - 1)
			finished = true;
	}
}

void Game::Draw_Plasmahit(void)
{
	int plh_counter = 0;
	int plh_index = 0;
	while (plh_counter < qunplspl)
	{
		if (plasp[plh_index][0] == 1)
		{
			plasplo->Draw(plasp[plh_index][1], plasp[plh_index][2], &plsfr[(plasp[plh_index][3])]);
			plasp[plh_index][3] = plasp[plh_index][3] + 1;
			if (plasp[plh_index][3] > 7)
			{
				plasp[plh_index][0] = 0;
				qunplspl -= 1;
			}
			plh_counter += 1;
		}
		plh_index += 1;
	}
}

bool Game::Collide(int collx, int colly, int collp)
{
	bool hit = false;
	double mud2 = 0;
	double mud3 = 0;
	mud2 = (collx - (player->Get_Sprite()->Getx() + 60));
	mud2 = mud2*mud2;
	mud3 = ((player->Get_Sprite()->Gety() + 45) - colly);
	mud3 = mud3*mud3;
	double tmp = (sqrt(mud2 + mud3));
	if (tmp < (collp + HIT_RANGE))
	{
		hit = true;
		schmhit = 2;
//		hitpoints -= 1;
	}
	return hit;
}

void Game::Boss_Destroyed(void)
{
	boss->Draw(bosscha[0], bosscha[1], &bss[0][5]);
	explocounter += 1;
	if (explocounter > 1)
	{
		int x = rand()%500;
		int y = rand()%100;
		Init_Expl((x + (bosscha[0])),(y + (70 + bosscha[1])));
		explocounter = 0;
	}
	bosscha[0] = bosscha[0] + 2;
	bosscha[1] = bosscha[1] + 3;
	if (bosscha[1] > 1000)
		boss_active = 3;
}

void Game::Boss_Destroyed2(void)
{
	sscorpion->Draw(bosscha[0], bosscha[1], &scfmm[0][5]);
	explocounter += 1;
	if (explocounter > 1)
	{
		int x = rand()%500;
		int y = rand()%100;
		Init_Expl((x + (bosscha[0])),(y + (70 + bosscha[1])));
		explocounter = 0;
	}
	bosscha[0] = bosscha[0] + 2;
	bosscha[1] = bosscha[1] + 3;
	if (bosscha[1] > 1000)
		boss_active = 6;
}

void Game::Draw_Transition(void)
{
	transit->Draw(transposit, 0);
	transposit -= 20;
	if (transposit > (-448) && transposit<(-423) && current_level == 1)
		continued = 1;
	if (transposit > (-948) && transposit<(-932) && current_level == 0)
		Reset();
	if (transposit < (-2000))
	{
		transtatus = 0;
		transposit = 1000;
	}
}

void Game::Reset(void)
{
	boss_active = 0;
	current_level += 1;
	unicounter = 6000;
	player->Get_Sprite()->Setx(440);
	player->Get_Sprite()->Sety(600);
	player_control = 1;
	boss_active = 0;
	scape_count = 124;
}

void Game::Start(void)
{	// introduction init
	Mix_Music *intro_bgm = NULL;
	intro_bgm = Mix_LoadMUS("music/intro.wav");	
	intro_time = SDL_GetTicks();
// mainmenu init
	Mix_Music *menu_bgm = NULL;
	menu_bgm = Mix_LoadMUS("music/menu.wav");
	menu_time = SDL_GetTicks();	
//game over init
	loser = new Land_Scape(sdl_setup, "pic/loser.png", 542, 247);	
	loser_time = new Land_Scape(sdl_setup, "pic/digits.png", 75, 492);	
//loser time wrap
	for (int pwdc = 0; pwdc <= 5; pwdc++)
	{
		prfram[pwdc].x = 0;
		prfram[pwdc].y = (82*pwdc);;
		prfram[pwdc].w = 75;
		prfram[pwdc].h = 82;
	}
//game init
	Mix_Music *game_level1 = NULL;
	game_level1 = Mix_LoadMUS("music/level1.wav");
	game_time = SDL_GetTicks();
	land = new Land_Scape(sdl_setup, "pic/land.jpg", 3500, 100);	

	for (int ldn = 0; ldn <= 34; ldn++)
	{
		land_scape[ldn].x = (ldn*100);
		land_scape[ldn].y = 0;
		land_scape[ldn].h = 100;
		land_scape[ldn].w = 100;
	}
//global init
	transit = new Land_Scape(sdl_setup, "pic/cross.png", 2000, 800);
	tbcont = new Land_Scape(sdl_setup, "pic/continued.jpg", 1000, 800); 
//ground init
	fifthe = Mix_LoadWAV("music/groundpellets.wav");	
	artil = Mix_LoadWAV("music/turretpellets.wav");
	wake = new Land_Scape(sdl_setup, "pic/waterwave.png", 797, 176);	
	mwake = new Land_Scape(sdl_setup, "pic/miniwaterwave.png", 37, 176);	
	wak = new Land_Scape(sdl_setup, "pic/waki.png", 203, 384);

	grshadow = new Land_Scape(sdl_setup, "pic/groundarmyshadow.png", 200, 400);
	tank = new Land_Scape(sdl_setup, "pic/groundarmy.png", 350, 500);	

	turret = new Land_Scape(sdl_setup, "pic/turrets.png", 200, 2400);	
	muflash = new Land_Scape(sdl_setup, "pic/muflash.png", 60, 180);	

	circ = new Land_Scape(sdl_setup, "pic/ci.png", 100, 200);	
	pellet = new Land_Scape(sdl_setup, "pic/pellets.png", 30, 130);	
//drum
	for (int awdr = 0; awdr <= DRUM_CAP - 1; awdr++)
	{
		for (int awdrr23 = 0; awdrr23 <= 3; awdrr23++)
		{
			drums[awdr][awdrr23] = 0;
		}
	}
//wave by boat
	for (int ewd = 0; ewd <= 2; ewd++)
	{
		waks[ewd].x = 0;
		waks[ewd].y = (ewd*128);
		waks[ewd].h = 128;
		waks[ewd].w = 203;
	}
//ground army shadow
	for (int shg = 0; shg <= 3; shg++)
	{
		shadg[shg].x = 0;
		shadg[shg].y = (shg*100);
		shadg[shg].h = 100;
		if (shg > 1)
			shadg[shg].w = 200;
		else
			shadg[shg].w = 165;
	}
//ground army
	for (int grtr = 0; grtr <= 9; grtr++)
	{
		for (int grgrt = 0; grgrt <= 4; grgrt++)
		{
			groundtar[grtr][grgrt] = 0;
		}
	}
//ground army wrap
	for (int tan = 0; tan <= 1; tan++)
	{
		for (int ewd = 0; ewd <= 2; ewd++)
		{
			tafr[tan][ewd].x  = (tan*143);
			tafr[tan][ewd].y = (ewd*96);
			tafr[tan][ewd].h = 96;
			tafr[tan][ewd].w = 143;
		}
	}
	tafr[0][2].x = 0;
	tafr[0][2].y = 200;
	tafr[0][2].h = 98;
	tafr[0][2].w = 165;
	tafr[1][2].x = 200;
	tafr[1][2].y = 200;
	tafr[1][2].h = 50;
	tafr[1][2].w  = 50;
	tafr[0][3].x=0;
	tafr[0][3].y=300;
	tafr[0][3].h=80;
	tafr[0][3].w = 175;
	tafr[1][3].x= 175;
	tafr[1][3].y = 300;
	tafr[1][3].w=175;
	tafr[1][3].h = 80;
	tafr[0][4].x=0;
	tafr[0][4].y=380;
	tafr[0][4].h=100;
	tafr[0][4].w=200;
	tafr[1][4].x = 200;
	tafr[1][4].y=380;
	tafr[1][4].h=10;
	tafr[1][4].w = 10;
//circle wrap
	circc[0].x = 0;
	circc[0].y = 0;
	circc[0].h=33;
	circc[0].w = 31;
	circc[1].x = 0;
	circc[1].y=35;
	circc[1].w= 45;
	circc[1].h = 47;
	circc[2].x=0;
	circc[2].y=82;
	circc[2].h=47;
	circc[2].w=47;
	circc[3].x=0;
	circc[3].y=129;
	circc[3].h=65;
	circc[3].w=65;
//turret
	for (int turb = 0; turb <= TURRET_CAP - 1; turb++)
	{
		for (int turw = 0; turw <= 8; turw++)
		{
			turr[turb][turw] = 0;
		}
	}
//turret wrap
	for (int ewwa = 0;ewwa <= 1; ewwa++)
	{
		for (int hihn = 0; hihn <= 47; hihn++)
		{
			turretfr[ewwa][hihn].x = (ewwa*100);
			turretfr[ewwa][hihn].y = (hihn*100);
			turretfr[ewwa][hihn].h = 100;
			turretfr[ewwa][hihn].w = 100;
		}
	}
//turret muzflash
	for (int fmmr = 0; fmmr <= 9; fmmr++)
	{
		for (int fqw = 0; fqw <= 4; fqw++)
		{
			muf[fmmr][fqw] = 0;
		}
	}
//turret muzflash wrap
	for (int mah = 0; mah <=2 ; mah++)
	{
		mffr[mah].x = 0;
		mffr[mah].y = (mah*60);
		mffr[mah].w = 60;
		mffr[mah].h = 60;
	}
//pellets
	for (int pell = 0; pell <= PELLET_CAP - 1; pell++)
	{
		for (int pell2 = 0; pell2 <= 5; pell2++)
		{
			pellets[pell][pell2] = 0;
		}
	}
//pellets wrap
	pelltt[0].x = 0;
	pelltt[0].y=0;
	pelltt[0].h=20;
	pelltt[0].w=20;
	pelltt[1].x=0;
	pelltt[1].y=20;
	pelltt[1].h=25;
	pelltt[1].w=25;
	pelltt[2].x=0;
	pelltt[2].y=45;
	pelltt[2].w=25;
	pelltt[2].h=25;
	pelltt[3].x=0;
	pelltt[3].y=70;
	pelltt[3].h=25;
	pelltt[3].w=25;
	pelltt[4].x=0;
	pelltt[4].y=100;
	pelltt[4].w=30;
	pelltt[4].h=30;
//gunboat init
	bigeng = Mix_LoadWAV("music/enggin.wav");
	gboat = new Land_Scape(sdl_setup, "pic/gunboat.png", 395, 857);
	scba = new Land_Scape(sdl_setup, "pic/boatwave.png", 322, 626);
//gunboat
	for (int tur_index = 0; tur_index <= GUNBOAT_CAP - 1; tur_index++)
	{
		for (int brgrt = 0; brgrt <= 3; brgrt++)
		{
			gunb[tur_index][brgrt] = 0;
		}
	}
//wave wrap
	qpl[0].x = 0;
	qpl[0].y = 0;
	qpl[0].h= 313;
	qpl[0].w = 322;
	qpl[1].x=0;
	qpl[1].y = 313;
	qpl[1].h = 313;
	qpl[1].w = 322;
//air army init
	bitbos = Mix_LoadWAV("music/airpellet.wav");
	alienstuff = new Land_Scape(sdl_setup, "pic/airarmy.png", 262, 939);
	aliencl2 = new Land_Scape(sdl_setup, "pic/airarmy2.png", 380, 1288);
//air army status
	for (int alesrr = 0; alesrr <= AIR_CAP - 1; alesrr++)
	{
		for (int wless = 0; wless <= 19; wless++)
		{
			alienstats[alesrr][wless] = 0;
		}
	}
	for (int aaelwe = 0; aaelwe <= AIR2_CAP - 1; aaelwe++)
	{
		for (int awell = 0;awell <= 24; awell++)
		{
			aliencl[aaelwe][awell] =0;
		}
	}
//air army wrap
	for (int alee = 0; alee <= 1; alee ++)
	{
		for (int alee2  = 0; alee2 <= 8; alee2++)
		{
			if (alee2 < 4){
				aliens[alee][alee2].x = (131*alee);
				aliens[alee][alee2].y = (132*alee2);
				aliens[alee][alee2].h = 132;
				aliens[alee][alee2].w = 131;
			}
			if (alee2 == 4)
			{
				aliens[alee][alee2].x = (131*alee);
				aliens[alee][alee2].y = 527;
				aliens[alee][alee2].h = 94;
				aliens[alee][alee2].w = 131;
			}
			if (alee2 == 5)
			{
				aliens[alee][alee2].x = (79*alee);
				aliens[alee][alee2].y = 622;
				aliens[alee][alee2].h = 79;
				aliens[alee][alee2].w = 79;
			}
			if (alee2 == 6)
			{
				aliens[alee][alee2].x = (79*alee);
				aliens[alee][alee2].y = 701;
				aliens[alee][alee2].h = 79;
				aliens[alee][alee2].w = 79;
			}
			if (alee2 == 7)
			{
				aliens[alee][alee2].x = (79*alee);
				aliens[alee][alee2].y = 780;
				aliens[alee][alee2].h = 79;
				aliens[alee][alee2].w = 79;
			}
			if (alee2 == 8)
			{
				aliens[alee][alee2].x = (79*alee);
				aliens[alee][alee2].y = 859;
				aliens[alee][alee2].h = 79;
				aliens[alee][alee2].w = 79;
			}
		}
	}
	for (int cl22 = 0; cl22 <= 1; cl22++)
	{
		for (int cl222 = 0; cl222 <= 3; cl222++)
		{
			clalfr[cl22][cl222].x = (cl22*133);
			clalfr[cl22][cl222].y = (cl222*126);
			clalfr[cl22][cl222].h = 126;
			clalfr[cl22][cl222].w = 133;
		}
	}
	for (int cdll = 0; cdll <= 1; cdll++)
	{
		clalfr[cdll][4].x = (111*cdll);
		clalfr[cdll][4].y = 511;
		clalfr[cdll][4].w = 111;
		clalfr[cdll][4].h = 132;
	}
	for (int cl223 = 0; cl223 <= 1; cl223++)
	{
		for (int cl2223 = 5; cl2223 <= 7; cl2223++)
		{
			clalfr[cl223][cl2223].y = (642+(202*(cl2223 - 5)));
			clalfr[cl223][cl2223].x = (178*cl223);
			clalfr[cl223][cl2223].h = 202;
			clalfr[cl223][cl2223].w = 178;
		}
	}
//gfire init
	zap = Mix_LoadWAV("music/shoot.wav");
	biglazer = Mix_LoadWAV("music/biglazer.wav");
	heligun = Mix_LoadWAV("music/heligun.wav");
	gfire = new Land_Scape(sdl_setup, "pic/gfire.png", 70, 611);
//gfire wrap
	for (int ggpww = 0; ggpww <= 1; ggpww++)
	{
		gff[ggpww].x = 0;
		gff[ggpww].y = (ggpww*41);
		gff[ggpww].h = 41;
		gff[ggpww].w = 16;
	}
	for (int ggo = 2; ggo <= 4; ggo++)
	{
		gff[ggo].x = 0;
		gff[ggo].y = (82 + ((ggo - 2)*79));
		gff[ggo].h = 79;
		gff[ggo].w = 60;
	}
	for (int ghdbb = 5; ghdbb <= 8; ghdbb++)
	{
		gff[ghdbb].x = 0;
		gff[ghdbb].y = (319 + ((ghdbb - 5)*73));
		gff[ghdbb].h = 73;
		gff[ghdbb].w = 70;
	}
//lightning init
	electricity = new Land_Scape(sdl_setup, "pic/lightning.png", 100, 820);
	hitter = new Land_Scape(sdl_setup, "pic/lightningsp.png", 100, 600);
//lightning 
	for (int bl223 = 0; bl223 <= LIGHTNING_CAP - 1; bl223++)
	{
		for (int bl2223 = 0; bl2223 <= 4; bl2223++)
		{
			bolt[bl223][bl2223] = 0;
		}
	}
//lightning split 
	for (int bl22 = 0; bl22 <= LIGHTNING_SPLIT_CAP - 1; bl22++)
	{
		for (int bl222 = 0; bl222 <= 3; bl222++)
		{
			sprk[bl22][bl222] = 0;
		}
	}
//lightning split wrap
	for (int asp3 = 0;asp3 <= 5; asp3++)
	{
		spkl[asp3].x = 0;
		spkl[asp3].y = (asp3*100);
		spkl[asp3].h = 100;
		spkl[asp3].w = 100;
	}
//lazer init
	alienla = new Land_Scape(sdl_setup, "pic/lazer.png", 67, 278); 
	blos = new Land_Scape(sdl_setup, "pic/lazersp.png", 120, 936);
//lazer
	for (int bl3 = 0; bl3 <= LAZER_CAP - 1; bl3++)
	{
		for (int bl23 = 0; bl23 <= 4; bl23++)
		{
			allz[bl3][bl23] = 0;
		}
	}	
//lazer wrap
	lazz[0].h = 80;
	lazz[0].w = 16;
	lazz[0].x = 0;
	lazz[0].y = 0;
	lazz[1].x = 0;
	lazz[1].y = 80;
	lazz[1].h = 180;
	lazz[1].w = 65;
	lazz[2].x = 0;
	lazz[2].y = 80;
	lazz[2].h = 180;
	lazz[2].w = 65;
//lazer split
	for (int qwe = 0; qwe <= LAZER_SPLIT_CAP - 1; qwe++)
	{
		for (int wee = 0; wee <= 4; wee++)
		{
			bloss[qwe][wee] = 0;
		}
	}
//lazer split wrap
	for (int wd2 = 0; wd2 <= 5; wd2++)
	{
		hfr[wd2].x = 0;
		hfr[wd2].y = (wd2*120);
		hfr[wd2].h = 120;
		hfr[wd2].w = 120;
	}
	for (int wd3 = 6;wd3 <= 11; wd3++)
	{
		hfr[wd3].x = 0;
		hfr[wd3].y = (720+(wd3*36));
		hfr[wd3].w = 38;
		hfr[wd3].h = 36;
	}
//player init
	machinegun = Mix_LoadWAV("music/gun.wav");
	tail = new Land_Scape(sdl_setup, "pic/tailpipe.png", 50, 300);
	pshadow = new Land_Scape(sdl_setup, "pic/playershadow.png", 100, 500);
	player = new Player(sdl_setup);
//shadow wrap 
	for (int pish = 0; pish <= 4; pish++)
	{
		schmesh[pish].x = 0;
		schmesh[pish].y = (pish*100);
		schmesh[pish].h = 100;
		schmesh[pish].w = 100;
	}
//tail wrap
	for (int piw = 0; piw <= 2; piw++)
	{
		pipe[piw].x = 0;
		pipe[piw].y = (piw*100);
		pipe[piw].h = 100;
		pipe[piw].w = 50;
	}
//player wrap
	for (int sddcc = 0; sddcc <= 2; sddcc++)
	{

		for (int sdddc = 0;sdddc <= 4; sdddc++)
		{
			schmetfr[sddcc][sdddc].x = (125*sddcc);
			schmetfr[sddcc][sdddc].y = (125*sdddc);
			schmetfr[sddcc][sdddc].w = 125;
			schmetfr[sddcc][sdddc].h = 125;
		}
	}
//geass init
	geass = new Land_Scape(sdl_setup, "pic/geass.png", 500, 4464);
	geass_icon = new Land_Scape(sdl_setup, "pic/v.png", 600, 1110);
//geass wrap
	for (int giw = 0; giw <= 17; giw++)
	{
		geas[giw].x = 0;
		geas[giw].y = (giw*248);
		geas[giw].h = 248;
		geas[giw].w = 500;
	}
//geass icon wrap
	for (int giiw = 0; giiw <= 2; giiw++)
	{
		geasi[giiw].x = 0;
		geasi[giiw].y = (giiw*370);
		geasi[giiw].h = 370;
		geasi[giiw].w = 600;
	}
//HPMP, points init
	slot = new Land_Scape(sdl_setup, "pic/slot.png", 450, 184);	
	hpmp = new Land_Scape(sdl_setup, "pic/hpmp.png", 300, 100);
	heart = new Land_Scape(sdl_setup, "pic/lives.png", 350, 46);
	points = new Land_Scape(sdl_setup, "pic/numbers.png", 500, 50);	
//hp wrap init
	for (int hgd = 1; hgd <= ONELIVE; hgd++)
	{
		hp[hgd].x = 16;
		hp[hgd].y = 0;
		hp[hgd].h = 50;
		hp[hgd].w = (264/ONELIVE)*hgd;
	}
	hp[0].x = 16;
	hp[0].y = 0;
	hp[0].h = 50;
	hp[0].w = 0;
//mp wrap init
	for (int mgd = 1; mgd <= 3*GEASS; mgd++)
	{
		mp[mgd].x = 17;
		mp[mgd].y = 50;
		mp[mgd].h = 50;
		mp[mgd].w = int((231.0/(3*GEASS))*mgd);
	}
	mp[0].x = 17;
	mp[0].y = 50;
	mp[0].h = 50;
	mp[0].w = 0;
//points wrap
	for (int wdddw = 0; wdddw <= 9; wdddw++)
	{
		pts[wdddw].x = (50*wdddw);
		pts[wdddw].y = 0;
		pts[wdddw].h = 50;
		pts[wdddw].w = 50;
	}
//lives wrap
	for (int wddd = 0; wddd <= 4; wddd++)
	{
		hrt[wddd].x = 0;
		hrt[wddd].y = 0;
		hrt[wddd].h = 46;
		hrt[wddd].w = (50*(wddd + 1));
	}
//gun fire init
	gunf = new Land_Scape(sdl_setup, "pic/gunfire.png", 29, 68);
	strek = new Land_Scape(sdl_setup, "pic/bullets.png", 25, 141);	
//gun fire wrap
	for (int fgd = 0; fgd <= 1; fgd++)
	{
		fg[fgd].x = 0;
		fg[fgd].y = (fgd*44);
		fg[fgd].h = 44;
		fg[fgd].w = 29;
	}
//bullets
	for (int brrew = 0; brrew <= BULLET_CAP - 1; brrew++)
	{
		for (int bewew = 0; bewew <= 2; bewew++)
		{
			bulx[brrew][bewew] = 0;
		}
	}
//strikes init
	splat = new Land_Scape(sdl_setup, "pic/strike.png", 38, 224);
	tag = Mix_LoadWAV("music/hit.wav");	
	for (int deww = 0; deww <= STRIKE_CAP - 1; deww++)
	{
		for (int deww2 = 0; deww2 <= 3; deww2++)
		{
			strikes[deww][deww2] = 0;
		}
	}
//strikes wrap
	for (int dfew = 0; dfew <= 3; dfew++)
	{
		strikefr[dfew].x = 0;
		strikefr[dfew].y = (dfew*56);
		strikefr[dfew].h = 56;
		strikefr[dfew].w = 38;
	}
//explosion init
	seconde = Mix_LoadWAV("music/trumexpl.wav");
	boom = Mix_LoadWAV("music/expl.wav");
	secondex = new Land_Scape(sdl_setup, "pic/secsplo.png", 200, 2800);	
	explo = new Land_Scape(sdl_setup, "pic/expl.png", 265, 3600);	
//drum explosion
	for (int secc = 0; secc <= DRUM_EXPL_CAP - 1; secc++)
	{
		for (int ccf = 0; ccf < 3; ccf++)
		{
			secondexx[secc][ccf] = 0;
		}
	}
//drum explosion wrap
	for (int aexc = 0; aexc <= 13; aexc++)
	{
		exploss[aexc].x = 0;
		exploss[aexc].y = (aexc*200);
		exploss[aexc].w = 200;
		exploss[aexc].h = 200;
	}
//explosion
	for (int cdwsd = 0; cdwsd <= EXPL_CAP - 1; cdwsd++)
	{
		for (int wps = 0; wps <= 3; wps++)
		{
			explosions[cdwsd][wps] = 0;
		}
	}
//explosion wrap
	for (int ewwwedf = 0; ewwwedf <= 13; ewwwedf++)
	{
		explofr[ewwwedf].x = 0;
		explofr[ewwwedf].y = (258*ewwwedf);
		explofr[ewwwedf].h = 258;
		explofr[ewwwedf].w = 265;
	}
//player explosion init
	playerblow = Mix_LoadWAV("music/playerexpl.wav");
	pexplo = new Land_Scape(sdl_setup, "pic/playerexpl.png", 150, 1950);	
//player explosion wrap
	for (int pe24 = 0; pe24 <= 12; pe24++)
	{
		pex[pe24].x = 0;
		pex[pe24].y = (pe24*150);
		pex[pe24].h = 150;
		pex[pe24].w = 150;
	}
//being hit init
	scatter = new Land_Scape(sdl_setup, "pic/split.png", 30, 720);
	scatterf = new Land_Scape(sdl_setup, "pic/splitf.png", 50, 500);	
//being hit strikes
	for (int splid = 0; splid <= SPLIT_CAP - 1; splid++)
	{
		for (int splis = 0; splis <= 4; splis++)
		{
			splitct[splid][splis] = 0;
		}
	}
//being hit strikes wrap
	for (int dd22q = 0; dd22q <= 23; dd22q++)
	{
		scat[dd22q].x = 0;
		scat[dd22q].y = (30*dd22q);
		scat[dd22q].w = 30;
		scat[dd22q].h = 30;
	}
	scat[24].x = 0;
	scat[24].y = 720;
	scat[24].h = 50;
	scat[24].w = 50;
	for (int qpawdq = 0; qpawdq <= 9; qpawdq++)
	{
		scatf[qpawdq].x = 0;
		scatf[qpawdq].y = (qpawdq*50);
		scatf[qpawdq].h = 50;
		scatf[qpawdq].w = 50;
	}
//warning init
	warner = Mix_LoadWAV("music/warn.wav");	
	warning = new Land_Scape(sdl_setup, "pic/warn.png", 634, 655);	
//warning warp
	for (int wrns = 0; wrns <= 4; wrns++)
	{
		wrn[wrns].x = 0;
		wrn[wrns].y = (131*wrns);
		wrn[wrns].w = 634;
		wrn[wrns].h = 131;
	}
//boss init
	boss = new Land_Scape(sdl_setup, "pic/boss.png", 1200, 2220);	
	boss_level = Mix_LoadMUS("music/bosslevel.wav");	
//boss wrap
	for (int dwwwqaa = 0; dwwwqaa <= 1; dwwwqaa++)
	{
		for (int dwcaa = 0; dwcaa <= 5; dwcaa++)
		{
			bss[dwwwqaa][dwcaa].x= (600*dwwwqaa);
			bss[dwwwqaa][dwcaa].y = (370*dwcaa);
			bss[dwwwqaa][dwcaa].w = 600;
			bss[dwwwqaa][dwcaa].h = 370;
		}
	}
//boss weapon init
	beam = new Land_Scape(sdl_setup, "pic/beam.png", 210, 800); 	
	bosspl = Mix_LoadWAV("music/bossgun.wav");
	cutt = Mix_LoadWAV("music/cute.wav");	//laser
	thirde = Mix_LoadWAV("music/lpellets.wav");	//little pellets
	pulse = new Land_Scape(sdl_setup, "pic/pulse.png", 250, 964);	//laser	shoot
	plas = new Land_Scape(sdl_setup, "pic/splsma.png", 168, 138);	
	plasplo = new Land_Scape(sdl_setup, "pic/spaw.png", 112, 936);	
	sprug = new Land_Scape(sdl_setup, "pic/spghit.png", 158, 924);
//beam wrap
	for (int bfw = 0; bfw <= 1; bfw++)
	{
		beamf[bfw].x = (105*bfw);
		beamf[bfw].y = 0;
		beamf[bfw].h = 800;
		beamf[bfw].w = 105;
	}
//laser	shoot wrap
	for (int pussc = 0; pussc <= 3; pussc++)
	{
		puf[pussc].x = 0;
		puf[pussc].y = (pussc * 241);
		puf[pussc].h = 241;
		puf[pussc].w = 250;
	}
//laser split wrap
	for (int wlcw = 0; wlcw <= 5; wlcw++)
	{
		spgct[wlcw].x = 0;
		spgct[wlcw].y = (154*wlcw);
		spgct[wlcw].w = 158;
		spgct[wlcw].h = 154;
	}
//plasma
	for (int pla = 0; pla <= PLASMA_CAP - 1; pla++)
	{
		for (int plaa = 0; plaa <= 4; plaa++)
		{
			passm[pla][plaa] = 0;
		}
	}
//plasma wrap
	for (int paas = 0; paas <= 2; paas++)
	{
		for (int ppas = 0; ppas <= 1; ppas++)
		{
			plasm[paas][ppas].x = (56*paas);
			plasm[paas][ppas].y = (69*ppas);
			plasm[paas][ppas].w = 56;
			plasm[paas][ppas].h = 69;
		}
	}
//plasma split
	for (int plas = 0; plas <= PLASMA_SPLIT_CAP - 1; plas++)
	{
		for (int plaas = 0; plaas <= 3; plaas++)
		{
			plasp[plas][plaas] = 0;
		}
	}
//plasma split wrap
	for (int plsf = 0; plsf <= 8; plsf++)
	{
		plsfr[plsf].x = 0;
		plsfr[plsf].y = (104*plsf);
		plsfr[plsf].h = 104;
		plsfr[plsf].w = 112;
	}
//boss2 init
	fourth = Mix_LoadWAV("music/boss2gun.wav");
	sscorpion = new Land_Scape(sdl_setup, "pic/boss2.png", 1200, 2550);
//boss wrap
	for (int scpp = 0; scpp <= 1; scpp++)
	{
		for (int scp2 = 0; scp2 <= 3; scp2++)
		{
			scfmm[scpp][scp2].x = (600*scpp);
			scfmm[scpp][scp2].y = (400*scp2);
			scfmm[scpp][scp2].h = 400;
			scfmm[scpp][scp2].w = 600;
		}
	}
	for (int scpp = 0; scpp <= 1; scpp++)
	{
		scfmm[scpp][4].x = (600*scpp);
		scfmm[scpp][4].y = 1600;
		scfmm[scpp][4].h = 550;
		scfmm[scpp][4].w = 600;
	}
	for (int scpp = 0; scpp <= 1; scpp++)
	{
		scfmm[scpp][5].x = (600*scpp);
		scfmm[scpp][5].y = 2150;
		scfmm[scpp][5].h = 400;
		scfmm[scpp][5].w = 600;
	}
//dialog init
	dialog1 = new Land_Scape(sdl_setup, "pic/guide1.png", 800, 200);
	dialog2 = new Land_Scape(sdl_setup, "pic/guide2.png", 800, 200);
	dialog3 = new Land_Scape(sdl_setup, "pic/guide3.png", 800, 200);

	while (!menu_gameover)
	{
		while (introduction)
		{
			if ((SDL_GetTicks() - intro_time) > FPS)
			{
				sdl_setup->Start();

				if(sdl_setup->Get_Main()->type == SDL_QUIT)
					return;
				intro_time = SDL_GetTicks();

				if (Mix_PlayingMusic() == 0)
					Mix_PlayMusic(intro_bgm,0);

				Draw_Storyboard();
				if(intro_idx > 1)
					story_words->Write_Text(intro_narr_idx);
				Intro_Getinput();

				if (intro_done && Mix_PlayingMusic() == 1)
					Mix_HaltMusic();
			}
			sdl_setup->End();
		}	

		while (mainmenu)
		{
			if ((SDL_GetTicks() - menu_time) > FPS)
			{
				sdl_setup->Start();

				if(sdl_setup->Get_Main()->type == SDL_QUIT)
					return;

				if (Mix_PlayingMusic() == 0)
					Mix_PlayMusic(menu_bgm, -1);
				menu_time = SDL_GetTicks();
				Draw_Menuboard();
				Menu_Getinput();

				menu_logo->Draw(0, 0, 1000, 800);

				if(menu_gameover)
					menu_options->Draw(0, 0, 319, 123);
				else
					menu_options->Draw(0, 123, 319, 123);

				if (!mainmenu  && Mix_PlayingMusic() == 1)
					Mix_HaltMusic();
			}
			sdl_setup->End();
		}	
/*
		if(current_level == 0)
			Reset();
		current_level = 1;
		guide = 0;
*/
		if((SDL_GetTicks() - game_time) > FPS)	
		{
			if(sdl_setup->Get_Main()->type == SDL_QUIT)
				return;
			sdl_setup->Start();
			if (Mix_PlayingMusic() == 0 && current_level == 0 && unicounter < 5200)
				Mix_PlayMusic(game_level1, -1);
			if (unicounter == 5200 && Mix_PlayingMusic())
				Mix_HaltMusic();
			if (Mix_PlayingMusic() == 0 && current_level == 1 && unicounter < 11000)
				Mix_PlayMusic(game_level1, -1);
			if (unicounter == 11000 && Mix_PlayingMusic())
				Mix_HaltMusic();
			Mix_VolumeMusic(128);

			game_time = SDL_GetTicks();

			Draw_Landscape();

			if (numgr > 0)
				Draw_Ground();
			if (onetime)
				One_Time();

			if(player_active && boss_active != 9)
				pshadow->Draw(player->Get_Sprite()->Getx() + 40, player->Get_Sprite()->Gety() + 20, &schmesh[player->Get_Status()]);

			if (unicounter == grncue[grq][0])
			{
				Init_Ground(grncue[grq][1], grncue[grq][2], grncue[grq][3]);
				grq += 1;
			}
			if (tur_counter < turcue.size())
			{
				if((scape_count + 9) == turcue[tur_counter][0] && current_level == 0)
				{
					Init_Turret(turcue[tur_counter][1], turcue[tur_counter][0]);
					tur_counter += 1;
				}
			}
			if (unicounter == (btcuess[btcue][0]))
			{
				Init_Gunboat(btcuess[btcue][1]);
				btcue += 1;
			}
			if (quantgbt > 0)
			{
				Draw_Gunboat();
				if (benct < 1)
				{
					if (Mix_Playing(0) == 0)
						Mix_PlayChannel(0, bigeng, 0);
					Mix_Volume(0, 40);
					benct = 50;
				}
			}
			if (qutur > 0)
				Draw_Turret();
			if (qumzfl > 0)
				Draw_Muzflash();

			if (unicounter == aliencues[cuer][0])
			{
				Init_Air(aliencues[cuer][1], aliencues[cuer][2], aliencues[cuer][3], aliencues[cuer][4]);
				cuer += 1;
			}
			if (alienqun > 0)
				Draw_Air();
			if (unicounter == cl2alcue[cl2q][0])
			{
				Init_Air2(cl2alcue[cl2q][1], cl2alcue[cl2q][2], cl2alcue[cl2q][3], cl2alcue[cl2q][4]);
				cl2q += 1;
			}
			if (numal2 > 0)
				Draw_Air2();

			if (unicounter > 5500 && current_level == 0)
			{
				if (Mix_PlayingMusic() == 0)
				{
					Mix_PlayMusic(boss_level, -1);
				}
			}
			if (unicounter > 11250 && current_level == 1 && continued == 0)
			{
				if (Mix_PlayingMusic() == 0)
				{
					Mix_PlayMusic(boss_level, -1);
				}
			}
			if (unicounter == 5350)
				warnstatus = 80;
			if (unicounter == 11100)
				warnstatus = 80;

			if (boss_active == 2)
				Boss_Destroyed();
			if (boss_active == 5)
				Boss_Destroyed2();
			if (boss_active == 3)
			{
				transtatus = 1;
				player_control = 0;
				boss_active = 9;
			}
			if (boss_active == 6)
			{
				transtatus = 1;
				player_control = 0;
				boss_active = 9;
			}
			if (unicounter == 5550)
				Init_Boss();
			if (unicounter == 11300)
				Init_Boss();
			if (unicounter > 5950 && current_level == 0)
				unicounter = 5700;
			if (unicounter > 11700 && current_level == 1  && continued == 0)
				unicounter = 11450;
			if (boss_active == 1)
				Draw_Boss();
			if (boss_active == 4)
				Draw_Boss2();
			if (quanp> 0)
				Draw_Plasma();
			if (quantlz > 0)
				Draw_Lazer();
			if (numlight > 0)
				Draw_Lightning();

			if (transtatus)
			{
				if (Mix_PlayingMusic())
					Mix_HaltMusic();
				Draw_Transition();
			}

			if (player_active == 1 && player_control == 1)
			{
				Draw_Player();
				player->Move();
				player->Attack();
			}

			if (player->Get_Shoot() && player_active == 1)
				Attack();
			if (bullnum > 0)
				Draw_Streak();
			if (nmexpsec > 0)
				Draw_Drumexpl();
			if (numexp > 0)
				Draw_Expl();

			if (qunplspl > 0)
				Draw_Plasmahit();
			if (spghit == 1)
				Draw_Spghit();
			if (quanhz > 0)
				Drawlzhit();
			if (numspk > 0)
				Draw_Sp();
			if (quanspt > 0)
				Draw_Split();
			if (explopr == 1)
				Draw_Playerexpl();

			if (quanpel > 0)
				Draw_Pellets();
			if (numstrikes > 0)
				Draw_Strikes();

			if(player->Get_Geass())
				Geass();

			if (warnstatus > 0)
			{
				Draw_Warning();
				warnstatus -= 1;
			}
			if (warnstatus == 79)
			{
				Mix_PlayChannel(3, warner, 0);
				Mix_Volume(3, 90);
			}

			Draw_HM();
			Draw_Lives();
			Draw_Points();

			if (hgunct > 0)
				hgunct -= 1;
			if (benct > 0)
				benct -= 1;

			if (rdir == 0)
				rframe += 1;
			else
				rframe -= 1;
			wf += 1;
			if (wf > 2)
				wf = 0;
			if (rframe > 5)
				rdir = 1;
			if (rframe < 1)
				rdir = 0; 

			if (respawncounter == 1)
			{
				player_active = 1;
				player_control = 1;
				invulnerability = VOLNERBLE_TIME;
				player->Get_Sprite()->Setx(440);
				player->Get_Sprite()->Sety(600);
				player->Set_Hits(ONELIVE);
			}
			if (invulnerability == 1)
			{
				invulnerability = 0;
				invm = 0;
			}
			if (respawncounter > 0)
				respawncounter -= 1;
			if (invulnerability > 0)
			{
				invulnerability -= 1;
				if (invm == 0)
					invm = 1;
				else
					invm = 0;
			}


			if (procounter == 0 && ov && pripro > 0)
			{
				procounter = 30;
				pripro -= 1;
			}
			if (procounter > 0)
				procounter -= 1;

			if (tagger>0)
				tagger = tagger - 1;
			if (gun_attack > 0)
				gun_attack -= 1;

			Draw_Dialog();

			if (ov)
			{
				loser->Draw(229, 200);
				loser_time->Draw(480, 445, &prfram[(pripro)]);

				Get_Loss();
			}
			if (continued)
			{
				tbcont->Draw(0, 0);
				contcounter += 1;
			}
			if (contcounter > 400)
				menu_gameover = true;
			if (pripro == 0 && ov == 1)
					menu_gameover = true;

			if(!guide)
				unicounter += 1;

			sdl_setup->End();
		}
	}
/*
	while(!quit) 
	{	
		sdl_setup->Start();

		SDL_Delay(delay);	

		sdl_setup->End();
	}
*/
}