#ifndef _BOSS
#define _BOSS

#include"Data.h"
#include"Bullet.h"
#include"Player.h"
#include"Explosion.h"

const int block = 25; // 5マス × 5マス

class Boss{
public:
	Boss();
	~Boss();
	double X(int num);
	double Y(int num);
	double CX(int num);
	double CY(int num);
	int Block();
	bool Exist();
	void Set(int second, int stage);
	bool Crash(double x, double y, Player *player);
	bool Shoot(Bullet *bullet, int stage, Player *player);
	void Draw();
	bool Win();
	bool Clear();
	void Death(Explosion *exp);
	void bitDeath(int number, Explosion *exp);
	void start(int second);
	bool End();
	bool bitCrash(int number);
private:
	Texture boss[block], boss1, boss2, core, enemy;
	void Move();
	void Fade();
	void Reset();
	void texSet();
	int num[block]; // どの部分がどのパーツかを格納
	bool bitFlag[block]; // enemyをボスに組み込むときに使う
	int born, flame, bang, bomb, fade, Fflame;
	double x, y, speed;
	bool right, saw, exist, set, clear;
	Sound exp2, exp3;
};

#endif