#include "GameRunner.h"


GameRunner::GameRunner() {
	asteroids[DefAsteroidNum * 4];
}

GameRunner::~GameRunner() {

}

void GameRunner::GameLoad() {
	player.Reset();

	arrPos = DefAsteroidNum - 1;

	for (int i = 0; i < DefAsteroidNum; i++) {
		asteroids[i].xRandSpd = 10 + rand() % 40;
		asteroids[i].yRandSpd = 10 + rand() % 40;
		do {
			asteroids[i].xRandPos = (rand() + 1) % GetScreenWidth();
			asteroids[i].yRandPos = (rand() + 1) % GetScreenHeight();
		} while (player.M3.Collision(player.M3.m20, player.M3.m21, 50, asteroid.xRandPos, asteroid.yRandPos));
		asteroids[i].SimpleSet(asteroid.xRandPos, asteroid.yRandPos, asteroid.xRandSpd, asteroid.yRandSpd, asteroid.STRT_HEALTH);


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
	//check if the player has been hit by an asteroid, if so RESET
	if (player.Alive == false) {
		Reset();
		GameLoad();
	}

	float DeltaTime = GetFrameTime();

	player.Controller(DeltaTime);

	player.Update();

	//asteroid update
	for (int i = 0; i < DefAsteroidNum * 4; i++) {
		asteroids[i].Update();
		asteroid.M3.WrapCoordinates(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].M3.m20, asteroids[i].M3.m21);
		if (asteroid.M3.Collision(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].Health, player.M3.m20, player.M3.m21)) {
			player.Alive = false;
		}
	}

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


}

void GameRunner::SpriteUpdate() {

	
	//update bullet and check for asteroid collision
	for (auto& b : bullet) {
		b.Update();
		for (int i = 0; i < DefAsteroidNum * 4; i++) {
			if (asteroids[i].M3.Collision(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].Health, b.M3.m20, b.M3.m21)) {
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
					//tempAsteroid.push_back({ a.x, a.y, 40.0f * sinf(angle2), -40.0f * cosf(angle2), a.oSize / 2, 0.0f });
				}
				else if (asteroids[i].Health < 20) {
					asteroids[i].Health = 0;
					asteroids[i].Alive = false;
				}


			}
		}

		//if (b.M3.m20 < 1 || b.M3.m21 < 1 || b.M3.m20 >= GetScreenWidth() || b.M3.m21 >= GetScreenHeight()) {
		//	b.erase();
		//}
	}

	//if (bullet.size() > 0) {
	//	auto i = std::remove_if(bullet.begin(), bullet.end(), [&](bullet.M3 o)
	//		{return (o.m20 < 1 || o.m21 < 1 || o.m20 >= GetScreenWidth() || o.m21 >= GetScreenHeight()); });
	//	if (i != bullet.end()) {
	//		bullet.erase(i);
	//	}
	//}

	//for (auto& Rb : bullet)

}

void GameRunner::Draw() {

	BeginDrawing();
	ClearBackground(BLACK);

	player.Draw();

	for (int i = 0; i < DefAsteroidNum * 4; i++) {
		//asteroids[i].Draw();
		DrawCircleLines(asteroids[i].M3.m20, asteroids[i].M3.m21, asteroids[i].Health, GREEN);
	}

	for (auto db : bullet) { 
		db.Draw();
	}

	DrawText(TextFormat("Score: %05i", points), 10, 10, 10, YELLOW);
	DrawText(TextFormat("Round: %i", rounds), 10, 20, 10, YELLOW);
	EndDrawing();
}


void GameRunner::AddBullet() {
	bullet.push_back({ //x, y, rotx, roty
	player.M3.m20, player.M3.m21, player.M3.m10, player.M3.m11
	});
}

