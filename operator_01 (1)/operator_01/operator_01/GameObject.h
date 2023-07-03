#pragma once
#include <raylib.h>
#include <math.h>
#include "Helper.h"

class GameObject
{
public:	
	GameObject();
	~GameObject();

	//Helper helper;

	////helper::Matrix3 M3;

	Helper::Matrix3 M3;


	float xSpeed;
	float ySpeed;
	float thrSpeed;
	int Health;

	bool Alive;

	
	virtual void SpriteUpdate();
	virtual void Draw();

	

};

