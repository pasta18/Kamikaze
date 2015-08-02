#ifndef _PLAYER
#define _PLAYER

#include"Data.h"

class Player{
public:
	Player();
	~Player();
	void Draw();
	double X();
	double Y();
	double CX();
	double CY();
	bool Exist();
	bool Bomb();
	bool BombStock();
	bool Spawn();
	bool End();
	int Stock();
	void Win();
	bool Over();
	bool Clear();
	void Reset();
	void Set();
	bool Crash(double x, double y, double radius);
private:
	void Move();
	void Death();
	void Respawn();
	void Barrier();
	Texture play;
	Sound sound;
	double x, y, tough;
	bool exist, saw, barrier, bomb, respawn, clear, over;
	int flame, stock;
	int barrierRadius;
};

#endif