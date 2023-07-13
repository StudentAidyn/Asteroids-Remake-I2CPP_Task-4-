#pragma once
#include <raylib.h>
#include <math.h>

class GameObject
{
public: //for other constructors/destructors to work, these need to be public
	GameObject();
	~GameObject();


	virtual struct Matrix3 { //matrix 3 in struct to separate from Main
		float m00, m10, m20;
		float m01, m11, m21;
		float m02, m12, m22;

		void Set();
	};
	
	Matrix3 M3;

	//Constant Variables -> used in all other inherited game objects
	float xSpeed;
	float ySpeed;
	float thrSpeed;
	int Health;

	bool Alive;

	//virtual functions, will be updated when inherited
	virtual void Update();
	virtual void Draw();
	
	//Constant Function
	virtual float angle();
};

