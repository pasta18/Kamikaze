#include"Boss.h"

Boss::Boss(){
	boss1 = Texture::Texture(L"Data/Texture/Boss1.png");
	boss2 = Texture::Texture(L"Data/Texture/Boss2.png");
	core = Texture::Texture(L"Data/Texture/Boss3.png");
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
	born = second;
	clear = false;
	x = widthMax - boss1.width * 5;
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
	}
	texSet();
}

bool Boss::Win(){
	return (!exist && saw);
}

bool Boss::Crash(double x, double y){
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
		else{
			if (abs(CX(i) - x) < boss1.width / 2 && abs(CY(i) - y) < boss1.height / 2){
				return true;
			}
		}
	}
	return false;
}

void Boss::Death(Explosion *exp){
	if (!exist && saw && bomb > 0 && flame == 0){
		if (bomb == 1){
			for (int i = 0; i < block; i++){
				if (num[i] == 1){
					exp->Set(X(i), Y(i));
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
				}
			}
		}
		else{
			Fade();
		}
	}
}