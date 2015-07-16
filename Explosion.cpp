#include"Explosion.h"

Explosion::Explosion(){
	exp[0] = Texture::Texture(L"Data/Texture/exp1.png");
	exp[1] = Texture::Texture(L"Data/Texture/exp2.png");
	exp[2] = Texture::Texture(L"Data/Texture/exp3.png"); 
	exp[3] = Texture::Texture(L"Data/Texture/exp4.png");
	exp[4] = Texture::Texture(L"Data/Texture/exp5.png");
	exp[5] = Texture::Texture(L"Data/Texture/exp6.png");
	exp[6] = Texture::Texture(L"Data/Texture/exp7.png");
	exist = false;
	now = 0;
}

Explosion::~Explosion(){

}

void Explosion::Reset(){
	exist = false;
}

bool Explosion::Exist(){
	return exist;
}

void Explosion::Set(double x, double y){
	if (!exist){
		this->x = x;
		this->y = y;
		exist = true;
		now = 0;
	}
}

void Explosion::Draw(){
	if (exist){
		exp[(int)now].draw(x, y);
		now += 0.25;
		if (now >= 7){
			exist = false;
			now = 0;
		}
	}
}