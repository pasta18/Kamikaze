#include"Main.h"

void Main(){
	Game *game = new Game();
	Window::SetTitle(L"Kamikaze Ver0.3.1");
	Window::Resize(692, 480);

	while (System::Update()){
		game->Draw();
	}

	delete game;
}