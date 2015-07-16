#ifndef _BULLET
#define _BULLET

#include"Data.h"
#include"Explosion.h"

class Bullet{
public:
	Bullet();
	~Bullet();
	void Draw();
	double X();
	double Y();
	double CX();
	double CY();
	double Radius();
	bool Crash(double x, double y);
	bool Exist();
	void Reset();
	void death(Explosion *exp);
	void Set(double x, double y, double speed, double rad);
private:
	Texture bullet;
	void Move();
	void End();
	double x, y, speed, rad;
	int flame = 0;
	bool exist, saw, flag;
};

#endif