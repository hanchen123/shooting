#pragma once
#include "StdAfx.h"
#include "SDL_Setup.h"
#include "Player.h"
#include "Land_Scape.h"
#include "Intro_Board.h"
#include "Intro_Narrative.h"
#include "Dialog.h"
#include <time.h>

const int FPS = 32;	
const int GAME_SPEED = 2;
const int LAND_CAP = 244;
const int GROUND_ALL_CAP = 25;
const int TURRET_CAP = 20;
const int DRUM_CAP = 20;

const int GUNBOAT_CAP = 5;

const int AIR_CAP = 15;
const int AIR2_CAP = 24;
const int AIR_ALL_CAP = 49;
const int AIR2_ALL_CAP = 60;
const int AIR_PATTERN_CAP = 28;

const int LIGHTNING_CAP = 5;
const int LIGHTNING_SPLIT_CAP = 8;
const int LIGHTNING_SPEED = 40;
const int LIGHTNING_DAMAGE = 3;
const int LAZER_CAP = 15;
const int LAZER_SPLIT_CAP = 20;
const int LAZER_SPEED = 30;

const int PELLET_SPEED = 6;
const int PELLET_CAP = 30;	
const int BULLET_CAP = 20;	//player shooting onetime
const int BULLET_SPEED = 50;	
const int PLAYER_DAMAGE = 1;
const int STRIKE_CAP = 40;
//boss1
const int PLASMA_SPEED = 12;
const int PLASMA_CAP = 40;
const int PLASMA_SPLIT_CAP = 20;
const int PLASMA_DAMAGE = 3;
const int PELLET_DAMAGE = 1;
//boss2
const int CHARGE_SPEED = 30;

const int DRUM_EXPL_CAP = 10;
const int EXPL_CAP = 20;
const int TURRET_PELLET_SHOOTING_SPEED = 50;
const int GROUND_PELLET_SHOOTING_SPEED = 50;
const int RENEW_TIME = 50;
const int VOLNERBLE_TIME = 50;	//can't be hit
const int HIT_RANGE = 50;	//being hit distance
const int SPLIT_CAP = 10;	
const int scoll_frame[20][4] = {{1,0,0,50}, {2,0,1,100}, {1,1,0,200}, {2,1,2,100}, {1,2,0,300}, {2,2,3,100}, {1,3,0,300}, {2,3,4,100}, {1,4,0,200}, {2,4,5,100}, 
{1,5,0,200}, {2,5,6,100}, {1,6,0,300}, {2,6,7,100}, {1,7,0,300}, {2,7,8,100}, {1,8,0,300}, {2,8,9,100}, {1,9,0,300}, {2,9,0,100}};		
//{scolling flag, current picture index, next picture index, last time}
int const bossatpattern[2][42] = {{81,6,6,6,6,6,6,40,4,80,4,40,10,10,10,10,10,10,2,50,6,6,6,6,6,6,6,6,6,6,6,20,4,80,4,10,10,10,4,4,70},
{1,1,1,1,1,1,1,11,12,13,7,3,6,6,6,6,6,6,8,1,1,1,1,1,1,1,1,1,1,1,6,11,12,13,7,3,6,6,8,1}};
int const bosspattern[12][3] = {{80,0,4}, {30,0,0}, {42,6,3}, {70,(-4),1}, {70,(-4),(-1)}, {80,6,(-3)}, {30,0,4}, {25,(-6),(-2)}, {50,0,0}, {30,(-5),2}, 
{70,4,0}, {25,(-5),(-1)}};
//{moving time, x, y}
int const bosspatt2[11][3] = {{130,0,3}, {80,3,0}, {90,(-3),1}, {50,(-1),(-1)}, {60,1,(-2)}, {40,(-3),2}, {20,(-2),(-1)}, {70,1,(-1)}, {50,2,2}, {40,2,(-1)}, {30,(-3),1}};
int const btcuess[5][2] = {{6220,390}, {6500,10}, {7900,450}, {9600,30}, {9601,380}};
int const firingbo[10] = {36, 20, 1, 24, 16, 48, 1, 30, 26, 1};

class Game
{
public:
	Game(int screen_w, int screen_h);
	~Game(void);
	void Start(void);

	void Draw_Storyboard(void);
	void Draw_Narrative(void);
	void Intro_Getinput(void);

	void Draw_Dialog(void);
	void Draw_Dialog1(void);
	void Draw_Dialog2(void);
	void Draw_Dialog3(void);
	void Draw_Dialog4(void);
	void Get_Loss(void);

	void Draw_Menuboard(void);
	void Menu_Getinput(void);

	void Read_Map(void);
	void Draw_Landscape(void);

	void Read_Groundarmy(void);
	void Init_Ground(int xg, int yg, int tg);
	void Draw_Ground(void);
	void One_Time(void);
	void Init_Drum(int that);
	void Check_Drum(void);

	void Init_Gunboat(int xbot);
	void Init_GunboatT(int tux, int tuy);
	void Draw_Gunboat(void);

	void Read_Airarmy(void);
	void Init_Air(int ax, int ay, int ty, int pa);
	void Init_Air2(int ax, int ay, int ty, int pa);
	void Draw_Air(void);
	void Draw_Air2(void);

	void Init_Lazer(int lzzx, int lzzy, int lzzt);
	void Draw_Lazer(void);
	bool Checklz(int stmx, int stmy, int stty);
	void Initlzhit(int lzhx, int lzhy, int lzht);
	void Drawlzhit(void);

	void Init_Lightning(int ligx, int ligy);
	void Draw_Lightning(void);
	bool Checkln(int chcxx, int chcyy);
	void Init_Sp(int xspq, int yspq);
	void Draw_Sp(void);

	void Init_Turret(int tux, int tuy);
	void Draw_Turret(void);

	void Turret_Shoot(int x, int y, int angle);
	void Init_Muzflash(int mfx, int mfy);
	void Draw_Muzflash(void);
	void Beg_Shell(int begs, int begy, int dhsx, int dhsy);

	void Init_Pellets(int px, int py, int pt);
	void Draw_Pellets(void);

	void Draw_Player(void);
	void Attack(void);
	void Geass(void);
	void Init_Streak(int bx, int by);
	void Draw_Streak(void);

	void Draw_HM(void);
	void Draw_Lives(void);
	void Draw_Points(void);

	bool Hit_Player (int hitpx, int hitpy, int prox);
	void Init_Split(int splx, int sply, int splt);
	void Draw_Split(void);
	void Init_Playerexpl(int pexx, int pexy);
	void Draw_Playerexpl(void);

	int Check_Hit(int chkx, int chky);
	void Init_Strike(int strx, int stry);
	void Draw_Strikes(void);

	void Init_Drumexpl(int dx,int dy);
	void Draw_Drumexpl(void);
	void Init_Expl(int ex, int ey);
	void Draw_Expl(void);

	void Draw_Warning(void);
	void Init_Boss(void);
	void Draw_Boss(void);
	int Check_Bosshit(int bshitx, int bshity);
	bool Collide(int collx, int colly, int collp);
	void Draw_Spghit(void);
	void Init_Plasma(int pmx, int pmy);
	void Draw_Plasma(void);
	void Init_Plasmahit(int plx, int ply);
	void Draw_Plasmahit(void);
	void Boss_Destroyed(void);

	void Draw_Boss2(void);
	int Check_Bosshit2(int bs2hx, int bs2hy);
	void Boss_Destroyed2(void);

	void Draw_Transition(void);
	void Reset(void);

private:
	int screen_w;
	int screen_h;
	int delay;
	bool quit; 

	bool introduction;	//introduction flag
	bool intro_done; //if introduction finished
	int intro_idx;	//introduction picture index
	int intro_lastime;	//picture frame index, or picture duration
	Uint32 intro_time;	//introduction time slice
	Intro_Board* story_board;

	int intro_narr_idx;	//introduction narrative index
	Intro_Narrative* story_words;
//dialog init
	bool guide;
	int dialog_lastime;
	int dial_idx;
	Land_Scape* dialog1;
	Land_Scape* dialog2;
	Land_Scape* dialog3;
	Dialog* dial;
//menu init
	bool mainmenu; //mainmenu flag
	bool menu_gameover;
	Uint32 menu_time;	//mainmenu time slice
	Sprite* menu_board;
	Sprite* menu_options;
	Sprite* menu_logo;

	int current_level;	//game level
	int scape_count;	//landscape counter
	int sec_scapect;	//time counter
	int level[LAND_CAP][10];	//landscape elements
	SDL_Rect land_scape[35];	//landscape picture index
	Land_Scape* land;
	Uint32 game_time;
//game over
	bool ov;
	int pripro;
	int procounter;	//game over counter
	SDL_Rect prfram[6];	//loser time wrap
	Land_Scape* loser;
	Land_Scape* loser_time;
//drum
	bool onetime;	//if drum
	int numdrums; //num of drum
	int drums[DRUM_CAP][4];
//global
	int unicounter;	//game counter
	int transtatus;	//change level flag
	int transposit; //trans x start
	int continued;	
	int contcounter;
	Land_Scape* transit;
	Land_Scape* tbcont;
//waks wrap counter
	int wf;
	int rdir;
	int rframe;
//mark by ship on water
	Land_Scape* wake;	
	Land_Scape* mwake;	
	Land_Scape* wak;
	SDL_Rect waks[3];
//ground army shadow
	Land_Scape* grshadow;
	SDL_Rect shadg[4];
//ground army 
	int groundtar[10][10];	//ground army
	int grncue[GROUND_ALL_CAP][4];	//{time, x, y, army type}
	int numgr;	//num of ground army in a screen
	int grq;	//total num of ground army in a game
	int groundact;	//num of ground army exist except for dead
//gunboat
	int btcue;	//boat counter
	int quantgbt;	//num of boat
	int benct;	//engine counter
	int gunb[GUNBOAT_CAP][4];	
	SDL_Rect qpl[2];	//wave wrap
	Mix_Chunk* bigeng;
	Land_Scape* gboat;
	Land_Scape* scba;	//wave by gunboat
//air army
	int numhells;
	int cuer;	//counter 
	int cl2q;
	int alienqun;	//num of air army
	int numal2;
	int alienstats[AIR_CAP][20];	//air army
	int aliencl[AIR2_CAP][25];
	int aliencues[AIR_ALL_CAP][5];	//{time, x, y, air type, moving type}
	int cl2alcue[AIR2_ALL_CAP][5];
	int atpattern[AIR_PATTERN_CAP][20];	//{time, x, y}{shooting time}
	SDL_Rect aliens[2][9];	//air army wrap
	SDL_Rect clalfr[2][8];
	Mix_Chunk* bitbos;
	Land_Scape* alienstuff;
	Land_Scape* aliencl2; 
//gfire 
	int hgunct;	//heligun counter
	SDL_Rect gff[9];	//gfire wrap
	Land_Scape* gfire;
	Mix_Chunk* zap;
	Mix_Chunk* biglazer;
	Mix_Chunk* heligun;
//lazer
	int quantlz;	//num of lazer
	int quanhz;	//num of lazer split
	int bloss[LAZER_SPLIT_CAP][5];	//lazer split
	int allz[LAZER_CAP][5];
	SDL_Rect hfr[12];	//lazer split wrap
	SDL_Rect lazz[3];	//lazer wrap
	Land_Scape* alienla;
	Land_Scape* blos;
//lightning
	int numlight;	//num of lightning
	int numspk;	//num of lightning split
	int sprk[LIGHTNING_SPLIT_CAP][4];	//lightning split
	int bolt[LIGHTNING_CAP][5];	//lightning 
	SDL_Rect spkl[6];	//lightning split wrap
	Land_Scape* hitter;
	Land_Scape* electricity;
//turrets
	Land_Scape* turret;
	int tur_counter;
	int qutur;	//num of turret
	int turr[TURRET_CAP][9];
	std::vector<std::vector<int> > turcue;
	SDL_Rect turretfr[2][48];	//turret wrap
	Mix_Chunk* artil;
//muzflash
	int qumzfl;	//num of turret muzflash
	int muf[10][5];
	SDL_Rect mffr[3];	//turret muflash wrap
	Land_Scape* muflash;
//tank and ship
	Land_Scape* tank;
	SDL_Rect tafr[2][5];	//[army_type][status]
//pellets
	Land_Scape* circ;
	SDL_Rect circc[4];
	Mix_Chunk* fifthe; //ground army emit pellets
	Land_Scape* pellet;
	SDL_Rect pelltt[5];		//pellets wrap
	int pellets[PELLET_CAP][6];		//{if empty, x, y, type, xmove, ymove}
	int quanpel;	//num of pellets
	int pfr;
//player
	int player_active;	//is player alive
	int player_control;
	int player_dir;		//direction
	int pe;
	int explopr;
	Land_Scape* tail;
	Land_Scape* pshadow;
	Player* player;
	SDL_Rect pipe[3];	//tail wrap
	SDL_Rect schmesh[5];	//shadow wrap
	SDL_Rect schmetfr[3][5];	//player machine
//geass
	int icon_counter;
	int icon_dir;
	int geass_counter;
	Land_Scape* geass_icon;
	Land_Scape* geass;
	SDL_Rect geasi[3];	//geass icon wrap
	SDL_Rect geas[18];	//geass wrap
//HPMP, points
	Land_Scape* points;
	Land_Scape* heart;
	Land_Scape* slot;
	Land_Scape* hpmp;
	SDL_Rect pts[10];
	SDL_Rect hrt[5];	//lives wrap
	SDL_Rect hp[ONELIVE + 1];	//hp wrap
	SDL_Rect mp[3*GEASS + 1];	//mp wrap
//being hit
	int invm;	//if being hit
	int schmhit;
	int respawncounter;	//refresh counter
	int invulnerability;	//being hit counter;
	int quanspt;	//num of split
	int splitct[SPLIT_CAP][5];
	SDL_Rect scat[34];	//being hit split wrap
	SDL_Rect scatf[10];
	Land_Scape* scatter;
	Land_Scape* scatterf;
//gun fire
	int gun_attack;	//fire sound counter
	int bullnum; //num of bullets
	int bulx[BULLET_CAP][3];
	Land_Scape* gunf;	
	Land_Scape* strek;
	SDL_Rect fg[2]; //gun fire wrap
	Mix_Chunk* machinegun;
//warning
	int warnstatus;
	int warnfr;	//wrap counter
	SDL_Rect wrn[5];
	Mix_Chunk* warner;
	Land_Scape* warning;
//boss
	int boss_active;
	int bosscha[17];	//boss properties
	SDL_Rect bss[2][6];	//boss wrap
	Land_Scape* boss;
	Mix_Music* boss_level;
//boss weapon
	int laseron;	//laser
	int prspg;	//lazer split counter
	int spghit;	//laser hit
	int spghitloc;	//laser location
	int quanp;	//num of plasma
	int qunplspl; //num of plasma split
	int passm[PLASMA_CAP][5];	//plasma
	int plasp[PLASMA_SPLIT_CAP][4];
	Land_Scape* beam;
	Land_Scape* pulse;
	Land_Scape* plas;
	Land_Scape* plasplo;	//plasma split
	Land_Scape* sprug;	//lazer split
	SDL_Rect spgct[6];	//lazer split wrap
	SDL_Rect puf[4];	//laser shoot wrap
	SDL_Rect beamf[2];	//beam wrap
	SDL_Rect plasm[3][2];	//plasma wrap
	SDL_Rect plsfr[9];	//plasma split wrap
	Mix_Chunk* bosspl;
	Mix_Chunk* cutt;
	Mix_Chunk* thirde;
//boss2
	int charge;
	int charge_x;
	int charge_y;
	int charge_r;
	int ready;
	SDL_Rect scfmm[2][6];
	Mix_Chunk* fourth;
	Land_Scape* sscorpion;
//strikes
	int strikes[STRIKE_CAP][4];
	int numstrikes; //num of strikes
	int tagger;	//hit sound counter
	Land_Scape* splat;
	SDL_Rect strikefr[4]; //strikes wrap
	Mix_Chunk* tag;
//explosion
	int secondexx[DRUM_EXPL_CAP][4];	//drum explosion
	int explosions[EXPL_CAP][4];	//explosion
	int nmexpsec;	//num of drum explosion
	int numexp;	//num of explosion
	SDL_Rect exploss[14];	//drum explosion wrap
	SDL_Rect explofr[14];	//explosion wrap
	Mix_Chunk* seconde;
	Mix_Chunk* boom;
	Land_Scape* secondex;	//explosion picture
	Land_Scape* explo;
//player explosion
	int pexp[3];	//player explosion position
	SDL_Rect pex[13];	//player explosion wrap
	Mix_Chunk* playerblow;	//player explosion sound
	Land_Scape* pexplo;
//boss explosion
	int explocounter;

	SDL_Setup* sdl_setup;
};

