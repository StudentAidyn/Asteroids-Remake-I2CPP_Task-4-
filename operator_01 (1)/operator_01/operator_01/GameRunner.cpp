#include "GameRunner.h"

GameRunner::GameRunner() {

}

void GameRunner::GameLoad() {
	player.PlStateStart();

	arrPos = DefAsteroid - 1;

	for (int i = 0; i < DefAsteroid; i++) {
		xRandSpd = 10 + rand() % 40;
		yRandSpd = 10 + rand() % 40;
		float angle = ((float)rand() / (float)RAND_MAX) * (2 * PI);
		do {
			xRandPos = rand() % GetScreenWidth();
			yRandPos = rand() % GetScreenHeight();
		} while (Collision(player.M3.m20, player.M3.m21, 50, xRandPos, yRandPos)); //Loop: makes sure Asteroids don't Spawn on Player
		asteroids[i].SimpleSet(xRandPos, yRandPos, xRandSpd * sinf(angle), -yRandSpd * cosf(angle), 40);
		//SimpleSet allows assignment of less values of more importance
	}
}

void GameRunner::RESET() {
	for (int i = 0; i < DefAsteroid * 4; i++) {
		asteroids[i].Health = 0;
	}
	GameLoad();
	points = 0;
	rounds = 0;

}

void GameRunner::Tick() {
	if (player.Alive == false) {
		RESET();
		GameLoad();
	}


	Controller();
	player.Update();
	WrapCoordinates(player.M3.m20, player.M3.m21, player.M3.m20, player.M3.m21); //possibly have to change this to in the Player Class
	
	ProjectileCheck();

	int ResetCheck = 0;
	for (int i = 0; i < DefAsteroid * 4; i++) {
		if (asteroids[i].Health == 0) {
			ResetCheck++;
		}
	}
	if (ResetCheck == 20) {
		points += 1000;
		GameLoad();
		rounds++;
	}

}

void GameRunner::Controller() {

	//Rotational Inputs 
	//Anti-Clockwise
	if (IsKeyDown(KEY_A)) {
		player.Rotate(GetFrameTime());
	}

	//Clockwise
	if (IsKeyDown(KEY_D)) {
		player.Rotate(-GetFrameTime());

	}

	//booster inputs
	if (IsKeyDown(KEY_W)) {
		player.Translate(1, GetFrameTime());

	}
	else if (IsKeyUp(KEY_W)) { player.boost = false; }

	if (IsKeyDown(KEY_S)) {
		player.Translate(4, GetFrameTime());

	}
	else if (IsKeyUp(KEY_S)) { player.turbo = false; }

	//shooting
	if (IsKeyPressed(KEY_SPACE)) {
		AddBullet();
	}

}

void GameRunner::ProjectileCheck() {


	//update bullet and check for asteroid collision
	for (auto& b : bullet) {
		b.Update();
		for (int i = 0; i < DefAsteroid * 4; i++) {
			if (asteroids[i].Health > 0) {
				if (Collision(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].Health, b.M3.m20, b.M3.m21)) {
					b.M3.m20 = -100;

					//points system
					if (asteroids[i].Health > 20) { points += 10; }
					else if (asteroids[i].Health > 10) { points += 25; }
					else if (asteroids[i].Health <= 10) { points += 50; }


					if (asteroids[i].Health > 10) {
						//create two child asteroids
						arrPos++;
						float angle1 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
						float angle2 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
						asteroids[arrPos].SimpleSet(asteroids[i].M3.m20, asteroids[i].M3.m21, 40.0f * sinf(angle1), -40.0f * cosf(angle1), asteroids[i].Health / 2);
						asteroids[i].SimpleSet(asteroids[i].M3.m20, asteroids[i].M3.m21, 40.0f * sinf(angle2), -40.0f * cosf(angle2), asteroids[i].Health / 2);
					}
					else if (asteroids[i].Health < 20) {
						asteroids[i].Health = 0;
						asteroids[i].Alive = false;
					}


				}
			}

		}
	}

	if (bullet.size() > 0) {
		auto i = std::remove_if(bullet.begin(), bullet.end(), [&](Bullet o)
			{return (o.M3.m20 < 1 || o.M3.m21 < 1 || o.M3.m20 >= GetScreenWidth() || o.M3.m21 >= GetScreenHeight()); });
		if (i != bullet.end()) {
			bullet.erase(i);
		}
	}

	//asteroid update
	for (int i = 0; i < DefAsteroid * 4; i++) {
		asteroids[i].Update();
		WrapCoordinates(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].M3.m20, asteroids[i].M3.m21);
		if (Collision(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].Health, player.M3.m20, player.M3.m21)) {
			player.Alive = false;
		}
	}
}

void GameRunner::Draw() {

	BeginDrawing();
	ClearBackground(BLACK);

	player.Draw();

	for (int i = 0; i < DefAsteroid * 4; i++) {
		asteroids[i].Draw();
	}

	for (auto db : bullet) {
		db.Draw();
	}


	DrawText(TextFormat("Score: %05i", points), 10, 10, 10, YELLOW);
	DrawText(TextFormat("Round: %i", rounds), 10, 20, 10, YELLOW);
	EndDrawing();
}


GameRunner::~GameRunner() {

}


void GameRunner::AddBullet() {
	bullet.push_back({player.M3.m20, player.M3.m21, player.M3.m10, player.M3.m11});

}


void GameRunner::WrapCoordinates(float ix, float iy, float& ox, float& oy) {
	oy = iy;
	ox = ix;
	if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
	if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();

	if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
	if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();

}


bool GameRunner::Collision(float cx, float cy, float radius, float x, float y) {
	return sqrt((x - cx) * (x - cx) + (y - cy) * (y - cy)) < radius;
}
