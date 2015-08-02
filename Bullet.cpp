#include"Bullet.h"

Bullet::Bullet(){
	bullet = Texture::Texture(L"Data/Texture/Bullet.png");
	sound = Sound::Sound(L"Data/Audio/shot.mp3");
	exist = false;
	saw = false;
	flag = false;
}

Bullet::~Bullet(){

}

void Bullet::Reset(){
	exist = false;
	saw = false;
}

void Bullet::Set(double x, double y, double speed, double rad){
	this->x = x - bullet.width / 2;
	this->y = y - bullet.height / 2;
	exist = true;
	saw = true;
	this->speed = speed;
	this->rad = rad;
	flame = 0;
	flag = false;
	sound.play();
}

double Bullet::X(){
	return x;
}

double Bullet::Y(){
	return y;
}

double Bullet::CX(){
	return x + bullet.width / 2;
}

double Bullet::CY(){
	return y + bullet.height / 2;
}

double Bullet::Radius(){
	return bullet.width / 2;
}

bool Bullet::Exist(){
	return exist;
}

void Bullet::End(){
	if (x < -20 || x > widthMax + 20|| y < -16 || y > heightMax + 20){
		exist = false;
	}
}

bool Bullet::Crash(double x, double y){
	double distance = sqrt(pow(CX() - x, 2.0) + pow(CY() - y, 2.0));
	if (distance <= bullet.width / 2){
		return true;
	}

	return false;
}

void Bullet::death(Explosion *exp){
	if (!flag && !exp->Exist()){
		flag = true;
		exp->Set(X(), Y());
		flame = 0;
	}
}

void Bullet::Move(){
	x -= speed * sin(rad);
	y += speed * cos(rad);
}

void Bullet::Draw(){
	if (exist){
		End();
		Move();
		if (flag){
			flame++;
			if (flame >= 18){
				saw = false;
				exist = false;
				flag = false;
				flame = 0;
			}
		}
		if (saw) bullet.draw(x, y);
	}
}