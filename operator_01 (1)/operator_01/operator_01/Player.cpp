#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::PlStateStart() {
	xSpeed = 0; //reset or set speeds to NULL (0)
	ySpeed = 0;

	M3.Set(); //set M3 Matrix
	M3.m20 = GetScreenWidth() / 2.0f; //set to middle of screen
	M3.m21 = GetScreenHeight() / 2.0f;
	SpriteUpdate(); //update sprites position

	//reset all bools to reflect re/start
	Alive = true;

	boost = false;
	turbo = false;
}

void Player::Rotate(float DeltaTime) { //set this to work to rotate the ship, Temp is MATRIX3 THAT IS WHY NO WORK!!
	float c = (float)cosf(DeltaTime * rotSpeed);
	float s = (float)sinf(DeltaTime * rotSpeed + PI);

	Matrix3 temp; //make temporary gameobject
	temp.Set();


	temp.m00 = M3.m00 * c + M3.m10 * -s + M3.m20 * 0;	//apply the main gameobject results to the temporary ones
	temp.m01 = M3.m01 * c + M3.m11 * -s + M3.m21 * 0;	//if you don't do this and apply the results directly
	temp.m02 = M3.m02 * c + M3.m12 * -s + M3.m22 * 0;	//then the new results being assigned will use the updated
														//variables instead of the initial ones.
	temp.m10 = M3.m00 * s + M3.m10 * c + M3.m20 * 0;
	temp.m11 = M3.m01 * s + M3.m11 * c + M3.m21 * 0;
	temp.m12 = M3.m02 * s + M3.m12 * c + M3.m22 * 0;


	M3.m00 = temp.m00; M3.m10 = temp.m10; //make the player angles equal to the temporary gameobjects angles
	M3.m01 = temp.m01; M3.m11 = temp.m11;
}

void Player::Translate(float SpeedM, float DeltaTime) {
	if (ySpeed < MAX_SPEED && xSpeed < MAX_SPEED) {
		xSpeed += sin(angle()) * thrSpeed * SpeedM * DeltaTime;
		ySpeed += -cos(angle()) * thrSpeed * SpeedM * DeltaTime;
	}

	if (SpeedM > 1) {
		turbo = true;
	}
	else {
		boost = true;
	}

	//function to limit the sped the player can move
	SpeedCap();
}

void Player::SpeedCap() {
	if (xSpeed >= MAX_SPEED) {
		xSpeed = MAX_SPEED - 1;
	}
	else if (xSpeed <= -MAX_SPEED) {
		xSpeed = -MAX_SPEED + 1;
	}
	if (ySpeed >= MAX_SPEED) {
		ySpeed = MAX_SPEED - 1;
	}
	else if (ySpeed <= -MAX_SPEED) {
		ySpeed = -MAX_SPEED + 1;
	}
}

void Player::Update() {
	//M3 Movement
	M3.m20 += xSpeed * GetFrameTime();
	M3.m21 += ySpeed * GetFrameTime();

	SpriteUpdate(); //update sprite based on movements
}

void Player::SpriteUpdate() {
	//update Sprite
	
	//[Rotation]
	for (int i = 0; i < 7; i++) {
		sx[i] = mx[i] * cos(angle()) - my[i] * sin(angle());
		sy[i] = mx[i] * sin(angle()) + my[i] * cos(angle());
	}

	//[Tranform]
	for (int i = 0; i < 7; i++) {
		sx[i] = sx[i] + M3.m20;
		sy[i] = sy[i] + M3.m21;
	}
}

void Player::Draw() {
	//Draw M3 ship

	DrawLine(sx[0], sy[0], sx[1], sy[1], PURPLE);
	DrawLine(sx[0], sy[0], sx[2], sy[2], PURPLE);
	DrawLine(sx[3], sy[3], sx[4], sy[4], PURPLE);

	if (boost == true) {
		DrawLine(sx[3], sy[3], sx[5], sy[5], RED);
		DrawLine(sx[4], sy[4], sx[5], sy[5], RED);
	}

	if (turbo == true) {
		DrawLine(sx[3], sy[3], sx[5], sy[5], ORANGE);
		DrawLine(sx[4], sy[4], sx[5], sy[5], ORANGE);

		DrawLine(sx[3], sy[3], sx[6], sy[6], BLUE);
		DrawLine(sx[4], sy[4], sx[6], sy[6], BLUE);
	}

}