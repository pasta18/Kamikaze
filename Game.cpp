#include"Game.h"

Game::Game(){
	title = Texture::Texture(L"Example/Windmill.png");
	normalEne = Texture::Texture(L"Data/Texture/Enemy.png");
	core = Texture::Texture(L"Data/Texture/core.png");
	menu = Texture::Texture(L"Data/Texture/menu.png");
	player = new Player();
	boss = new Boss();
	font = Font::Font(20);
	for (int i = 0; i < 20; i++){
		enemy[i] = new Enemy();
	}
	for (int i = 0; i < 50; i++){
		exp[i] = new Explosion();
		bul[i] = new Bullet();
	}
	stage = 1;
	select = 0;
	//enemy[0]->Set(Window::Width() / 2, 0, 1, 0, normalEne, 0, false, 0);
	//enemy[1]->Set(Window::Width() / 3, 0, 2, 0, core, 0, true, 0);
	//boss->Set(2, stage);
	flame = 0;
	second = 0;
	endFlame = 0;
	win = false;
	end = false;
}

Game::~Game(){
	delete player;
	for (int i = 0; i < 20; i++){
		delete enemy[i];
	}
	for (int i = 0; i < 50; i++){
		delete exp[i];
		delete bul[i];
	}
	delete boss;
}

void Game::Play(){
	if (boss->Clear()){
		status = Result;
		win = true;
	}
	if (player->Over()) status = Result;

	if (end){
		endFlame++;
		if (endFlame >= 120){
			endFlame = 0;
			end = false;
			// GameOverÇ÷êÑà⁄

		}
	}
	Time();
	for (int i = 0; i < 50; i++){
		if (bul[i]->Exist()) bul[i]->Draw();
	}
	for (int i = 0; i < 20; i++){
		enemy[i]->Draw(second);
	}
	if (boss->End() && !player->Bomb()){
		player->Crash(player->CX(), player->CY(), 10);
		end = player->End();
		for (int j = 0; j < 50; j++){
			if (!exp[j]->Exist()){
				exp[j]->Set(player->X(), player->Y());
				break;
			}
		}
	}
	if (!boss->Exist()) boss->start(second);
	if (!player->Clear() && boss->Win()){
		player->Win();
	}
	if (player->Clear()){
		for (int i = 0; i < 50; i++){
			if (!exp[i]->Exist()){
				boss->Death(exp[i]);
				break;
			}
		}
	}
	boss->Draw();
	player->Draw();
	Crash();
	Shoot();
	for (int i = 0; i < 50; i++){
		if (exp[i]->Exist()) exp[i]->Draw();
	}
	Menu();
}

void Game::Shoot(){
	if (boss->Exist()){
		bool flag = true;
		while (flag){
			for (int i = 0; i < 50; i++){
				if (!bul[i]->Exist()){
					flag = boss->Shoot(bul[i], stage, player);
					break;
				}
			}
		}
	}
	for (int i = 0; i < 20; i++){
		if (enemy[i]->Exist() && enemy[i]->Shoot()){
			for (int j = 0; j < 50; j++){
				if (!bul[j]->Exist()){
					enemy[i]->Fire(bul[j]);
					break;
				}
			}
		}
	}
}

void Game::Time(){
	flame++;
	if (flame >= 60){
		flame = 0;
		second++;
	}
}

void Game::Crash(){
	if (!player->Exist() || player->Spawn()) return;
	if (player->Bomb()){
		for (int i = 0; i < 20; i++){
			if (enemy[i]->Exist() && !enemy[i]->Core()){
				if (enemy[i]->Crash(player->CX(), player->CY())){
					for (int j = 0; j < 50; j++){
						if (!exp[j]->Exist()){
							enemy[i]->death(exp[j]);
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < 50; i++){
			if (bul[i]->Exist()){
				if (bul[i]->Crash(player->CX(), player->CY())){
					for (int j = 0; j < 50; j++){
						if (!exp[j]->Exist()){
							exp[j]->Set(bul[i]->X(), bul[i]->Y());
						}
					}
				}
			}
		}
	}
	if (boss->Exist() && boss->Crash(player->CX(), player->CY())){
		player->Crash(player->CX(), player->CY(), 10);
		end = player->End();
		for (int j = 0; j < 50; j++){
			if (!exp[j]->Exist()){
				exp[j]->Set(player->X(), player->Y());
				break;
			}
		}
	}

	for (int i = 0; i < 20; i++){
		if (enemy[i]->Exist() && !enemy[i]->Core()){
			if (!player->Bomb()){
				if (player->Crash(enemy[i]->CX(), enemy[i]->CY(), enemy[i]->Radius())){
					end = player->End();
					for (int j = 0; j < 50; j++){
						if (!exp[j]->Exist()){
							exp[j]->Set(player->X(), player->Y());
							break;
						}
					}
				}
			}
		}
		else if (enemy[i]->Exist()){
			if (enemy[i]->Crash(player->CX(), player->CY())){
				for (int j = 0; j < 50; j++){
					if (!exp[j]->Exist()){
						enemy[i]->death(exp[j]);
						for (int k = 0; k < 20; k++){
							if (enemy[k]->Exist()){
								for (int l = 0; l < 50; l++){
									if (!exp[l]->Exist()){
										enemy[k]->death(exp[l]);
										break;
									}
								}
							}
						}
						break;
					}
				}
			}
		}
	}
	if (player->Bomb()) return;
	for (int i = 0; i < 50; i++){
		if (bul[i]->Exist()){
			if (player->Crash(bul[i]->CX(), bul[i]->CY(), bul[i]->Radius())){
				for (int j = 0; j < 50; j++){
					if (!exp[j]->Exist()){
						exp[j]->Set(player->X(), player->Y());
						break;
					}
				}
			}
		}
	}
}

void Game::Menu(){
	// menu.draw(Window::Width() - menu.width, 0);
	Rect(widthMax + 32, 0, Window::Width() - widthMax + 32, Window::Height()).draw(Palette::Black);
	Line(widthMax + 32, 0, widthMax + 32, Window::Height()).draw();

	font(L"Stock:",player->Stock()).draw(widthMax + 40, 0);

	if (player->BombStock()){
		font(L"<Barrier>").draw(widthMax + 40, 60);
	}
}


void Game::Draw(){
	switch (status)
	{
	case Start:
		Title();
		break;
	case Playing:
		Play();
		break;
	case Result:
		End();
		break;
	}
}

void Game::Title(){
	font(L"ê_ïó-Kamikaze-").draw(210, Window::Height() / 3);
	font(L"START").draw(285, 250);
	font(L"END").draw(300, 300);

	int place;

	if (select == 0) place = 250;
	else place = 300;
			
	font(L"Å®").draw(250, place);

	if (Input::KeyUp.clicked){
		select++;
		select %= 2;
	}

	if (Input::KeyDown.clicked){
		select++;
		select %= 2;
	}

	if (Input::KeySpace.clicked){
		if (select == 0){
			stage = 1;
			boss->Set(2, stage);
			flame = 0;
			player->Set();
			second = 0;
			endFlame = 0;
			end = false;
			status = Playing;
			for (int i = 0; i < 50; i++){
				bul[i]->Reset();
				exp[i]->Reset();
			}
		}
		else{
			System::Exit();
		}
	}
}

void Game::End(){
	if (win){
		font(L"GAME CLEAR").draw(230, Window::Height() / 3);
	}
	else{
		font(L"GAME OVER").draw(235, Window::Height() / 3);
	}
	font(L"PRESS Space Key").draw(210, Window::Height() / 2);

	if (Input::KeySpace.clicked) status = Start;
}