#pragma once
#include "GameObject.h"

#include "Bullet.h"
#include <list>

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Controller();
	void AddBullet();

	std::list <Bullet> bullet;

	//Variables
	const float MAX_SPEED = 200.0f;
	float thrSpeed;
	float rotSpeed = 5.0f;

	void SpeedCap(float ixs, float iys, float& oxs, float& oys);

	//Player Ship Model Coords
	float mx[7] = { 0.0f, 5.0f, -5.0f, 4.0f, -4.0f, 0.0f, 0.0f };
	float my[7] = { -5.0f, 5.0f, 5.0f, 3.0f, 3.0f,  7.0f, 15.0f };
	float sx[7], sy[7];

	//Inheritence
	void SpriteUpdate();
	void Draw();

	//Visual Variables
	bool boost;
	bool turbo;
};



