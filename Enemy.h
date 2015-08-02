#ifndef _ENEMY
#define _ENEMY
#include"Data.h"
#include"Bullet.h"
#include"Explosion.h"
#include"Player.h"

class Enemy{
public:
	Enemy();
	~Enemy();
	void Draw(int second);
	void Set(double x, double y, double speed, double rad, Texture tex, int second, bool damage, int patarn);
	double X();
	double Y();
	double CX();
	double CY();
	double Radius();
	bool Core();
	bool Exist();
	bool Accept();
	bool Crash(double x, double y);
	bool Shoot();
	bool Fire(Bullet *bullet, Player *player);
	void death(Explosion *exp);
	void Reset();
private:
	void Move();
	void Start(int second);
	void End();
	void ShootPatarn(int patarn);
	double Rad(int num);
	Texture ene;
	double x, y, speed, rad, b_rad;
	int second, shoot, flame, way, fire;
	bool go, set, damage, saw, dep;
};

#endif