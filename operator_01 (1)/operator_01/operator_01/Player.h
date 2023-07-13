#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player();
	~Player();

	//Matrix -> M3 (inherited)

	//Set Variables
	const float MAX_SPEED = 200.0f;

	float thrSpeed = 60.0f;
	float rotSpeed = 5.0f;

	//Indicators
	bool turbo;
	bool boost;

	//Overridden Functions
	void Update();
	void Draw();

	//Additional Functions
	void PlStateStart();
	void SpriteUpdate();

	void SpeedCap();
	void Rotate(float DeltaTime);
	void Translate(float SpeedM, float DeltaTime);

	//Player Ship Sprite vert pos
	float mx[7] = { 0.0f, 5.0f, -5.0f, 4.0f, -4.0f, 0.0f, 0.0f };
	float my[7] = { -5.0f, 5.0f, 5.0f, 3.0f, 3.0f,  7.0f, 15.0f };
	float sx[7], sy[7];
};

