#ifndef _BACKGROUND
#define _BACKGROUND

#include"Data.h"

const int point = 100;

class BackGround{
public:
	BackGround();
	~BackGround();
	void Draw();
private:
	int dotx[point], doty[point];
	int scale[point], clear[point];
	int speed[point];
	void Move();
	void Set();
	void Reset(int number);
};

#endif