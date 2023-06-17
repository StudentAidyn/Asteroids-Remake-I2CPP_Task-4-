#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	Player();
	~Player();

	const float MAX_SPEED = 200.0f;
	bool turbo;
	bool boost;

	float bulletSpeed = 80;

	float thrSpeed;


};

