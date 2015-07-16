#include"Player.h"

Player::Player(){
	play = Texture::Texture(L"Data/Texture/player.png");
	x = firstX;
	y = firstY;
	flame = 0;
	exist = true;
	saw = true;
	bomb = true;
	barrier = false;
	respawn = false;
	stock = 4;
	clear = false;
	barrierRadius = 20;
	tough = 0;
	over = false;
}

Player::~Player(){

}

double Player::X(){
	return x;
}

double Player::Y(){
	return y;
}

double Player::CX(){
	return x + play.width / 2;
}

double Player::CY(){
	return y + play.height / 2;
}

bool Player::Exist(){
	return exist;
}

void Player::Set(){
	exist = true;
	saw = true;
	bomb = true;
	barrier = false;
	over = false;
	stock = 4;
	flame = 0;
	tough = 0.0;
	clear = false;
	x = firstX;
	y = firstY;
}

bool Player::Bomb(){
	return barrier;
}

bool Player::BombStock(){
	return bomb;
}

void Player::Move(){
	bool slant = false;
	double speed = Speed;

	if (Input::KeyLShift.pressed || Input::KeyRShift.pressed) speed /= 2;

	if (Input::KeyUp.pressed){
		if (Input::KeyRight.pressed){
			slant = true;
			x += speed * cos(Pi / 4);
		}
		if (Input::KeyLeft.pressed){
			slant = true;
			x -= speed * cos(Pi / 4);
		}

		if (slant) y -= speed * sin(Pi / 4);
		else y -= speed;
	}
	else if (Input::KeyDown.pressed){
		if (Input::KeyRight.pressed){
			slant = true;
			x += speed * cos(Pi / 4);
		}
		if (Input::KeyLeft.pressed){
			slant = true;
			x -= speed * cos(Pi / 4);
		}
		if (slant) y += speed * sin(Pi / 4);
		else y += speed;
	}
	else{
		if (Input::KeyRight.pressed){
			x += speed;
		}
		if (Input::KeyLeft.pressed){
			x -= speed;
		}
	}
	// Šˆ“®ŒÀŠE
	if (x < 0) x = 0;
	if (x > widthMax) x = widthMax;
	if (y < 4) y = 4;
	if (y > heightMax) y = heightMax;
}

bool Player::Crash(double x, double y, double radius){
	double distance = sqrt(pow(CX() - x, 2.0) + pow(CY() - y, 2.0));
	if (distance <= radius) {
		exist = false;
		return true;
	}
	return false;
}

void Player::Barrier(){
	if (barrier){
		const Circle circle(CX(), CY(), barrierRadius);
		circle.drawFrame((int)tough, 0, Color(0, 100, 200, 150));
		tough -= 0.1;
		if (!saw) tough = 0.0;
		if (tough <= 0.0) barrier = false;
	}
}

void Player::Death(){
	if (!exist && saw){
		flame++;
		if (flame >= 18){
			saw = false;			
			flame = 0;
		}
	}
}

void Player::Respawn(){
	if (respawn){
		flame++;
		if (flame >= 120) {
			flame = 0;
			respawn = false;
		}
	}
}

bool Player::Clear(){
	return clear;
}

void Player::Win(){
	clear = true;
}

bool Player::Spawn(){
	return respawn;
}

int Player::Stock(){
	return stock;
}

bool Player::End(){
	if (stock <= 0){
		return true;
	}
	return false;
}

bool Player::Over(){
	return over;
}

void Player::Draw(){
	if (stock > 0 && !saw){
		flame++;
		if (flame >= 10){
			flame = 0;
			x = firstX;
			y = firstY;
			stock--;
			bomb = true;
			respawn = true;
			exist = true;
			saw = true;
		}
	} else if (!saw){
		over = true;
	}
	if (respawn) Respawn();
	if (exist && !clear) Move();
	if (saw) {
		Death();
		if (respawn) play.draw(x, y, Alpha(100));
		else play.draw(x, y);
	}
	if (bomb && Input::KeyZ.pressed){
		bomb = false;
		barrier = true;
		tough = (double)barrierRadius;
	}
	if (barrier) Barrier();
	if (Input::KeyLShift.pressed || Input::KeyRShift.pressed) Circle(CX(), CY(), 4.0).draw(Palette::Red);
}