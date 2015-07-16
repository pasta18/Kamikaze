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
	bool Exist();
	void Set(int second, int stage);
	bool Crash(double x, double y);
	bool Shoot(Bullet *bullet, int stage, Player *player);
	void Draw();
	bool Win();
	bool Clear();
	void Death(Explosion *exp);
	void start(int second);
	bool End();
private:
	Texture boss[block], boss1, boss2, core;
	void Move();
	void Fade();
	void Reset();
	void texSet();
	int num[block]; // どの部分がどのパーツかを格納
	int born, flame, bang, bomb, fade, Fflame;
	double x, y, speed;
	bool right, saw, exist, set, clear;
};

#endif