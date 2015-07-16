#ifndef _ENEMY
#define _ENEMY
#include"Data.h"
#include"Bullet.h"
#include"Explosion.h"

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
	void Fire(Bullet *bullet);
	void death(Explosion *exp);
private:
	void Move();
	void Start(int second);
	void End();
	void ShootPatarn(int patarn);
	double Rad(int num);
	Texture ene;
	double x, y, speed, rad;
	int second, shoot, flame, way, fire;
	bool go, set, damage, saw;
};

#endif