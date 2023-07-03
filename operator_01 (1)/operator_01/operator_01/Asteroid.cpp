#include "Asteroid.h"

Asteroid::Asteroid() {
	M3.Set(M3);
}

Asteroid::~Asteroid() {

}

void Asteroid::Update() {
	M3.m20 += xSpeed * GetFrameTime();
	M3.m21 += ySpeed * GetFrameTime();
}

void Asteroid::Draw() {
	BeginDrawing();
	DrawCircleLines(M3.m20, M3.m21, Health, GREEN);
	EndDrawing();
}