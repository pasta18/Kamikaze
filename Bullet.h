#ifndef _BULLET
#define _BULLET

#include"Data.h"
#include"Explosion.h"

class Bullet{
public:
	Bullet();
	~Bullet();
	void Draw(); // �`��܂�private�̊֐����O������s����֐�
	double X(); // x��Ԃ�
	double Y(); // y��Ԃ�
	double CX(); // ���S��x���W��Ԃ�
	double CY(); // ���S��y���W��Ԃ�
	double Radius(); // ���a��Ԃ�
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