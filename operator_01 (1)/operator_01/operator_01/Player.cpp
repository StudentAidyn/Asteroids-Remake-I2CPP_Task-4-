#include "Player.h"

Player::Player() {
	boost = false;
	turbo = false;
}

Player::~Player() {

}

void Player::SpeedCap(float ixs, float iys, float& oxs, float& oys) {

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

void Player::SpriteUpdate() {

	//Rotation
	for (int i = 0; i < 7; i++) {
		sx[i] = mx[i] * cos(angle()) - my[i] * sin(angle());
		sy[i] = mx[i] * sin(angle()) + my[i] * cos(angle());
	}

	//Tranform
	for (int i = 0; i < 7; i++) {
		sx[i] = sx[i] + M3.m20;
		sy[i] = sy[i] + M3.m21;
	}
}

void Player::Controller() {

	//Rotational Inputs-------------------------

	//Anti-Clockwise
	if (IsKeyDown(KEY_A)) {
		//Positive GetFrameTime
		DeltaTimer = GetFrameTime() * rotSpeed;
		Rotate(DeltaTimer, M3);

	}

	//Clockwise
	if (IsKeyDown(KEY_D)) {
		//Negative GetFrameTime
		DeltaTimer = -GetFrameTime() * rotSpeed;
		Rotate(DeltaTimer, M3);

	}

	//booster inputs----------------------------------------------

	if (IsKeyDown(KEY_W)) {
		//thrust
		if (ySpeed < MAX_SPEED && xSpeed < MAX_SPEED) {
			xSpeed += sin(angle()) * thrSpeed * GetFrameTime();
			ySpeed += -cos(angle()) * thrSpeed * GetFrameTime();
		}

		boost = true;
	}
	else if (IsKeyUp(KEY_W)) { boost = false; }

	if (IsKeyDown(KEY_S)) {
		//thrust
		if (ySpeed < MAX_SPEED && xSpeed < MAX_SPEED) {
			xSpeed += sin(angle()) * thrSpeed * 4 * GetFrameTime();
			ySpeed += -cos(angle()) * thrSpeed * 4 * GetFrameTime();
		}

		turbo = true;
	}
	else if (IsKeyUp(KEY_S)) { turbo = false; }


	//function to limit the sped the player can move
	SpeedCap(xSpeed, ySpeed, xSpeed, ySpeed);


	//shooting
	if (IsKeyPressed(KEY_SPACE)) {
		AddBullet();
	}


	//UPDATER
	M3.m20 += xSpeed * GetFrameTime();
	M3.m21 += ySpeed * GetFrameTime();

	WrapCoordinates(M3.m20, M3.m21, M3.m20, M3.m21);

}

void Player::Draw() {
	BeginDrawing();

	if (turbo == true) {
		DrawLine(sx[3], sy[3], sx[5], sy[5], ORANGE);
		DrawLine(sx[4], sy[4], sx[5], sy[5], ORANGE);

		DrawLine(sx[3], sy[3], sx[6], sy[6], BLUE);
		DrawLine(sx[4], sy[4], sx[6], sy[6], BLUE);
	}

	if (boost == true) {
		DrawLine(sx[3], sy[3], sx[5], sy[5], RED);
		DrawLine(sx[4], sy[4], sx[5], sy[5], RED);
	}


	DrawLine(sx[0], sy[0], sx[1], sy[1], PURPLE);
	DrawLine(sx[0], sy[0], sx[2], sy[2], PURPLE);
	DrawLine(sx[3], sy[3], sx[4], sy[4], PURPLE);
	EndDrawing();
}

void Player::AddBullet() {
	bullet.push_back({ //x, y, rotx, roty
	M3.m20, M3.m21, M3.m10, M3.m11
	bulletSpeed * sinf(angle()),
	-bulletSpeed * cosf(angle()),
		});
}