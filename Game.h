#ifndef _GAME
#define _GAME

#include"Enemy.h"
#include"Player.h"
#include"Data.h"
#include"Boss.h"
#include"BackGround.h"

enum Status{
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
	void Time();
	void pause();
	void Crash();
	void Menu();
	void Shoot();
	void AddEnemy();
	bool end, win, add;
	int flame, second, endFlame, stage, select, num;
	Player *player;
	Enemy *enemy[20];
	Explosion *exp[50];
	Bullet *bul[50];
	Boss *boss;
	BackGround *backGround;
	Status status = Start;
	Font font;
	Texture normalEne, core, menu;
	Sound title, battle, exp2, button, cancel;
};

#endif