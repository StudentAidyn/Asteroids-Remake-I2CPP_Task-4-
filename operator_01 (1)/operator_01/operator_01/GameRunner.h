#pragma once
#include <raylib.h>
#include <list>
#include "Bullet.h"

class GameRunner
{
	//functions
	void GameLoad();
	void Reset();
	void Controller();
	void Update();
	void Draw();

	
	void ContUpdate();
	void SpriteUpdate();
	
	void AddBullet();

	//base variables
	int DefAsteroidNum = 5;

	//variables
	float DeltaTimer;
	int arrPos;
	int points;
	int rounds;

	std::list <Bullet> bullet;
};

