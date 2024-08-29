/*
#include"game.h"
#include<iostream>
//对象
#define peo_width 40
#define peo_height 40
Game game;
pos Pos = { 0,0 };
athor peo(Pos, peo_width, peo_height);
void Game::update() {

}
void Game::input() {

}
void init() {
	loadimage(&peo.pic, L"res\\人物.png", peo_width, peo_height);
	game.list.push_back(peo);
}
void GameStart(bool a) {
	initgraph(600, 400);
	while (a) {
		//game.output();
		game.input();
		game.update();
		game.output();
	}
}
int main() {
	init();
	GameStart(true);
	return 0;
}
*/