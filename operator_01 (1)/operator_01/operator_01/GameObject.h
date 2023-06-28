#pragma once
#include <raylib.h>
#include <math.h>
#include "Helper.h"

class GameObject
{
public:	
	GameObject();
	~GameObject();

	Helper::Matrix3 M3;
	float xSpeed;
	float ySpeed;
	float thrSpeed;
	int Health;

	bool Alive;

	void Set(Helper::Matrix3 Matrix);
	void Rotate(float DeltaTime, Helper::Matrix3 Matrix);
	void WrapCoordinates(float ix, float iy, float& ox, float& oy);
	bool Collision(float cx, float cy, float radius, float x, float y);
	virtual void SpriteUpdate();
	virtual void Draw();

	float angle() {
		float result;
		result = atan2(M3.m10, M3.m11);
		return result;
	}

};

