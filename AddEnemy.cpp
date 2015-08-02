#include"Game.h"

void Game::AddEnemy(){
	if (add){
		switch (stage){
		case 1:
			for (int i = 0; i < 20; i++){
				if (enemy[i]->Accept()){
					switch (num){// (x, y, speed, rad, texture, second, core?, patarn)
					case 0:
						enemy[i]->Set(widthMax / 3 * 2, -15, 1, Radians(30), normalEne, 4, false, 0);
						break;
					case 1:
						enemy[i]->Set(widthMax / 3, -15, 1, -Radians(30), normalEne, 4, false, 0);
						break;
					case 2:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 8, false, 0);
						break;
					case 3:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 10, false, 0);
						break;
					case 4:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 12, false, 0);
						break;
					case 5:
						enemy[i]->Set(widthMax + 20, 50, 0.5, Radians(90), core, 10, true, 0);
						break;
					case 6:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 14, false, 0);
						break;
					case 7:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 16, false, 0);
						break;
					case 8:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(90), normalEne, 18, false, 0);
						break;
					case 9:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 10, false, 0);
						break;
					case 10:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 13, false, 0);
						break;
					case 11:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 15, false, 0);
						break;
					case 12:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 18, false, 0);
						break;
					case 13:
						enemy[i]->Set(widthMax, -15, 1, Radians(70), normalEne, 25, false, 0);
						break;
					case 14:
						enemy[i]->Set(widthMax, -15, 1, Radians(70), normalEne, 26, false, 0);
						break;
					case 15:
						enemy[i]->Set(widthMax, -15, 1, Radians(70), normalEne, 27, false, 0);
						break;
					case 16:
						enemy[i]->Set(widthMax, -15, 1, Radians(70), normalEne, 28, false, 0);
						break;
					case 17:
						enemy[i]->Set(0, -15, 1, -Radians(70), normalEne, 30, false, 0);
						break;
					case 18:
						enemy[i]->Set(0, -15, 1, -Radians(70), normalEne, 31, false, 0);
						break;
					case 19:
						enemy[i]->Set(0, -15, 1, -Radians(70), normalEne, 32, false, 0);
						break;
					case 20:
						enemy[i]->Set(0, -15, 1, -Radians(70), normalEne, 33, false, 0);
						break;
					case 21:
						enemy[i]->Set(widthMax + 20, 0, 0.5, Radians(90), core, 30, true, 0);
						break;
					default:
						add = false;
						break;
						//enemy[1]->Set(Window::Width() / 3, -15, 2, 0, core, 0, true, 0);
					}
					num++;
				}
				if (!add) break;
			}
			break;
		case 2:
			for (int i = 0; i < 20; i++){
				if (enemy[i]->Accept()){
					switch (num){// (x, y, speed, rad, texture, second, core?, patarn)
					case 0:
						enemy[i]->Set(widthMax + 20, 200, 2, Radians(110), normalEne, 4, false, 0);
						break;
					case 1:
						enemy[i]->Set(-20, 200, 2, Radians(-110), normalEne, 4, false, 0);
						break;
					case 2:
						enemy[i]->Set(widthMax - 10, -15, 1, 0, normalEne, 8, false, 2);
						break;
					case 3:
						enemy[i]->Set(10, -15, 1, 0, normalEne, 8, false, 2);
						break;
					case 4:
						enemy[i]->Set(widthMax - 10, -15, 1, 0, normalEne, 13, false, 2);
						break;
					case 5:
						enemy[i]->Set(10, -15, 1, 0, normalEne, 13, false, 2);
						break;
					case 6:
						enemy[i]->Set(widthMax - 10, -15, 1, 0, normalEne, 18, false, 2);
						break;
					case 7:
						enemy[i]->Set(10, -15, 1, 0, normalEne, 18, false, 2);
						break;
					case 8:
						enemy[i]->Set(widthMax + 20, 50, 0.5, Radians(90), core, 12, true, 0);
						break;
					case 9:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 24, false, 1);
						break;
					case 10:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 24, false, 3);
						break;
					case 11:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 26, false, 1);
						break;
					case 12:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 26, false, 3);
						break;
					case 13:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 28, false, 1);
						break;
					case 14:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 28, false, 3);
						break;
					case 15:
						enemy[i]->Set(widthMax + 20, 0, 2, Radians(90), normalEne, 30, false, 1);
						break;
					case 16:
						enemy[i]->Set(-20, 100, 2, -Radians(90), normalEne, 30, false, 3);
						break;
					case 17:
						enemy[i]->Set(-20, 50, 1, Radians(-90), core, 25, true, 0);
						break;
					default:
						add = false;
						break;
						//enemy[1]->Set(Window::Width() / 3, -15, 2, 0, core, 0, true, 0);
					}
					num++;
				}
				if (!add) break;
			}
			break;
		}
	}
}