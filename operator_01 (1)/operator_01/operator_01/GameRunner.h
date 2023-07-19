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


	void GameLoad();	//	GameLoad: is the default game state setter.*/
	void Tick();		//	Tick: updates each game object like a server tick.
	void Controller();	//	Controller: checks for user input. 
	void Draw();		//	Draw: wipes the background and calls apon each game objects' draw function.
	void RESET();		/*	Reset: makes all asteroids null, also sets score to nulland then calls...
							GameLoad to 'default' the game state*/

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

	/*Variable speeds and positions used when assigning the random directions the
	asteroids will go at the start of each round*/

	//Bullet List with Related Function
	std::list <Bullet> bullet;
	void AddBullet();	
	/*AddBullet: adds a bullet to the bullet list 
	by using the angle values from the player*/


	//How the Player knows they are advancing
	int points = 0;
	int rounds = 0;
	//these variables increase whenever an asteroid is destroyed or a new round is started

	//Helper Functions
	void WrapCoordinates(float ix, float iy, float& ox, float& oy);		
	/*WrapCoordinates: takes objects current xand y values and then changes them to 
	opposite side of screen*/
	bool Collision(float cx, float cy, float radius, float x, float y);
	/*Collision: is a boolean function which takes 2 game object x and y values and 
	compares them to each other to see if they are colliding in each others space*/
	void ProjectileCheck();
	/*ProjectileCheck: updates all game objects that are projectiles, this includes Asteroids and bullets.
	It checks for bullet collision with asteroids and splits asteroids if collisions occur.*/
	
};

