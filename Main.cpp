#include"Main.h"

void Main(){
	Game *game = new Game();

	while (System::Update()){
		game->Draw();
	}

	delete game;
}