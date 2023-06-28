#include "GameRunner.h"
#include "Player.h"
#include "Asteroid.h"
#include <iostream>


Player player;

void GameRunner::GameLoad() {
	
	player.M3.m20 = GetScreenWidth() / 2.0f;
	player.M3.m21 = GetScreenHeight() / 2.0f;
	SpriteUpdate();
	player.rotSpeed = 5.0f;
	player.thrSpeed = 60.0f;
	player.Alive = true;
	player.xSpeed = 0;
	player.ySpeed = 0;
	boost = false;
	turbo = false;

	arrPos = DefAsteroidNum - 1;

	for (int i = 0; i < DefAsteroidNum; i++) {
		xRandSpd = 10 + rand() % 40;
		yRandSpd = 10 + rand() % 40;
		do {
			xRandPos = rand() % GetScreenWidth();
			yRandPos = rand() % GetScreenHeight();
		} while (Collision(player.m20, player.m21, 50, xRandPos, yRandPos));
		asteroids[i] = {
			10, -0, xRandPos,
			10, 0, yRandPos,
			0, 0, 1,

			xRandSpd,
			yRandSpd,
			0,
			40
		};


	}

}

void GameRunner::Reset() {
	for (int i = 0; i < DefAsteroidNum * 4; i++) {
		asteroids[i].Health = 0;
	}
	GameLoad();
	points = 0;
	rounds = 0;

}

void GameRunner::Update() {
	if (player.Alive == false) {
		Reset();
		GameLoad();
	}
	player.Controller();
	ContUpdate();
	SpriteUpdate();
	int ResetCheck = 0;
	for (int i = 0; i < DefAsteroidNum * 4; i++) {
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


void GameRunner::ContUpdate() {


	//asteroid update
	for (int i = 0; i < DefAsteroidNum * 4; i++) {
		asteroids[i].m20 += asteroids[i].xSpeed * GetFrameTime();
		asteroids[i].m21 += asteroids[i].ySpeed * GetFrameTime();
		WrapCoordinates(asteroids[i].m20, asteroids[i].m21, asteroids[i].m20, asteroids[i].m21);
		if (Collision(asteroids[i].m20, asteroids[i].m21, asteroids[i].Health, player.m20, player.m21)) {
			player.Alive = false;
		}
	}
}

void GameRunner::SpriteUpdate() {

	//update bullet and check for asteroid collision
	for (auto& b : bullet) {
		b.m20 += b.xSpeed * 5 * GetFrameTime();
		b.m21 += b.ySpeed * 5 * GetFrameTime();
		for (int i = 0; i < DefAsteroidNum * 4; i++) {
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


}

void GameRunner::Draw() {

	BeginDrawing();
	ClearBackground(BLACK);

	for (int i = 0; i < DefAsteroidNum * 4; i++) {
		DrawCircleLines(asteroids[i].m20, asteroids[i].m21, asteroids[i].Health, GREEN);
	}

	for (auto db : bullet) {
		DrawPixel(db.m20, db.m21, ORANGE);
	}

	DrawText(TextFormat("Score: %05i", points), 10, 10, 10, YELLOW);
	DrawText(TextFormat("Round: %i", rounds), 10, 20, 10, YELLOW);
	EndDrawing();
}




void GameRunner::AddBullet() {
	bullet.push_back({ //x, y, rotx, roty
	player.M3.m20, player.M3.m21, player.M3.m10, player.M3.m11
	//bulletSpeed * sinf(angle()),
	//-bulletSpeed * cosf(angle()),
		});
}

