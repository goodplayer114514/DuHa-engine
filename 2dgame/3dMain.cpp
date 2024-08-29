#include"DuHa3D.h"
#include<conio.h>
#include<iostream>
#define Ro_speed 0.1
int ab;
void Game::input() {
	if (_kbhit()) {
		ab = _getch();
	}
	switch (ab) {
	case 'w':
		MainCam.Cam_pos.z += Ro_speed;
		break;
	case 's':
		MainCam.Cam_pos.z -= Ro_speed;
		break;
	case 'a':
		MainCam.Cam_pos.x += Ro_speed;
		break;
	case 'd':
		MainCam.Cam_pos.x -= Ro_speed;
		break;
	case 'z':
		MainCam.Cam_ro.z += Ro_speed;
		break;
	case 'x':
		MainCam.Cam_ro.z -= Ro_speed;
		break;
	case 'c':
		MainCam.Cam_ro.y += Ro_speed;
		break;
	case 'v':
		MainCam.Cam_ro.y -= Ro_speed;
		break;
	}
	ab = 0;
}void Game::update() {

}
int main() {
	Game* MyGame=new Game(1,40,4.0/3.0,2,60);
	initgraph(600, 400);
	MyGame->MainCam.pixel_Ch(600, 400);
	MyGame->MainCam.Cam_pos.x = 0;
	MyGame->MainCam.Cam_pos.y = 0;
	MyGame->MainCam.Cam_pos.z = -3;
	GameObject *hi=new GameObject;
	//float cubeheight=1, cubewidth=1, cubelong=1;
	//std::cout << hi->Poslist[101].WorldNormalPos.z;
	Pos pos1(0, 0, 0);
	Pos pos2(1, 0, 0);
	Pos pos3(1, 0, 1);
	Pos pos4(0, 0, 1);
	Pos pos5(0, 1, 0);
	Pos pos6(1, 1, 0);
	Pos pos7(1, 1, 1);
	Pos pos8(0, 1, 1);
	hi->Mian.insert(std::pair<int, int>(0, 5));
	hi->Mian.insert(std::pair<int, int>(1, 6));
	hi->Mian.insert(std::pair<int, int>(2, 4));
	hi->Mian.insert(std::pair<int, int>(4, 6));
	hi->Mian.insert(std::pair<int, int>(0, 2));
	hi->Poslist.push_back(pos1);
	hi->Poslist.push_back(pos2);
	hi->Poslist.push_back(pos3);
	hi->Poslist.push_back(pos4);
	hi->Poslist.push_back(pos5);
	hi->Poslist.push_back(pos6);
	hi->Poslist.push_back(pos7);
	hi->Poslist.push_back(pos8);
	MIan(hi, 255, 0, 0);
	MyGame->objectlist.push_back(*hi);
	MyGame->Running(true);
	delete hi;
	delete MyGame;
	return 0;
}
