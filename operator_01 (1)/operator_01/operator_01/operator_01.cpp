#include <iostream>
#include <raylib.h>
#include "Game.h"
#include "Object.h"
#include "GameRunner.h"
using namespace std;

int main() {
	cout << "Hello World!";

	//Game game;
	//game.GameLoad();
	//InitWindow(600, 400, "TestWindow");

	//while (!WindowShouldClose()) {
	//	game.Update();
	//	game.Draw();
	//}
	//
	//game.End();

	//Object game;
	//InitWindow(600, 400, "Asteroids_GAME--Aidyn_RADFORD");
	//game.GameLoad();
	//

	//while (!WindowShouldClose()) {
	//	game.Update();
	//	game.Draw();
	//}

	//game.End();

	GameRunner game;
	InitWindow(600, 400, "Asteroids_GAME--Aidyn_RADFORD");
	game.GameLoad();


	while (!WindowShouldClose()) {
		game.Update();
		game.Draw();
	}

	return 0;
}