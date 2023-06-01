#include "Object.h"
#include <iostream>

Object::Object() {

}

void Object::GameLoad() {
	Set(player);
	player.m20 = GetScreenWidth() / 2.0f;
	player.m21 = GetScreenHeight() / 2.0f;
	SpriteUpdate();
	rotSpeed = 5.0f;
	player.thrSpeed = 60.0f;
	player.Alive = true;

	boost = false;
	turbo = false;
	

	for (int i = 0; i < DefAsteroid; i++) {
		xRandSpd = 10 + rand() % 40;
		yRandSpd = 10 + rand() % 40;
		xRandPos = rand() % GetScreenWidth();
		yRandPos = rand() % GetScreenHeight();
		asteroids[i] = {
			10, 0, xRandPos,
			10, 0, yRandPos,
			0, 0, 1, 

			xRandSpd,
			yRandSpd,
			0,
			40
		};


	}

}

void Object::Update() {
	Controller();
	CUpdate();
	SpriteUpdate();

}

void Object::Controller() {

	//Rotational Inputs 
	//Anti-Clockwise
	if (IsKeyDown(KEY_A)) {
		//Rotate(player.rotSpeed, player, player);

		float c = (float)cosf(GetFrameTime() * rotSpeed);
		float s = (float)sinf(GetFrameTime() * rotSpeed + PI);

		gameObject temp; //make temporary gameobject
		Set(temp);

		temp.m00 = player.m00 * c + player.m10 * -s + player.m20 * 0; //apply the main gameobject results to the temporary ones
		temp.m01 = player.m01 * c + player.m11 * -s + player.m21 * 0; //if you don't do this and apply the results directly
		temp.m02 = player.m02 * c + player.m12 * -s + player.m22 * 0; //then the new results being assigned will use the updated
																	  //variables instead of the initial ones.
		temp.m10 = player.m00 * s + player.m10 * c + player.m20 * 0;
		temp.m11 = player.m01 * s + player.m11 * c + player.m21 * 0;
		temp.m12 = player.m02 * s + player.m12 * c + player.m22 * 0;

		player.m00 = temp.m00; player.m10 = temp.m10; //make the player angles equal to the temporary gameobjects angles
		player.m01 = temp.m01; player.m11 = temp.m11;

	}

	//Clockwise
	if (IsKeyDown(KEY_D)) {
		float c = (float)cos(-GetFrameTime() * rotSpeed);
		float s = (float)sin(-GetFrameTime() * rotSpeed + PI);

		gameObject temp;
		Set(temp);

		temp.m00 = player.m00 * c + player.m10 * -s + player.m20 * 0;
		temp.m01 = player.m01 * c + player.m11 * -s + player.m21 * 0;
		temp.m02 = player.m02 * c + player.m12 * -s + player.m22 * 0;

		temp.m10 = player.m00 * s + player.m10 * c + player.m20 * 0;
		temp.m11 = player.m01 * s + player.m11 * c + player.m21 * 0;
		temp.m12 = player.m02 * s + player.m12 * c + player.m22 * 0;

		player.m00 = temp.m00; player.m10 = temp.m10;
		player.m01 = temp.m01; player.m11 = temp.m11;
		
	}

	//booster inputs
	if (IsKeyDown(KEY_W)) {
		//thrust
		if (player.ySpeed < MAX_SPEED && player.xSpeed < MAX_SPEED) {
			player.xSpeed += sin(player.angle()) * player.thrSpeed * GetFrameTime();
			player.ySpeed += -cos(player.angle()) * player.thrSpeed * GetFrameTime();
		}

		boost = true;
	}
	else if (IsKeyUp(KEY_W)) { boost = false; }

	if (IsKeyDown(KEY_S)) {
		//thrust
		if(player.ySpeed < MAX_SPEED && player.xSpeed < MAX_SPEED){
			player.xSpeed += sin(player.angle()) * player.thrSpeed * 4 * GetFrameTime();
			player.ySpeed += -cos(player.angle()) * player.thrSpeed * 4 * GetFrameTime();
		}

		turbo = true;
	}
	else if (IsKeyUp(KEY_S)) { turbo = false; }

	//function to limit the sped the player can move
	SpeedCap(player.xSpeed, player.ySpeed, player.xSpeed, player.ySpeed);


	//shooting
	if (IsKeyPressed(KEY_SPACE)) {
		AddBullet();
	}

}

void Object::CUpdate() {
	player.m20 += player.xSpeed * GetFrameTime();
	player.m21 += player.ySpeed * GetFrameTime();

	WrapCoordinates(player.m20, player.m21, player.m20, player.m21);
}

void Object::SpriteUpdate() {

	//Rotation
	for (int i = 0; i < 7; i++) {
		sx[i] = mx[i] * cos(player.angle()) - my[i] * sin(player.angle());
		sy[i] = mx[i] * sin(player.angle()) + my[i] * cos(player.angle());
	}

	//Tranform
	for (int i = 0; i < 7; i++) {
		sx[i] = sx[i] + player.m20;
		sy[i] = sy[i] + player.m21;
	}

	//update bullet and check for asteroid collision
	for (auto& b : bullet) {
		b.m20 += b.xSpeed * 5 * GetFrameTime();
		b.m21 += b.ySpeed * 5 * GetFrameTime();
		for (int i = 0; i < DefAsteroid * 4; i++) {
			if (Collision(asteroids[i].m20, asteroids[i].m21, asteroids[i].Health, b.m20, b.m21)) {
				b.m20 = -100;

				//points system
				if (asteroids[i].Health > 20) { points += 10; }
				else if (asteroids[i].Health > 10) { points += 25; }
				else if (asteroids[i].Health <= 10) { points += 50; }


				if (asteroids[i].Health > 10) {
					//create two child asteroids
					arrPos++;
					float angle1 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
					float angle2 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
					asteroids[arrPos].SimpleSet(asteroids[i].m20, asteroids[i].m21, 40.0f * sinf(angle1), -40.0f * cosf(angle1), asteroids[i].Health / 2);
					asteroids[i].SimpleSet(asteroids[i].m20, asteroids[i].m21, 40.0f * sinf(angle2), -40.0f * cosf(angle2), asteroids[i].Health / 2);
					//tempAsteroid.push_back({ a.x, a.y, 40.0f * sinf(angle2), -40.0f * cosf(angle2), a.oSize / 2, 0.0f });
				}
				else if (asteroids[i].Health < 20) {
					asteroids[i].Health = 0;
					asteroids[i].Alive = false;
				}

				
			}
		}
	}

	if (bullet.size() > 0) {
		auto i = std::remove_if(bullet.begin(), bullet.end(), [&](gameObject o)
			{return (o.m20 < 1 || o.m21 < 1 || o.m20 >= GetScreenWidth() || o.m21 >= GetScreenHeight()); });
		if (i != bullet.end()) {
			bullet.erase(i);
		}
	}

	//asteroid update
	for (int i = 0; i < DefAsteroid * 4; i++) {
		asteroids[i].m20 += asteroids[i].xSpeed * GetFrameTime();
		asteroids[i].m21 += asteroids[i].ySpeed * GetFrameTime();
		WrapCoordinates(asteroids[i].m20, asteroids[i].m21, asteroids[i].m20, asteroids[i].m21);
	}
}

void Object::Draw() {

	BeginDrawing();
	ClearBackground(BLACK);

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

	for (int i = 0; i < DefAsteroid * 4; i++) {
		DrawCircleLines(asteroids[i].m20, asteroids[i].m21, asteroids[i].Health, GREEN);
	}

	for (auto db : bullet) {
		DrawPixel(db.m20, db.m21, ORANGE);
	}

	DrawText(TextFormat("Score: %05i", points), 10, 10, 20, YELLOW);
	EndDrawing();
}

void Object::End() {

}

Object::~Object() {

}


void Object::AddBullet() {
	bullet.push_back({
		1, player.m10, player.m20,
		0, player.m11, player.m21,
		0, 0, 1,

		bulletSpeed * sinf(player.angle()),
		- bulletSpeed * cosf(player.angle()),
		0,
		0
		});
}

void Object::Set(gameObject &matrix) {
	matrix.m00 = 1; matrix.m10 = 0; matrix.m20 = 0;
	matrix.m01 = 0; matrix.m11 = 1; matrix.m21 = 0;
	matrix.m02 = 0; matrix.m12 = 0; matrix.m22 = 1;
}

void Object::Rotate(float radians, const gameObject gOi, gameObject gOo) {
	float c = (float)cosf(radians);
	float s = (float)sinf(radians + PI);// radians + MathF.PI --> +z access points into scene
	gameObject temp;
	Set(temp);
	
	temp.m00 = player.m00 * c + player.m10 * -s + player.m20 * 0;
	temp.m01 = player.m01 * c + player.m11 * -s + player.m21 * 0;
	temp.m02 = player.m02 * c + player.m12 * -s + player.m22 * 0;

	temp.m10 = player.m00 * s + player.m10 * c + player.m20 * 0;
	temp.m11 = player.m01 * s + player.m11 * c + player.m21 * 0;
	temp.m12 = player.m02 * s + player.m12 * c + player.m22 * 0;
			  													 
	player.m00 = temp.m00; player.m10 = temp.m10;
	player.m01 = temp.m01; player.m11 = temp.m11;
	player.m02 = temp.m02; player.m12 = temp.m12;


}

void Object::WrapCoordinates(float ix, float iy, float& ox, float& oy) {
	oy = iy;
	ox = ix;
	if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
	if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();

	if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
	if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();

}

void Object::SpeedCap(float ixs, float iys, float& oxs, float& oys) {

	if (player.xSpeed >= MAX_SPEED) {
		std::cout << "X :: you have hit MAX_SPEED :: " << player.xSpeed << std::endl;
		player.xSpeed = MAX_SPEED - 1;
	}
	else if (player.xSpeed <= -MAX_SPEED) {
		std::cout << "X :: you have hit MAX_SPEED :: " << player.xSpeed << std::endl;
		player.xSpeed = -MAX_SPEED + 1;
	}
	if (player.ySpeed >= MAX_SPEED) {
		std::cout << "Y :: you have hit MAX_SPEED :: " << player.ySpeed << std::endl;
		player.ySpeed = MAX_SPEED - 1;
	}
	else if (player.ySpeed <= -MAX_SPEED) {
		std::cout << "Y :: you have hit MAX_SPEED :: " << player.ySpeed << std::endl; //remove this later and all others
		player.ySpeed = -MAX_SPEED + 1;
	}
}

bool Object::Collision(float cx, float cy, float radius, float x, float y) {
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}
/*

00	10	20
01	11	21
02	12	22

1	2	3
4	5	6
7	8	9

a	b	c
d	e	f
g	h	i

1 * a + 2 * d + 3 * g;
4 * a + 5 * d + 6 * g;
7 * a + 8 * d + 9 * g;

1 * b + 2 * e + 3 * h;
4 * b + 5 * e + 6 * h;
7 * b + 8 * e + 9 * h;

1 * c + 2 * f + 3 * i;
4 * c + 5 * f + 6 * i;
7 * c + 8 * f + 9 * i;


00	10	
01	11		

1	2	
3	4	

a	b	
c	d	

1 * a + 2 * c;
3 * a + 4 * c;

1 * b + 2 * d;
3 * b + 4 * d;


*/

// unreal engine 4.27