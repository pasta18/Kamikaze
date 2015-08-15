#include"Game.h"

Game::Game(){	
	normalEne = Texture(L"Data/Texture/Enemy.png");
	core = Texture(L"Data/Texture/core.png");
	menu = Texture(L"Data/Texture/kamikaze_UI.png");
	title = Sound(L"Data/Audio/title.mp3");
	battle = Sound(L"Data/Audio/battle.mp3");
	exp2 = Sound(L"Data/Audio/exp2.mp3");
	button = Sound(L"Data/Audio/button.mp3");
	cancel = Sound(L"Data/Audio/sys.mp3");
	TitleBack = Image(L"Data/Texture/title_background.png");
	StartButton = Image(L"Data/Texture/title_start.png");
	EndButton = Image(L"Data/Texture/title_end.png");
	TitleLogo = Image(L"Data/Texture/title_logo.png");
	t_back = Texture(TitleBack);
	t_start = Texture(StartButton);
	t_end = Texture(EndButton);
	t_logo = Texture(TitleLogo);
	t_start_on = Texture(StartButton.brighten(80));
	t_end_on = Texture(EndButton.brighten(80));
	AllTitle = Image(L"Data/Texture/kamikaze_title.png");
	/*
	for (int i = 0; i < 70; i++){
		titleTexture[i] = Texture(AllTitle.medianBlur(i));
	}
	*/
	Stock[0] = Texture(L"Data/Texture/zanki_0.png");
	Stock[1] = Texture(L"Data/Texture/zanki_1.png");
	Stock[2] = Texture(L"Data/Texture/zanki_2.png");
	Stock[3] = Texture(L"Data/Texture/zanki_3.png");
	Stock[4] = Texture(L"Data/Texture/zanki_4.png");
	On = Texture(L"Data/Texture/ka.png");
	Off = Texture(L"Data/Texture/huka.png");
	black = Rect(0, 0, Window::Width(), Window::Height());
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
	blackFlame = 255;
	win = false;
	end = false;
	GameStart = false;
	tmpStock = 4;
	s_flame = 255;
	b_flame = 255;
	s_on = false;
	b_on = false;
	logo_flame = 0;
	up = false;
	load_flame = 0;
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

	if (boss->Win()) return;

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
	menu.draw(Window::Width() - menu.width, 0);

	if (tmpStock == player->Stock()){
		Stock[player->Stock()].draw(605, 17, Alpha(255 - logo_flame));
	}
	else{
		if (s_on){

			Stock[player->Stock()].draw(605, 17, Alpha(s_flame));
			s_flame += (int)(255 / 30);
			if (s_flame > 255){
				s_flame = 255;
				s_on = false;
				tmpStock = player->Stock();
			}
		}
		else{
			Stock[player->Stock() +1].draw(605, 17, Alpha(s_flame));
			s_flame -= (int)(255 / 30);
			if (s_flame < 0){
				s_flame = 0;
				s_on = true;
			}
		}
	}

	if (player->BombStock()) {
		if (b_on){
			Off.draw(609, 150, Alpha(b_flame));

			b_flame -= (int)(255 / 30);

			if (b_flame < 0){
				b_flame = 0;
				b_on = false;
			}
		}
		else{
			if(b_flame != 255) On.draw(609, 152, Alpha(b_flame));
			else On.draw(609, 152, Alpha(255 - logo_flame));

			if (b_flame < 255){
				b_flame += (int)(255 / 30);
			}

			if (b_flame > 255){
				b_flame = 255;
			}
		}
	}
	else{
		if (b_on){
			if(b_flame != 255) Off.draw(609, 150, Alpha(b_flame));
			else Off.draw(609, 150, Alpha(255 - logo_flame));

			if (b_flame < 255){
				b_flame += (int)(255 / 30);
			}

			if (b_flame > 255){
				b_flame = 255;
			}
		}
		else{
			On.draw(609, 152, Alpha(b_flame));
			
			b_flame -= (int)(255 / 30);
			
			if (b_flame < 0){
				b_flame = 0;
				b_on = true;
			}
		}
		
		if (up) logo_flame--;
		else logo_flame++;

		if (logo_flame >= 50) up = true;
		if (logo_flame <= 0) up = false;
	}

}


void Game::Draw(){
	switch (status)
	{
	case Loading:
		Load();
		break;
	case Start:
		Title();
		break;
	case Playing:
		Play();
		if (blackFlame > 0) {
			black.draw(Color(0, 0, 0, blackFlame));
			blackFlame -= 2;
		}
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

void Game::Load(){
	if (black.w != Window::Width()) black = Rect(0, 0, Window::Width(), Window::Height());
	font(L"NOW LOADING").draw(450, 420, Palette::Red);
	Line(0, 460, load_flame * Window::Width() / 70, 460).draw(10, Palette::Red);

	if (load_flame < 70){
		titleTexture[load_flame] = Texture(AllTitle.medianBlur(load_flame));
		load_flame++;
	}
	else{
		status = Start;
	}
}

void Game::Title(){
	black.draw(Palette::Black);
	if (!GameStart){
		/*
		font(L"_•—-Kamikaze-").draw(210, Window::Height() / 3);
		font(L"START").draw(285, 250);
		font(L"END").draw(300, 300);
		font(L"Ver0.1").draw(500, 420);
		*/
		t_back.draw(26, 0);
		t_logo.draw(26, 0, Alpha(255 - logo_flame));

		if (select == 0){
			t_start_on.draw(408, 0);
			t_end.draw(534, 0, Alpha(255 - logo_flame));
		}
		else{
			t_start.draw(408, 0, Alpha(255 - logo_flame));
			t_end_on.draw(534, 0);
		}

		if (up) logo_flame--;
		else logo_flame++;

		if (logo_flame >= 50) up = true;
		if (logo_flame <= 0) up = false;

		if (!title.isPlaying) title.play();

		if (Input::KeyRight.clicked){
			select++;
			select %= 2;
		}

		if (Input::KeyLeft.clicked){
			select++;
			select %= 2;
		}

		if (Input::KeySpace.clicked){
			button.playMulti();

			GameStart = true;
			
		}
	}
	else{
		if(flame < 70) titleTexture[flame].draw(26, 0);
		
		if (flame == 120){
			if (select == 0){
				blackFlame = 255;
				GameStart = false;
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
				tmpStock = player->Stock();
				s_flame = 255;
				b_flame = 255;
				s_on = false;
				b_on = false;
			}
			else{
				System::Exit();
			}
		}
		else{
			flame++;
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
		button.playMulti();
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
		else {
			status = Start;
			flame = 0;
		}
	}
}