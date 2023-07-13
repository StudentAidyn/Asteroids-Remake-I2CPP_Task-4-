#pragma once
#include <list>
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

class GameRunner
{
public:
	GameRunner();
	~GameRunner();


	void GameLoad();
	void Tick();
	void Controller();
	void Draw();
	void RESET();

	//Player
	Player player;

	//Asteroid Array and Related Vars
	const int DefAsteroid = 5;
	
	Asteroid asteroids[20];
	
	int arrPos;
	
	float xRandSpd;
	float yRandSpd;

	float xRandPos;
	float yRandPos;


	//Bullet List with Related Func
	std::list <Bullet> bullet;
	void AddBullet();


	//Player knows they are advancing
	int points = 0;
	int rounds = 0;


	//Helper Functions
	void WrapCoordinates(float ix, float iy, float& ox, float& oy);
	bool Collision(float cx, float cy, float radius, float x, float y);
	void ProjectileCheck();
	
};

