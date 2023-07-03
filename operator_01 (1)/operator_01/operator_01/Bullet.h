#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	Bullet(float x, float y, float rotX, float rotY);

	void Update();
	void Draw();

	float BulletSpeed = 80;
};

