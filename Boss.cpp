#include"Boss.h"

Boss::Boss(){
	boss1 = Texture::Texture(L"Data/Texture/Boss1.png");
	boss2 = Texture::Texture(L"Data/Texture/Boss2.png");
	core = Texture::Texture(L"Data/Texture/Boss3.png");
	enemy = Texture::Texture(L"Data/Texture/Enemy.png");
	exp2 = Sound::Sound(L"Data/Audio/exp2.mp3");
	exp3 = Sound::Sound(L"Data/Audio/exp3.mp3");
	saw = false;
	exist = false;
	right = false;
	fade = false;
	flame = 0;
	Fflame = 0;
	bang = 0;
	set = false;
	for (int i = 0; i < block; i++){
		num[i] = 0;
		bitFlag[i] = false;
	}
	bomb = 0;
	clear = false;
}

Boss::~Boss(){

}

double Boss::X(int num){
	return x + (num % 5) * boss1.width;
}

double Boss::Y(int num){
	return y + (num / 5) * boss1.height;
}

double Boss::CX(int num){
	return X(num) + boss1.width / 2;
}

double Boss::CY(int num){
	return Y(num) + boss1.height / 2;
}

void Boss::Set(int second, int stage){
	Reset();
	fade = false;
	set = true;
	exist = false;
	saw = false;
	born = second;
	clear = false;
	for (int i = 0; i < block; i++){
		bitFlag[i] = false;
	}
	x = widthMax / 2 - boss1.width * 5 / 2;
	y = -boss1.height * 5;
	switch (stage){ // ボスの情報を設定
	case 1:
		num[0] = 5;
		num[1] = 6;
		num[2] = 6;
		num[3] = 6;
		num[4] = 2;
		num[5] = 7;
		num[9] = 7;
		num[10] = 7;
		num[12] = 1;
		num[14] = 7;
		num[15] = 7;
		num[19] = 7;
		num[20] = 4;	
		num[24] = 3;
		break;
	case 2:
		num[0] = 8;
		num[1] = 5;
		num[2] = 6;
		num[3] = 2;
		num[4] = 8;
		num[6] = 4;
		num[7] = 1;
		num[8] = 3;
		num[15] = 8;
		num[16] = 8;
		num[18] = 8;
		num[19] = 8;
		num[20] = 8;
		num[24] = 8;
	}
	texSet();
}

bool Boss::Win(){
	return (!exist && saw);
}

bool Boss::bitCrash(int number){
	return bitFlag[number];
}

bool Boss::Crash(double x, double y, Player *player){
	for (int i = 0; i < block; i++){
		if (num[i] == 0) continue;
		if (num[i] == 1){
			double distance = sqrt(pow(CX(i) - x, 2.0) + pow(CY(i) - y, 2.0));
			if (distance < core.width / 2){
				exist = false;
				flame = 0;
				bomb = 10;
			}
		}
		else if (num[i] == 8){
			double distance = sqrt(pow(CX(i) - x, 2.0) + pow(CY(i) - y, 2.0));
			if (distance < core.width / 2){
				if (!player->Bomb()) return true;
				bitFlag[i] = true;
			}
		}
		else{
			if (abs(CX(i) - x) < boss1.width / 2 && abs(CY(i) - y) < boss1.height / 2){
				return true;
			}
		}
	}
	return false;
}

void Boss::bitDeath(int number, Explosion *exp){
	if (bitCrash((number))){
		exp->Set(X(number), Y(number));
		exp2.playMulti();
	}
}

void Boss::Death(Explosion *exp){
	if (!exist && saw && bomb > 0 && flame == 0){
		if (bomb == 1){
			for (int i = 0; i < block; i++){
				if (num[i] == 1){
					exp->Set(X(i), Y(i));
					exp3.play();
					fade = true;
					Fflame = 255;
					break;
				}
			}
		}
		else{
			int bx = Random(-boss1.width, boss1.width);
			int by = Random(-boss1.width, boss1.width);
			for (int i = 0; i < block; i++){
				if (num[i] == 1){
					exp->Set(X(i) + bx, Y(i) + by);
					exp2.playMulti();
					break;
				}
			}
		}
		bomb--;
	}
	flame++;
	if (flame >= 20) flame = 0;
}

bool Boss::Shoot(Bullet *bullet, int stage, Player *player){
	if (!bullet->Exist()){
		if (bang == 0) flame++;
		if (flame >= 120) flame = 0;
		
		double rad = 0.0;

		switch (stage){
		case 1: // ステージごとにボスの弾は変わる
			if (flame == 60){
				switch (bang){
				case 0:
					bang = 9;
					break;
				case 1:
					bullet->Set(CX(20), CY(20), BulletSpeed / 2, 0);
					break;
				case 2:
					bullet->Set(CX(20), CY(20), BulletSpeed / 2, Radians(30));
					break;
				case 3:
					bullet->Set(CX(20), CY(20), BulletSpeed / 2, -Radians(30));
					break;
				case 4:
					bullet->Set(CX(24), CY(24), BulletSpeed / 2, 0);
					break;
				case 5:
					bullet->Set(CX(24), CY(24), BulletSpeed / 2, Radians(30));
					break;
				case 6:
					bullet->Set(CX(24), CY(24), BulletSpeed / 2, -Radians(30));
					break;
				case 7:
					rad = atan((CX(20) - player->CX()) / abs(CY(20) - player->CY()));
					bullet->Set(CX(20), CY(20), BulletSpeed / 3, rad);
					break;
				case 8:
					rad = atan((CX(24) - player->CX()) / abs(CY(24) - player->CY()));
					bullet->Set(CX(24), CY(24), BulletSpeed / 3, rad);
					break;
				default:
					break;
				}
				bang--;
			}
			break;
		case 2:
			if (flame%60 == 0){
				switch (bang){
				case 0:
					bang = 9;
					break;
				case 1:
					if (num[16] != 8) break;
					rad = atan((CX(16) - player->CX()) / abs(CY(16) - player->CY()));
					bullet->Set(CX(16), CY(16), BulletSpeed / 3, rad);
					break;
				case 2:
					if (num[18] != 8) break;
					rad = atan((CX(18) - player->CX()) / abs(CY(18) - player->CY()));
					bullet->Set(CX(18), CY(18), BulletSpeed / 3, rad);
					break;
				case 3:
					if (num[20] != 8) break;
					rad = atan((CX(20) - player->CX()) / abs(CY(20) - player->CY()));
					bullet->Set(CX(20), CY(20), BulletSpeed / 3, rad);
					break;
				case 4:
					if (num[24] != 8) break;
					rad = atan((CX(24) - player->CX()) / abs(CY(24) - player->CY()));
					bullet->Set(CX(24), CY(24), BulletSpeed / 3, rad);
					break;
				case 5:
					if (num[15] != 8) break;
					rad = atan((CX(15) - player->CX()) / abs(CY(15) - player->CY()));
					bullet->Set(CX(15), CY(15), BulletSpeed / 3, rad);
					break;
				case 6:
					if (num[19] != 8) break;
					rad = atan((CX(19) - player->CX()) / abs(CY(19) - player->CY()));
					bullet->Set(CX(19), CY(19), BulletSpeed / 3, rad);
					break;
				case 7:
					if (num[0] != 8) break;
					rad = atan((CX(0) - player->CX()) / abs(CY(0) - player->CY()));
					bullet->Set(CX(0), CY(0), BulletSpeed / 3, rad);
					break;
				case 8:
					if (num[4] != 8) break;
					rad = atan((CX(4) - player->CX()) / abs(CY(4) - player->CY()));
					bullet->Set(CX(4), CY(4), BulletSpeed / 3, rad);
					break;
				default:
					break;
				}
				bang--;
			}
			break;
		}
		if (bang == 0) return false;
	}
	return true;
}

void Boss::Reset(){
	for (int i = 0; i < block; i++){
		num[i] = 0;
	}
}

void Boss::texSet(){
	for (int i = 0; i < block; i++){
		if (num[i] == 1){
			boss[i] = core;
		}
		else if (2 <= num[i] && num[i] <= 5){
			boss[i] = boss2;
		}
		else if (6 <= num[i] && num[i] <= 7){
			boss[i] = boss1;
		}
		else if (num[i] == 8){
			boss[i] = enemy;
		}
	}
}

void Boss::start(int second){
	if (!exist && born == second){
		exist = true;
		saw = true;
	}
}

bool Boss::Exist(){
	return exist;
}

int Boss::Block(){
	return block;
}

void Boss::Move(){
	if (y < 5){
		y += 0.5;
	}
	else{
		if (right){
			x += 2;
			if (x + boss1.width * 4 + 5 > widthMax) right = false;
		}
		else {
			x -= 2;
			if (x < 10) right = true;
		}
	}
}

bool Boss::End(){
	return (fade && Fflame >= 250);
}

void Boss::Fade(){
	Fflame -= 5;
	if (fade){
		for (int i = 0; i < block; i++){
			switch (num[i]){
			case 1:
				boss[i].draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 2:
				boss[i].draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 3:
				boss[i].rotate(Radians(90.0)).draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 4:
				boss[i].rotate(Radians(180.0)).draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 5:
				boss[i].rotate(Radians(270.0)).draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 6:
				boss[i].draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 7:
				boss[i].rotate(Radians(90.0)).draw(X(i), Y(i), Alpha(Fflame));
				break;
			case 8:
				boss[i].draw(X(i), Y(i), Alpha(Fflame));
				break;
			}
		}
	}
	if (Fflame == 0){
		saw = false;
		clear = true;
	}
}

bool Boss::Clear(){
	return clear;
}

void Boss::Draw(){
	if (exist) Move();
	if (saw) {
		if (!fade){
			for (int i = 0; i < block; i++){

				if (bitFlag[i]){
					bitFlag[i] = false;
					num[i] = 0;
				}

				switch (num[i]){
				case 1:
					boss[i].draw(X(i), Y(i));
					break;
				case 2:
					boss[i].draw(X(i), Y(i));
					break;
				case 3:
					boss[i].rotate(Radians(90.0)).draw(X(i), Y(i));
					break;
				case 4:
					boss[i].rotate(Radians(180.0)).draw(X(i), Y(i));
					break;
				case 5:
					boss[i].rotate(Radians(270.0)).draw(X(i), Y(i));
					break;
				case 6:
					boss[i].draw(X(i), Y(i));
					break;
				case 7:
					boss[i].rotate(Radians(90.0)).draw(X(i), Y(i));
					break;
				case 8:
					boss[i].draw(X(i), Y(i));
					break;
				}
			}
		}
		else{
			Fade();
		}
	}
}