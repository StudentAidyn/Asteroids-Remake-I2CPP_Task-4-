#pragma once
#include "GameObject.h"
class Asteroid : public GameObject
{
	Asteroid();
	~Asteroid();

	const int DefAsteroid = 5;

	float xRandSpd;
	float yRandSpd;

	float xRandPos;
	float yRandPos;

	void SimpleSet(float x, float y, float xs, float ys, int h) {
		m20 = x;
		m21 = y;
		xSpeed = xs;
		ySpeed = ys;
		Health = h;

	};
};

