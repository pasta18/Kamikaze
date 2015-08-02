#include"Game.h"

Game::Game(){	
	normalEne = Texture::Texture(L"Data/Texture/Enemy.png");
	core = Texture::Texture(L"Data/Texture/core.png");
	menu = Texture::Texture(L"Data/Texture/menu.png");
	title = Sound::Sound(L"Data/Audio/title.mp3");
	battle = Sound::Sound(L"Data/Audio/battle.mp3");
	exp2 = Sound::Sound(L"Data/Audio/exp2.mp3");
	button = Sound::Sound(L"Data/Audio/button.mp3");
	cancel = Sound::Sound(L"Data/Audio/sys.mp3");
	title.setLoop(true);
	battle.setLoop(true);
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
	backGround = new BackGround;
	stage = 1;
	select = 0;
	num = 0;
	add = true;	
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
	delete backGround;
}

void Game::Play(){
	if (!battle.isPlaying) battle.play();
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
			// GameOver‚Ö„ˆÚ

		}
	}
	if (add) AddEnemy();
	Time();
	backGround->Draw();
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
	if (Input::KeyA.clicked) status = Pause;
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
					bool b_flag = enemy[i]->Fire(bul[j], player);
					if(!b_flag) break;
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
							exp2.playMulti();
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
							exp2.playMulti(0.1);
						}
					}
				}
			}
		}
	}
	if (boss->Exist() && boss->Crash(player->CX(), player->CY(), player)){
		player->Crash(player->CX(), player->CY(), 10);
		end = player->End();
		for (int j = 0; j < 50; j++){
			if (!exp[j]->Exist()){
				exp[j]->Set(player->X(), player->Y());
				exp2.playMulti();
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
							exp2.playMulti();
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
						exp2.playMulti();
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
	for (int i = 0; i < boss->Block(); i++){
		if (boss->bitCrash(i)){
			for (int j = 0; j < 50; j++){
				if (!exp[j]->Exist()){
					exp[j]->Set(boss->X(i), boss->Y(i));
					break;
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
						exp2.playMulti();
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
	case Pause:
		pause();
		break;
	case Result:
		End();
		break;
	}
}

void Game::pause(){
	font(L"PAUSE").draw(280, Window::Height() / 3);
	font(L"Resume Press A Key").draw(195, Window::Height() / 2);
	if (Input::KeyA.clicked) status = Playing;
}

void Game::Title(){
	font(L"_•—-Kamikaze-").draw(210, Window::Height() / 3);
	font(L"START").draw(285, 250);
	font(L"END").draw(300, 300);
	font(L"Ver0.1").draw(500, 420);

	if (!title.isPlaying) title.play();

	int place;

	if (select == 0) place = 250;
	else place = 300;
			
	font(L"¨").draw(250, place);

	if (Input::KeyUp.clicked){
		select++;
		select %= 2;
	}

	if (Input::KeyDown.clicked){
		select++;
		select %= 2;
	}

	if (Input::KeySpace.clicked){
		button.play();
		if (select == 0){
			stage = 1;
			boss->Set(createBoss, stage);
			flame = 0;
			player->Set();
			second = 0;
			endFlame = 0;
			num = 0;
			win = false;
			add = true;
			end = false;
			status = Playing;
			title.stop();
			for (int i = 0; i < 50; i++){
				if (i < 20) enemy[i]->Reset();
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
	if (battle.isPlaying) battle.stop();
	if (win){
		if (stageMax <= stage){
			font(L"GAME CLEAR").draw(230, Window::Height() / 3);
		}
		else{
			font(L"STAGE CLEAR").draw(225, Window::Height() / 3);
		}
	}
	else{
		font(L"GAME OVER").draw(235, Window::Height() / 3);
	}
	font(L"PRESS Space Key").draw(210, Window::Height() / 2);

	if (Input::KeySpace.clicked) {
		button.play();
		if (win && stageMax > stage){
			stage++;
			boss->Set(createBoss, stage);
			flame = 0;
			player->Reset();
			second = 0;
			endFlame = 0;
			num = 0;
			win = false;
			add = true;
			end = false;
			status = Playing;
			for (int i = 0; i < 50; i++){
				if (i < 20) enemy[i]->Reset();
				bul[i]->Reset();
				exp[i]->Reset();
			}
		}
		else status = Start;
	}
}