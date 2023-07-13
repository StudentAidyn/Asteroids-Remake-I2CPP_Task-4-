#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	Bullet(float _m20, float _m21, float _m10, float _m11); 
	//This is needed as a Simplified value setter.
	//This copies player position and angle to the bullet, 
	//letting it fire from the same position in the same direction.
	
	//Overridden Functions
	void Draw(); 
	void Update();

	//Variables
	float bulletSpeed = 80;
};

