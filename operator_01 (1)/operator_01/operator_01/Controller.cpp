#include "Controller.h"
//
//Controller::Controller() {
//	
//}
//
//Controller::~Controller() {
//
//}
//
//void Controller::Input(float DeltaTime) {
//
//	//Rotational Inputs-------------------------
//
//	//Anti-Clockwise
//	if (IsKeyDown(KEY_A)) {
//		//Positive GetFrameTime
//		player.Rotate(DeltaTime * player.rotSpeed, player.M3);
//	}
//
//	//Clockwise
//	if (IsKeyDown(KEY_D)) {
//		//Negative GetFrameTime
//		player.Rotate(-DeltaTime * player.rotSpeed, player.M3);
//	}
//
//	//booster inputs----------------------------------------------
//
//	if (IsKeyDown(KEY_W)) {
//		//thrust
//		if (player.ySpeed < player.MAX_SPEED && player.xSpeed < player.MAX_SPEED) {
//			player.xSpeed += sin(player.angle()) * player.thrSpeed * GetFrameTime();
//			player.ySpeed += -cos(player.angle()) * player.thrSpeed * GetFrameTime();
//		}
//
//		player.boost = true;
//	}
//	else if (IsKeyUp(KEY_W)) { player.boost = false; }
//
//	if (IsKeyDown(KEY_S)) {
//		//thrust
//		if (player.ySpeed < player.MAX_SPEED && player.xSpeed < player.MAX_SPEED) {
//			player.xSpeed += sin(player.angle()) * player.thrSpeed * 4 * GetFrameTime();
//			player.ySpeed += -cos(player.angle()) * player.thrSpeed * 4 * GetFrameTime();
//		}
//
//		player.turbo = true;
//	}
//	else if (IsKeyUp(KEY_S)) { player.turbo = false; }
//
//
//	//function to limit the sped the player can move
//	player.SpeedCap(player.xSpeed, player.ySpeed, player.xSpeed, player.ySpeed);
//
//
//	//shooting
//	if (IsKeyPressed(KEY_SPACE)) {
//		AddBullet();
//	}
//
//
//	//UPDATER
//	player.M3.m20 += player.xSpeed * GetFrameTime();
//	player.M3.m21 += player.ySpeed * GetFrameTime();
//
//	player.WrapCoordinates(player.M3.m20, player.M3.m21, player.M3.m20, player.M3.m21);
//
//
//}
//
//void Controller::Update() {
//
//	player.Update();
//
//
//}
//
//void Controller::Draw() {
//
//	player.Draw()
//
//}



