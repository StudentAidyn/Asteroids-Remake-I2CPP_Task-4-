#include "Asteroid.h"

Asteroid::Asteroid() {

}

Asteroid::~Asteroid() {

}

void Asteroid::SimpleSet(float x, float y, float xs, float ys, int h) {
	M3.m20 = x;
	M3.m21 = y;
	xSpeed = xs;
	ySpeed = ys;
	Health = h;
}

void Asteroid::Update() {
	//positional updates
	M3.m20 += xSpeed * GetFrameTime();
	M3.m21 += ySpeed * GetFrameTime();
}

void Asteroid::Draw() {
	//Draw Asteroid
	DrawCircleLines(M3.m20, M3.m21, Health, GREEN);

}