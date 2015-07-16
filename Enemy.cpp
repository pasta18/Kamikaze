#include"Enemy.h"

Enemy::Enemy(){
	shoot = 0;
	flame = 0;
	way = 0;
	fire = 0;
	go = false;
	set = false;
	saw = false;
}

Enemy::~Enemy(){

}

double Enemy::X(){
	return x;
}

double Enemy::Y(){
	return y;
}

double Enemy::CX(){
	return x + ene.width / 2;
}

double Enemy::CY(){
	return y + ene.height / 2;
}

double Enemy::Radius(){
	return ene.width / 2;
}

bool Enemy::Core(){
	return damage;
}

bool Enemy::Exist(){
	return go;
}

bool Enemy::Crash(double x, double y){
	double distance = sqrt(pow(CX() - x, 2.0) + pow(CY() - y, 2.0));
	if (distance <= ene.width / 2){
		return true;
	}
	
	return false;
}

void Enemy::death(Explosion *exp){
	if (go && !exp->Exist()){
		go = false;
		exp->Set(X(), Y());
		flame = 0;
	}
}

void Enemy::Set(double x, double y, double speed, double rad, Texture tex, int second, bool damage, int patarn){
	this->x = x;
	this->y = y;
	this->speed = speed;
	this->rad = rad;
	this->ene = tex;
	this->second = second;
	set = true;
	this->damage = damage;
	ShootPatarn(patarn);
	flame = 0;
}

void Enemy::ShootPatarn(int patarn){
	switch (patarn)
	{
	case 0:
		shoot = 60;
		way = 1;
		break;
	default:
		break;
	}
}

void Enemy::Move(){
	x -= speed * sin(rad);
	y += speed * cos(rad);
}

void Enemy::Start(int second){
	if (set && !go && second == this->second){
		go = true;
		saw = true;
	}
}

bool Enemy::Shoot(){
	bool flag = false;

	if (shoot <= flame && !damage){
		flag = true;
		fire = way;
		flame = 0;
	}
	flame++;

	return flag;
}

void Enemy::Fire(Bullet *bullet){
	if (!bullet->Exist()){
		if(way == 1)bullet->Set(CX(), CY(), BulletSpeed, 0);
	}
}

double Enemy::Rad(int num){
	double b_rad = 0.0;

	return b_rad;
}

void Enemy::End(){
	if (x < -20 || x > widthMax + 20 || y < -16 || y > heightMax + 20){
		go = false;
		set = false;
		saw = false;
	}
}

void Enemy::Draw(int second){
	if (set){
		Start(second);
		End();
		if (go){
			Move();
		}
		if (saw && !go){
			flame++;
			if (flame >= 18){
				saw = false;
				set = false;
				flame = 0;
			}
		}
		if(saw) ene.draw(x, y);
	}
}