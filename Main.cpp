#include"Main.h"

void Main(){
	Game *game = new Game();
	Window::SetTitle(L"Kamikaze Ver0.1");

	while (System::Update()){
		game->Draw();
	}

	delete game;
}