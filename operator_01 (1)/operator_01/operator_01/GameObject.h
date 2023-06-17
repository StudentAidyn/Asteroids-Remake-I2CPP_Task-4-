#pragma once
#include <raylib.h>
#include <math.h>

class GameObject
{
	//matrix
	GameObject();
	~GameObject();
public:
	float m00, m10, m20;
	float m01, m11, m21;
	float m02, m12, m22;
	float xSpeed;
	float ySpeed;
	float thrSpeed;
	int Health;

	bool Alive;



	float angle() {
		float result;
		result = atan2(m10, m11);
		return result;
	}

};

