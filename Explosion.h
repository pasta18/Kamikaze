#ifndef _EXPLOSION
#define _EXPLOSION
#include"Data.h"

class Explosion{
public:
	Explosion();
	~Explosion();
	void Draw();
	void Reset();
	void Set(double x, double y);
	bool Exist();
private:
	Texture exp[7];
	double now;
	double x, y;
	bool exist;
};

#endif