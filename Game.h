#ifndef _GAME
#define _GAME

#include"Enemy.h"
#include"Player.h"
#include"Data.h"
#include"Boss.h"

enum Status{
	Start,
	Playing,
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
	Status status = Start;
	Font font;
	Texture normalEne, core, menu;
};

#endif