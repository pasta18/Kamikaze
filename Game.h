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
	bool end, win;
	int flame, second, endFlame, stage, select;
	Player *player;
	Enemy *enemy[20];
	Explosion *exp[50];
	Bullet *bul[50];
	Boss *boss;
	Status status = Start;
	Font font;
	Texture title, normalEne, core, menu;
};

#endif