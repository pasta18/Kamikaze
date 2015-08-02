#include"BackGround.h"

BackGround::BackGround(){
	Set();
}

BackGround::~BackGround(){

}

void BackGround::Set(){
	for (int i = 0; i < point; i++){
		dotx[i] = Random(0, Window::Width());
		doty[i] = Random(0, Window::Height());
		scale[i] = Random(1, 3);
		clear[i] = Random(1, 150);
		speed[i] = Random(5, 30);
	}
}

void BackGround::Reset(int number){
	dotx[number] = Random(0, Window::Width());
	doty[number] = -5;
	scale[number] = Random(1, 3);
	clear[number] = Random(1, 150);
	speed[number] = Random(5, 30);
}

void BackGround::Move(){
	for (int i = 0; i < point; i++){
		if (doty[i] > Window::Height() + 5) Reset(i);
		else doty[i] += speed[i];
	}
}

void BackGround::Draw(){
	Move();
	for (int i = 0; i < point; i++){
		Circle(dotx[i], doty[i], scale[i]).draw(Color(255, 255, 255, clear[i]));
	}
}