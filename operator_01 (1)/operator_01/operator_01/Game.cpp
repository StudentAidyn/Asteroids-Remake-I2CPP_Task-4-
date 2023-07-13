//this is the old one that I don't want to use because I followed too close to a video

#include "Game.h"
#include <vector>

Game::Game() {
	Game::player;
	bool boost = false;
	bool turbo = false;
}
void Game::GameLoad(){


	asteroid.push_back({ 20.0f, 20.0f, 60.0f, 0.0, (int)40, 0.0f });
	asteroid.push_back({ 70.0f, 70.0f, 60.0f, -60.0, (int)40, 0.0f });

	player.x = GetScreenWidth() / 2;
	player.y = GetScreenHeight() / 2;
	player.dx = 0.0f;
	player.dy = 0.0f;
	player.angle = 0.0f;
		//set up all game instances, 
		//..this can includes the points and the randomisation of the asteroids


}
void Game::Update() {
	//ROTATE
	if (IsKeyDown(KEY_D)) {
		//player.Rotate(player, -GetFrameTime());
		player.angle += 5.0f * GetFrameTime();
	}

	if (IsKeyDown(KEY_A)) {
		//player.Rotate(player, -GetFrameTime());
		player.angle -= 5.0f * GetFrameTime();
	}
	//BOOST
	if (IsKeyDown(KEY_W)) {
		player.dx += sin(player.angle) * 20.0f * GetFrameTime();
		player.dy += -cos(player.angle) * 20.0f * GetFrameTime();
		boost = true;
	}
	else if (IsKeyUp(KEY_W)) { boost = false; }

	if (IsKeyDown(KEY_S)) {
		player.dx += sin(player.angle) * 1000.0f * GetFrameTime();
		player.dy += -cos(player.angle) * 1000.0f * GetFrameTime();
		turbo = true;
	}
	else if (IsKeyUp(KEY_S)) { turbo = false; }

	if (IsKeyDown(KEY_SPACE)) {
		bullet.push_back({ player.x, player.y, 500.0f * sinf(player.angle), -500.0f * cosf(player.angle), 0, 0 });
	}
	
	player.x += player.dx * 4 * GetFrameTime();
	player.y += player.dy * 4 * GetFrameTime();







	WrapCoordinates(player.x, player.y, player.x, player.y);

	for (auto &a : asteroid) {

		a.x += a.dx * GetFrameTime();
		a.y += a.dy * GetFrameTime();
		WrapCoordinates(a.x, a.y, a.x, a.y);
		DrawCircle(a.x, a.y, a.oSize, GRAY);
	}


	for (auto& b : bullet) {

		b.x += b.dx * GetFrameTime();
		b.y += b.dy * GetFrameTime();
		//WrapCoordinates(b.x, b.y, b.x, b.y);
		//DrawPixel(b.x-2, b.y -2, RED);
		//DrawPixel(b.x - 1, b.y - 1, ORANGE);
		DrawPixel(b.x, b.y, YELLOW);
		//DrawPixel(b.x +1, b.y + 1, GREEN);
		//DrawPixel(b.x +2, b.y + 2, BLUE);
		//DrawPixel(b.x +3, b.y + 3, PURPLE);

		for (auto& a : asteroid) {
			if (Collision(a.x, a.y, a.oSize, b.x, b.y)) {
				b.x = -100;
				if (a.oSize > 10) {
					//create two child asteroids
					float angle1 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
					float angle2 = ((float)rand() / (float)RAND_MAX) * (2 * PI);
					tempAsteroid.push_back({ a.x, a.y, 40.0f * sinf(angle1), -40.0f * cosf(angle1), a.oSize / 2, 0.0f });
					tempAsteroid.push_back({ a.x, a.y, 40.0f * sinf(angle2), -40.0f * cosf(angle2), a.oSize / 2, 0.0f });
				}
				//points system
				if (a.oSize > 20) { points += 10; }
				else if (a.oSize > 10) { points += 25; }
				else if (a.oSize <= 10) { points += 50; }
				a.x = -100;
			}
		}
	}

	for (auto ta : tempAsteroid) {
		asteroid.push_back(ta);
	}
	tempAsteroid.clear();

	//BULLET DESTROY FUNCTION
	//if (bullet.size() > 0) {
	//	auto i = std::remove_if(bullet.begin(), bullet.end(), [&](gameobject o)
	//		{return (o.x < 1 || o.y < 1 || o.x >= getscreenwidth() || o.y >= getscreenheight()); });
	//	if (i != bullet.end()) {
	//		bullet.erase(i);
	//	}
	//}

	//ASTEROID DESTROY FUNCTION
	if (asteroid.size() > 0) {
		auto i = std::remove_if(asteroid.begin(), asteroid.end(), [&](gameObject o) {return (o.x < 0); }); {
			if (i != asteroid.end()) {
				asteroid.erase(i);
			}
		}

	}

	float mx[7] = { 0.0f, 5.0f, -5.0f, 4.0f, -4.0f, 0.0f, 0.0f};
	float my[7] = { -5.0f, 5.0f, 5.0f, 3.0f, 3.0f,  7.0f, 15.0f};
	float sx[7], sy[7];

	for (int i = 0; i < 7; i++) {
		sx[i] = mx[i] * cosf(player.angle) - my[i] * sinf(player.angle);
		sy[i] = mx[i] * sinf(player.angle) + my[i] * cosf(player.angle);
	}

	for (int i = 0; i < 7; i++) {
		sx[i] = sx[i] + player.x;
		sy[i] = sy[i] + player.y;
	}

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

	

}
void Game::Draw() {

	float ta = 0;
	float tb = 0;
	Vector2 top; top.x = 5; top.y = 0;
	Vector2 rW; rW.x = 10; rW.y = 10;
	Vector2 lW; lW.x = 0; lW.y = 10;
	Vector2 bsR; bsR.x = 9; bsR.y = 8;
	Vector2 bsL; bsL.x = 1; bsL.y = 8;
		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(TextFormat("Score: %05i", points), 10, 10, 20, YELLOW);

		//DrawLineV(top, rW, PURPLE);
		//DrawLineV(top, lW, PURPLE);
		//DrawLineV(bsL, bsR, PURPLE);

		//DrawLine(bsL.x, bsL.y, bsL.x + 4, bsL.y + 4, RED);
		//DrawLine(bsR.x, bsR.y, bsR.x - 4, bsR.y + 4, RED);

	
		EndDrawing();
}

void Game::End() {

}

void Game::WrapCoordinates(float ix, float iy, float &ox, float &oy) {
	oy = iy;
	ox = ix;
	if (ix < 0.0f) ox = ix + (float)GetScreenWidth();
	if (ix >= (float)GetScreenWidth()) ox = ix - (float)GetScreenWidth();

	if (iy < 0.0f) oy = iy + (float)GetScreenHeight();
	if (iy >= (float)GetScreenHeight()) oy = iy - (float)GetScreenHeight();

}

bool Game::Collision(float cx, float cy, float radius, float x, float y) {
	return sqrt((x - cx)*(x - cx) + (y - cy)*(y - cy)) < radius;
}