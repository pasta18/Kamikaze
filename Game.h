#ifndef _GAME
#define _GAME

#include"Enemy.h"
#include"Player.h"
#include"Data.h"
#include"Boss.h"
#include"BackGround.h"

enum Status{
	Loading,
	Start,
	Playing,
	Pause,
	Result,
};

class Game{
public:
	Game();	
	~Game();
	void Draw();
private:
	void Title();
	void Play();
	void End();
	void Load();
	void Time();
	void pause();
	void Crash();
	void Menu();
	void Shoot();
	void AddEnemy();
	bool end, win, add, GameStart, s_on, b_on, up;
	int flame, second, endFlame, stage, select, num, blackFlame;
	int tmpStock, s_flame, b_flame;
	int logo_flame, load_flame;
	Player *player;
	Enemy *enemy[20];
	Explosion *exp[50];
	Bullet *bul[50];
	Boss *boss;
	BackGround *backGround;
	Status status = Loading;
	Font font;
	Image TitleBack, StartButton, EndButton, TitleLogo, AllTitle;
	Texture normalEne, core, titleTexture[70];
	Texture t_back, t_start, t_end, t_logo, t_start_on, t_end_on;
	Texture menu, Stock[5], On, Off;
	Rect black;
	Sound title, battle, exp2, button, cancel;
};

#endif