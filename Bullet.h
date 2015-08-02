#ifndef _BULLET
#define _BULLET

#include"Data.h"
#include"Explosion.h"

class Bullet{
public:
	Bullet();
	~Bullet();
	void Draw(); // 描画含むprivateの関数を外から実行する関数
	double X(); // xを返す
	double Y(); // yを返す
	double CX(); // 中心のx座標を返す
	double CY(); // 中心のy座標を返す
	double Radius(); // 半径を返す
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
	Sound sound;
};

#endif