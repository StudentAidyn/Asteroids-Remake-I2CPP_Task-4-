#include "Bullet.h"

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

void Bullet::Update() {
	M3.m20 += xSpeed * 5 * GetFrameTime();
	M3.m21 += ySpeed * 5 * GetFrameTime();
}

Bullet::Bullet(float x, float y, float rotX, float rotY) {
	M3.m20 = x; M3.m21 = y;
	M3.m10 = rotX; M3.m11 = rotY;
}

void Bullet::Draw() {
	BeginDrawing();
	DrawPixel(M3.m20, M3.m21, GREEN);
	EndDrawing();
}