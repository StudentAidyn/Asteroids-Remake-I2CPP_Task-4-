#pragma once
#include <raylib.h>
#include <Vector>
#include <iostream>

#include "Bullet.h"
#include "Controller.h"
#include "Player.h"
#include "Asteroid.h"
#include "GameObject.h"

class GameRunner
{
public:
	GameRunner();
	~GameRunner();

	Player player;
	Asteroid asteroid;
	Controller control;

	Helper helper;

	float DeltaTime;

	//functions
	void GameLoad();
	void Reset();
	void Update();
	void Draw();

	
	void ContUpdate();
	void SpriteUpdate();
	
	void AddBullet();

	//base variables
	const int DefAsteroidNum = 5;

	//variables
	float DeltaTimer;
	int arrPos;
	int points;
	int rounds;

	std::vector <Bullet> bullet;
	Asteroid asteroids[];
	//two different asteroid types, one is a regular call to class, 
	//another is the array, the call to class is like a temporary value
};

