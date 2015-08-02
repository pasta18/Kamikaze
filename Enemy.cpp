#include"Enemy.h"

Enemy::Enemy(){
	shoot = 0;
	flame = 0;
	way = 0;
	b_rad = 0;
	fire = 0;
	go = false;
	set = false;
	saw = false;
	dep = false;
}

Enemy::~Enemy(){

}

void Enemy::Reset(){
	shoot = 0;
	flame = 0;
	way = 0;
	b_rad = 0;
	fire = 0;
	go = false;
	set = false;
	saw = false;
	dep = false;
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
		dep = false;
		b_rad = Rad(patarn);
		break;
	case 1:
		shoot = 60;
		way = 3;
		dep = false;
		b_rad = Rad(patarn);
		break;
	case 2:
		shoot = 60;
		way = 1;
		dep = true;
		b_rad = Rad(patarn);
		break;
	case 3:
		shoot = 60;
		way = 3;
		dep = true;
		b_rad = Rad(patarn);
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
	if (!saw && set && !go && second == this->second){
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

bool Enemy::Fire(Bullet *bullet, Player *player){
	if (!bullet->Exist()){
		if (dep){
			double tmp = atan((CX() - player->CX()) / abs(CY() - player->CY()));

			if (way == 1) bullet->Set(CX(), CY(), BulletSpeed, 0 + tmp);
			if (way == 3) bullet->Set(CX(), CY(), BulletSpeed / 2, b_rad - (way - fire) * Radians(30) + tmp);
		}
		else{
			if (way == 1) bullet->Set(CX(), CY(), BulletSpeed, 0);
			if (way == 3) bullet->Set(CX(), CY(), BulletSpeed, b_rad - (way - fire) * Radians(30));
		}
	}
	fire--;
	if (fire <= 0) return false;
	return true;
}

bool Enemy::Accept(){
	return !set;
}

double Enemy::Rad(int num){

	if (num == 1 || num == 3) return Radians(30);

	return 0.0;
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