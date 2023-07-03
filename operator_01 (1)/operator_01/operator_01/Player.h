#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:

	Player();
	~Player();

	//Not_Inherited------------------------------
	
	//const update
	void Controller(float DeltaTime);
	void Update();
	void SpriteUpdate();

	//functions
	void SpeedCap(float ixs, float iys, float& oxs, float& oys);
	void Reset();

	//-------------------------------------------


	//Changed_Inherited--------------------------
	void Draw();
	//-------------------------------------------

	//Variables
	const float MAX_SPEED = 200.0f;
	float thrSpeed;
	float rotSpeed = 5.0f;


	//Visual Variables
	bool boost;
	bool turbo;
	
private:

	//Player Ship Model Coords---------------------------------------
	//DO NOT TOUCH 
	float mx[7] = { 0.0f, 5.0f, -5.0f, 4.0f, -4.0f, 0.0f, 0.0f };
	float my[7] = { -5.0f, 5.0f, 5.0f, 3.0f, 3.0f,  7.0f, 15.0f };
	float sx[7], sy[7];
	//DO NOT TOUCH
	//---------------------------------------------------------------

};



