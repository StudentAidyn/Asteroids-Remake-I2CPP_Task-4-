#include <iostream>
#include <raylib.h>
#include "GameRunner.h"
using namespace std;

int main() {
	GameRunner game;
	InitWindow(600, 400, "Asteroids_GAME--Aidyn_RADFORD");
	game.GameLoad(); //IMPORTANT -> call Window Before GameLoad or won't spawn player properly

	while (!WindowShouldClose()) {
		game.Tick(); //Tick is Update but called tick as it runs through the updates
		game.Draw(); //calls draw as often as each tick
	}

	return 0;
}