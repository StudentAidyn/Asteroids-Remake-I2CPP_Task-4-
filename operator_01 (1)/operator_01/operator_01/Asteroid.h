#pragma once
#include "GameObject.h"
class Asteroid : public GameObject
{
public:
	Asteroid();
	~Asteroid();

	void Update();
	void Draw();

	const int STRT_HEALTH = 40;
	const int DefAsteroid = 5;

	float xRandSpd;
	float yRandSpd;

	float xRandPos;
	float yRandPos;


	void SimpleSet(float x, float y, float xs, float ys, int h) {
		M3.m20 = x;
		M3.m21 = y;
		xSpeed = xs;
		ySpeed = ys;
		Health = h;

	};
};

